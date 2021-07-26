#ifndef WORKER_H
#define WORKER_H

#include "nlohmann/json.hpp"
#include "webserver/client_ws.hpp"
using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;

class Worker
{
public:
	enum MsgBoxIcon {
		NoIcon = 0,		/* 没有图标 */
		Information = 1, 	/* 普通提示 */
		Warning = 2,		/* 警告图标 */
		Critical = 3,		/* 错误图标 */
		Question = 4		/* 疑问图标 */
	};

	static Worker *Instance();
	static void Destory();

	void Start(std::shared_ptr<WsClient::Connection> connection);
	void WSUiRoute(const nlohmann::json &msg);
	void WSSrvRoute(const nlohmann::json &msg);

private:
	Worker();
	~Worker();

	void sendMessage(const nlohmann::json &message);

private:
	static Worker* _This;
	std::shared_ptr<WsClient::Connection> _Connection;
};

#endif // WORKER_H
