#ifndef UIWSROUTE_H
#define UIWSROUTE_H

#include "nlohmann/json.hpp"
#include "webserver/server_ws.hpp"
using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

class UIWsRoute
{
public:
    static UIWsRoute *Instance();

    void Init(WsServer::Endpoint& ep);
    std::shared_ptr<WsServer::Connection> GetConnection();
    void SetConnection(std::shared_ptr<WsServer::Connection> connection);

    void SendMsg(const std::string& msg);

private:
    UIWsRoute();
    ~UIWsRoute();

    static void onOpen(std::shared_ptr<WsServer::Connection> connection);

    static void onClose(std::shared_ptr<WsServer::Connection> connection,
			int status, const std::string &);

    static void onError(std::shared_ptr<WsServer::Connection> connection,
			const SimpleWeb::error_code &ec);

    static void onMessage(std::shared_ptr<WsServer::Connection> connection,
			  std::shared_ptr<WsServer::Message> message);

private:
    static UIWsRoute *_This;
    std::shared_ptr<WsServer::Connection> _Connection;
};

#endif // UIWSROUTE_H
