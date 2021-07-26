#include <iostream>

#include "worker.h"

#include "utils/softwareabout.h"

#include "easylog/easylogging++.h"
INITIALIZE_EASYLOGGINGPP

#include "webserver/client_ws.hpp"
using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;


/**
 * @brief InitLog - 设置日志格式
 */
void InitLog()
{
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.setGlobally(el::ConfigurationType::ToFile, "true");
	defaultConf.setGlobally(el::ConfigurationType::Enabled, "true");
	defaultConf.setGlobally(el::ConfigurationType::Filename, SOFTWARE_PATH_LOG_TESTITEM);
	defaultConf.setGlobally(el::ConfigurationType::Format, "[%datetime | %level] %loc : %msg");
	defaultConf.setGlobally(el::ConfigurationType::MaxLogFileSize, "20971520");
	defaultConf.setGlobally(el::ConfigurationType::LogFlushThreshold, "1");
	el::Loggers::reconfigureAllLoggers(defaultConf);
}


int main()
{
	InitLog();

	WsClient wsclient(WS_URL_ITEMS);

	wsclient.on_open = [](std::shared_ptr<WsClient::Connection> connection) {
		LOG(INFO) << "Items Client: Opened connection";
		Worker::Instance()->Start(connection);
	};

	wsclient.on_message = [](std::shared_ptr<WsClient::Connection> connection, std::shared_ptr<WsClient::Message> message) {
		auto msg = message->string();
		LOG(DEBUG) << "\n>>>>> Items Message received <<<<<\n"
				      "from:\n"
				   << connection.get()
				   << "\ncontent:\n"
				   << msg
				   << "\n------------------------------";
		try {
			nlohmann::json request = nlohmann::json::parse(msg);

			nlohmann::json &content = request["Content"];
			std::string method = request["Method"].get<std::string>();
			if (method == "RecvCallUI") {
				Worker::Instance()->WSUiRoute(content);
			} else if (method == "RecvCallSvc") {
				Worker::Instance()->WSSrvRoute(content);
			} else if (method == "RecvClose") {
				Worker::Destory();
				connection->send_close(0);
			}
		} catch (std::exception &e) {
			LOG(WARNING) << e.what();
		}
	};

	wsclient.on_close = [](std::shared_ptr<WsClient::Connection> /*connection*/,
			int status, const std::string & /*reason*/) {
		LOG(INFO) << "Items Client: Closed connection with status code " << status;
	};

	wsclient.on_error = [](std::shared_ptr<WsClient::Connection> /*connection*/,
			const SimpleWeb::error_code &ec) {
		LOG(INFO) << "Items Client: Error: " << ec << ", error message: " << ec.message();
	};

	wsclient.start();
	return 0;
}
