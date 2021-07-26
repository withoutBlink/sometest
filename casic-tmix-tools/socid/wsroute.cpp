#include "wsroute.h"

#include "nlohmann/json.hpp"
#include "easylog/easylogging++.h"

#include "utils/softwareabout.h"

using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;

WsRoute *WsRoute::_This = nullptr;

WsRoute *WsRoute::Instance()
{
	if (!_This) {
		_This = new WsRoute;
	}
	return _This;
}

std::shared_ptr<WsClient::Connection> WsRoute::GetConnection()
{
	return this->_Connection;
}

void WsRoute::SetConnection(std::shared_ptr<WsClient::Connection> connection)
{
	this->_Connection = connection;
}

void WsRoute::Destroy()
{
	this->_Client->stop();
	this->_Run = false;
	this->_Worker->join();
	delete this->_Worker;
	this->_Worker = nullptr;
}

void WsRoute::SendMsg(const std::string& msg)
{
	if (msg.empty())
		return ;

	LOG(INFO) << "\n"
		  << msg;

	auto sendmsg = std::make_shared<WsClient::SendStream>();
	*sendmsg << msg;
	if (this->_Connection)
		this->_Connection->send(sendmsg);
}

void WsRoute::RegisterUiCallBack(std::function<void (const nlohmann::json &)> uiroute)
{
	this->_UIRoute = uiroute;
}

void WsRoute::RegisterSvcCallBack(std::function<void (const nlohmann::json &)> svcroute)
{
	this->_SvcRoute = svcroute;
}

void WsRoute::Start(std::function<void ()> start)
{
	//	this->_Worker = new std::thread([=]() {
	if (!this->_Client) {
		return ;
	}

	this->_StartCallBack = start;
	while (this->_Run) {
		this->_Client->on_open = onOpen;
		this->_Client->on_close = onClose;
		this->_Client->on_error = onError;
		this->_Client->on_message =  onMessage;
		this->_Client->start();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	//	});
}

WsRoute::WsRoute():
	_Run(true)
{
	this->_Client = new WsClient(WS_URL_ITEMS);
}

WsRoute::~WsRoute()
{
	delete this->_Client;
	this->_Client = nullptr;
}

void WsRoute::onOpen(std::shared_ptr<WsClient::Connection> connection)
{
	LOG(DEBUG) << "Opened connection " << connection.get();
	WsRoute::Instance()->SetConnection(connection);
	WsRoute::Instance()->_StartCallBack();
}

void WsRoute::onClose(std::shared_ptr<WsClient::Connection> connection, int status, const std::string &)
{
	LOG(DEBUG) << "Closed connection " << connection.get() << " with status code " << status;
	WsRoute::Instance()->SetConnection(nullptr);
}

void WsRoute::onError(std::shared_ptr<WsClient::Connection> connection, const SimpleWeb::error_code &ec)
{
	LOG(WARNING) << "Error in connection " << connection.get() << ". " << "Error: " << ec << ", error message: " << ec.message();
}

void WsRoute::onMessage(std::shared_ptr<WsClient::Connection> connection, std::shared_ptr<WsClient::Message> message)
{
	auto msg = message->string();
	LOG(DEBUG) << "\n>>>>> Message received <<<<<\n"
		      "from:\n"
		   << connection.get()
		   << "\ncontent:\n"
		   << msg
		   << "\n------------------------------";
	try {
		nlohmann::json request = nlohmann::json::parse(msg);
		if (request.is_null() || !request.is_object()
				|| !request.contains("Method") || !request["Method"].is_string()
				|| !request.contains("Content") || request["Content"].is_null()
				) {
			throw std::invalid_argument("failed json request parse.");
		}

		nlohmann::json &content = request["Content"];
		std::string method = request["Method"].get<std::string>();
		if (method == "CallUI") {
			WsRoute::Instance()->_UIRoute(content);
		} else if (method == "CallSVC") {
			WsRoute::Instance()->_SvcRoute(content);
		}
	} catch (std::exception &e) {
		LOG(WARNING) << e.what();
	}
}
