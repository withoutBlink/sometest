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

	void Config(const nlohmann::json &msg);

	void WSUiRoute(const nlohmann::json &msg);
	void WSSrvRoute(const nlohmann::json &msg);

private:
	Worker();
	~Worker();

	void callInput(const std::string& title,
		       const std::string& text,
		       const std::string& validator);
	std::string recvInput(const nlohmann::json& msg);

	void sendMessage(const nlohmann::json &message);
	std::string getValueFromConf(const std::string &key);

	/**
	 * @brief getbhdc - 获取华虹版本
	 */
	std::string getBHDC();
	std::string getBHDC(const std::string& devnode);


	std::string findDevNode(const std::string &mountpoint);
	std::string getOSDevNode();
	std::string getHomeDevNode();
	std::string getHdFwRecv();

    std::string shellCmd(const std::string &cmd);
    std::string getPackageVer(const std::string &packname);


private:
	static Worker* _This;
	int _CurDialogId;
	nlohmann::json _CurItemConf;
	std::shared_ptr<WsClient::Connection> _Connection;
};

#endif // WORKER_H
