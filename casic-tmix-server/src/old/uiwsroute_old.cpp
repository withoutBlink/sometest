#include "uiwsroute.h"

#include "easylog/easylogging++.h"

UIWsRoute *UIWsRoute::_This = nullptr;

UIWsRoute *UIWsRoute::Instance()
{
	if (!_This) {
		_This = new UIWsRoute;
	}
	return _This;
}

void UIWsRoute::Init(WsServer::Endpoint &ep)
{
	ep.on_open = onOpen;
	ep.on_close = onClose;
	ep.on_error = onError;
	ep.on_message = onMessage;
}

std::shared_ptr<WsServer::Connection> UIWsRoute::GetConnection()
{
	return this->_Connection;
}

void UIWsRoute::SetConnection(std::shared_ptr<WsServer::Connection> connection)
{
	this->_Connection = connection;
}

void UIWsRoute::SendMsg(const std::string &msg)
{
	if (msg.empty())
		return ;

	LOG(INFO) << "\nUI SendMsg:\n" << msg;

	auto sendstream = std::make_shared<WsServer::SendStream>();
	*sendstream << msg;
	if (this->_Connection)
		this->_Connection->send(sendstream);
}

UIWsRoute::UIWsRoute()
{

}

UIWsRoute::~UIWsRoute()
{

}

void UIWsRoute::onOpen(std::shared_ptr<WsServer::Connection> connection)
{
	LOG(DEBUG) << "UI Opened connection " << connection.get();
	UIWsRoute::Instance()->SetConnection(connection);
}

void UIWsRoute::onClose(std::shared_ptr<WsServer::Connection> connection,
	     int status, const std::string &)
{
	LOG(DEBUG) << "UI Closed connection " << connection.get() << " with status code " << status;
	UIWsRoute::Instance()->SetConnection(nullptr);
}

void UIWsRoute::onError(std::shared_ptr<WsServer::Connection> connection,
	     const SimpleWeb::error_code &ec)
{
	LOG(WARNING) << "UI Error in connection " << connection.get() << ". " << "Error: " << ec << ", error message: " << ec.message();
	UIWsRoute::Instance()->SetConnection(nullptr);
}

void UIWsRoute::onMessage(std::shared_ptr<WsServer::Connection> connection,
	       std::shared_ptr<WsServer::Message> message)
{
	auto msg = message->string();
	LOG(DEBUG) << "\n>>>>> Message received <<<<<\n"
		   << "from ui: \n"
		   << connection.get()
		   << "\ncontent: \n"
		   << msg
		   << "\n-------------------------";

	nlohmann::json response;
	std::string method;
	try {
		nlohmann::json request = nlohmann::json::parse(msg);
		if (request.is_null() || !request.is_object()
				|| !request.contains("Method") || !request["Method"].is_string()
				|| !request.contains("Content") || request["Content"].is_null()
				) {
			throw std::invalid_argument("failed json content.");
		}

		const nlohmann::json& content = request["Content"];
		method = request["Method"];
		if (method == "GetSrvIP") {
		}
	} catch (std::exception &e) {
		LOG(ERROR) << e.what();
		if (method.empty())
			return;
		response = {
			{"Method", method},
			{"Content", ""},
			{"Result", {
				 {"Code", -1}, {"ErrMsg", e.what()}
			 }}
		};
	}

	LOG(INFO) << response.dump(4);
	UIWsRoute::Instance()->SendMsg(response.dump(4));
}

