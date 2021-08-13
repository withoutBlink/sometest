#ifndef WSSROUTE_H
#define WSSROUTE_H

#include "utils/softwareabout.h"
#include "nlohmann/json.hpp"
#include "webserver/server_ws.hpp"
#include "src/testcontrol.h"
#include "easylog/easylogging++.h"
#include "config.h"

using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

class WSSRoute
{
public:
    static WSSRoute *Instance();
	void Init(WsServer::Endpoint& ep);
    void SendMsg(std::string& ipaddr, const std::string& msg);
    void BroadCast(const std::string& msg);
    // void InitUi();
    // void InitItem();

private:
    WSSRoute();
    ~WSSRoute();

    void SetConnection(std::shared_ptr<WsServer::Connection> connection);
    std::shared_ptr<WsServer::Connection> GetConnection(const std::string& addr);
    std::shared_ptr<WsServer::Connection> GetConnection(const std::uint16_t& id);
    void SendMsg(std::shared_ptr<WsServer::Connection> connection, const std::string& msg);
    void ErrorRespond(std::string err, std::shared_ptr<WsServer::Connection> connection);
    void CloseConnection(std::shared_ptr<WsServer::Connection> connection);
    static void onOpen(std::shared_ptr<WsServer::Connection> connection);
    static void onClose(std::shared_ptr<WsServer::Connection> connection,
                int status, const std::string &);
    static void onError(std::shared_ptr<WsServer::Connection> connection,
                const SimpleWeb::error_code &ec);
    static void onMessage(std::shared_ptr<WsServer::Connection> connection,
                  std::shared_ptr<WsServer::Message> message);
    void onItemMesg(const nlohmann::json request, std::shared_ptr<WsServer::Connection> connection);
    void onUIMesg(const nlohmann::json request, std::shared_ptr<WsServer::Connection> connection);

private:
    static WSSRoute *_This;
    // std::map<std::string, std::string> _Key;
    std::map<std::string, std::shared_ptr<WsServer::Connection>> _UIConnection;
    std::map<std::string, std::shared_ptr<WsServer::Connection>> _ItemConnection;
    std::mutex _ConnectionMutex;
};


#endif // WSSROUTE_H
