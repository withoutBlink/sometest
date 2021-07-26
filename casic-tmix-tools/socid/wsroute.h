#ifndef WSROUTE_H
#define WSROUTE_H

#include "nlohmann/json.hpp"

#include "webserver/client_ws.hpp"
using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;

class WsRoute
{
public:
	static WsRoute *Instance();

	std::shared_ptr<WsClient::Connection> GetConnection();
	void SetConnection(std::shared_ptr<WsClient::Connection> connection);
	void Destroy();
	void SendMsg(const std::string& msg);

	void RegisterUiCallBack(std::function<void (const nlohmann::json&)> uiroute);
	void RegisterSvcCallBack(std::function<void (const nlohmann::json&)> svcroute);
	void Start(std::function<void (void)> start);

private:
	WsRoute();
	~WsRoute();

	static void onOpen(std::shared_ptr<WsClient::Connection> connection);
	static void onClose(std::shared_ptr<WsClient::Connection> connection, int status, const std::string & /*reason*/);
	static void onError(std::shared_ptr<WsClient::Connection> connection, const SimpleWeb::error_code &ec);
	static void onMessage(std::shared_ptr<WsClient::Connection> connection, std::shared_ptr<WsClient::Message> message);

private:
	static WsRoute *_This;
	bool _Run;
	WsClient *_Client;
	std::thread *_Worker;
	std::shared_ptr<WsClient::Connection> _Connection;
	std::function<void ()> _StartCallBack;
	std::function<void (const nlohmann::json&)> _UIRoute;
	std::function<void (const nlohmann::json&)> _SvcRoute;
};

#endif // WSROUTE_H
