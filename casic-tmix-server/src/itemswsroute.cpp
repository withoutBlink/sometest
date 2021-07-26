#include "itemswsroute.h"
#include "easylog/easylogging++.h"

#include "uiwsroute.h"

ItemsWsRoute *ItemsWsRoute::_This = nullptr;

ItemsWsRoute *ItemsWsRoute::Instance()
{
	if (!_This) {
		_This = new ItemsWsRoute;
	}
	return _This;
}

void ItemsWsRoute::Init(WsServer::Endpoint &ep)
{
	ep.on_open = onOpen;
	ep.on_close = onClose;
	ep.on_error = onError;
	ep.on_message = onMessage;
}

std::shared_ptr<WsServer::Connection> ItemsWsRoute::GetConnection()
{
	return this->_Connection;
}

void ItemsWsRoute::SetConnection(std::shared_ptr<WsServer::Connection> connection)
{
	this->_Connection = connection;
}

void ItemsWsRoute::SendMsg(const std::string &msg)
{
	if (msg.empty())
		return ;

	LOG(INFO) << "\nItems SendMsg:\n" << msg;

	auto sendstream = std::make_shared<WsServer::SendStream>();
	*sendstream << msg;
	if (this->_Connection)
		this->_Connection->send(sendstream);
}

ItemsWsRoute::ItemsWsRoute()
{

}

ItemsWsRoute::~ItemsWsRoute()
{

}

void ItemsWsRoute::onOpen(std::shared_ptr<WsServer::Connection> connection)
{
	LOG(DEBUG) << "Items Opened connection " << connection.get();
	ItemsWsRoute::Instance()->SetConnection(connection);
}

void ItemsWsRoute::onClose(std::shared_ptr<WsServer::Connection> connection,
	     int status, const std::string &)
{
	LOG(DEBUG) << "Items Closed connection " << connection.get() << " with status code " << status;
	ItemsWsRoute::Instance()->SetConnection(nullptr);
}

void ItemsWsRoute::onError(std::shared_ptr<WsServer::Connection> connection,
	     const SimpleWeb::error_code &ec)
{
	LOG(WARNING) << "Items Error in connection " << connection.get() << ". " << "Error: " << ec << ", error message: " << ec.message();
	ItemsWsRoute::Instance()->SetConnection(nullptr);
}

void ItemsWsRoute::onMessage(std::shared_ptr<WsServer::Connection> connection,
	       std::shared_ptr<WsServer::Message> message)
{
	auto msg = message->string();
	LOG(DEBUG) << "\n>>>>> Message received <<<<<\n"
		   << "from Items: \n"
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
		if (method == "CallUI") {
			UIWsRoute::Instance()->SendMsg(msg);
		}
	} catch (std::exception &e) {
		LOG(ERROR) << e.what();
//		if (method.empty())
//			return;
//		response = {
//			{"Method", method},
//			{"Content", ""},
//			{"Result", {
//				 {"Code", -1}, {"ErrMsg", e.what()}
//			 }}
//		};
	}

//	LOG(INFO) << response.dump(4);
//	ItemsWsRoute::Instance()->SendMsg(response.dump(4));
}

