#include <iostream>

#include "src/config.h"
#include "utils/hardwarefreak.h"
#include "src/wssroute.h"
#include "webserver/server_ws.hpp"
using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

#include "easylog/easylogging++.h"
INITIALIZE_EASYLOGGINGPP

/**
 * @brief InitLog - 设置日志格式
 */
void InitLog()
{
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.setGlobally(el::ConfigurationType::ToFile, "true");
	defaultConf.setGlobally(el::ConfigurationType::Enabled, "true");
	defaultConf.setGlobally(el::ConfigurationType::Filename, SOFTWARE_PATH_LOG_SERVICE);
	defaultConf.setGlobally(el::ConfigurationType::Format, "[%datetime | %level] %loc : %msg");
	defaultConf.setGlobally(el::ConfigurationType::MaxLogFileSize, "20971520");
	defaultConf.setGlobally(el::ConfigurationType::LogFlushThreshold, "1");
	el::Loggers::reconfigureAllLoggers(defaultConf);
}

int main()
{
	InitLog();

//	MonitorTemp monitortemp;
//	monitortemp.Start();

	WsServer service;
	service.config.port = Config::Instance()->Data.PortService;
	service.config.thread_pool_size = std::thread::hardware_concurrency();

	auto &uiroute = service.endpoint[std::string("^") + WS_URL_SVCUI + std::string("?$")];
	WSSRoute::Instance()->Init(uiroute);

	auto &itemsroute = service.endpoint[std::string("^") + WS_URL_SVCITEMS + std::string("?$")];
	WSSRoute::Instance()->Init(itemsroute);

	LOG(INFO) << "Service Start: " << service.config.address << ":" << service.config.port;

	service.start();

//	monitortemp.Stop();

	return 0;
}
