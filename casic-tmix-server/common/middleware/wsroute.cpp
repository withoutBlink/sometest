#include "wsroute.h"

#include "nlohmann/json.hpp"
#include "easylog/easylogging++.h"

#include "config.h"

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
	_This->StopWork();
	if (_This) {
		delete _This;
		_This = nullptr;
	}
}

void WsRoute::SendMsg(const QString& msg)
{
	SendMsg(msg.toStdString());
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

void WsRoute::StartWork()
{
	if (!this->_Client) {
		return ;
	}

	this->_Run = true;
	while (this->_Run) {
		this->_Client->on_open = onOpen;
		this->_Client->on_close = onClose;
		this->_Client->on_error = onError;
		this->_Client->on_message =  onMessage;
		this->_Client->start();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	emit this->SignalResultReady();
}


void WsRoute::StopWork()
{
	if (this->_Run) {
		this->_Run = false;
		this->_Client->stop();
	}
}

WsRoute::WsRoute():
	_Run(false)
{
	QString url = QString("%1:%2%3")
//			.arg("172.70.6.100")
			.arg(IP_SERVICE)
			.arg(Config::Instance()->Data.Port)
			.arg(WS_URL_SVCUI);

	this->_Client = new WsClient(url.toStdString());
}

WsRoute::~WsRoute()
{
	this->StopWork();

	if (this->_Client) {
		delete this->_Client;
		this->_Client = nullptr;
	}
}

void WsRoute::onOpen(std::shared_ptr<WsClient::Connection> connection)
{
	LOG(DEBUG) << "Opened connection " << connection.get();
	WsRoute::Instance()->SetConnection(connection);
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
		QString method = QString::fromStdString(request["Method"].get<std::string>());
		if (method == "SendCallUI") {
			emit WsRoute::Instance()->SignalCallUI(QString::fromUtf8(content.dump().c_str()));
		} else if (method == "Temperature") {
			emit WsRoute::Instance()->SignalRecvTemp(QString::fromUtf8(content.dump().c_str()));
		} else if (method == "Messages") {
			emit WsRoute::Instance()->SignalMessages(QString::fromUtf8(content.dump().c_str()));
		} else if (method == "Started") {
			emit WsRoute::Instance()->SignalStarted(QString::fromUtf8(content.dump().c_str()));
		} else if (method == "ItemList") {
			emit WsRoute::Instance()->SignalItemList(QString::fromUtf8(content.dump().c_str()));
		} else if (method == "ItemResult") {
			emit WsRoute::Instance()->SignalItemResult(QString::fromUtf8(content.dump().c_str()));
		}
	} catch (std::exception &e) {
		LOG(WARNING) << e.what();
	}
}
