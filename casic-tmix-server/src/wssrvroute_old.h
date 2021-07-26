#ifndef WSSRVROUTE_H
#define WSSRVROUTE_H

#include "utils/softwareabout.h"

#include "nlohmann/json.hpp"
#include "webserver/server_ws.hpp"
using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

class WSSrvRoute
{
public:
	static WSSrvRoute *Instance();

	void Init(WsServer::Endpoint& ep);
	std::shared_ptr<WsServer::Connection> GetConnection(const std::string &key);
	void SetConnection(const std::string &key, std::shared_ptr<WsServer::Connection> connection);

	void SendMsgToUI(const std::string& msg);
	void SendMsgToItem(const std::string& msg);
	void SendMsg(const std::string &key, const std::string& msg);

	void InitUi();
	void InitItem();

private:
	WSSrvRoute();
	~WSSrvRoute();
    nlohmann::json parseContent(nlohmann::json richContent);
    nlohmann::json parseContent(std::string richContent);

	static void onOpen(std::shared_ptr<WsServer::Connection> connection);

	static void onClose(std::shared_ptr<WsServer::Connection> connection,
			    int status, const std::string &);

	static void onError(std::shared_ptr<WsServer::Connection> connection,
			    const SimpleWeb::error_code &ec);

	static void onMessage(std::shared_ptr<WsServer::Connection> connection,
			      std::shared_ptr<WsServer::Message> message);

private:
	static WSSrvRoute *_This;
	std::map<std::string, std::string> _Key;
	std::map<std::string, std::shared_ptr<WsServer::Connection>> _Connection;
	std::mutex _ConnectionMutex;
};


#endif // WSSRVROUTE_H
