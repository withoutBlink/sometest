#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <mutex>

#include "src/rwlock.h"
#include "utils/softwareabout.h"

#include "nlohmann/json.hpp"
//#include "thread/thread.hpp"

class GlobalData
{
public:
	GlobalData()
		: PortScanServer(PORT_SCANSRV)
		, PortServerHTTP(PORT_SERVER_HTTP)
		, PortServerWS(PORT_SERVER_WS)
		, PortService(PORT_SERVICE)
		, ErrIntereupt(true)
		, ErrRepetitionCount(3)
		, ErrRepetitionTime("after_current_group"){}

	std::string IP;
	int PortScanServer;
	int PortServerHTTP;
	int PortServerWS;
	int PortService;
    bool ErrIntereupt;
	int ErrRepetitionCount;
	std::string ErrRepetitionTime;
};





class Config
{
public:
	static Config *Instance();
	static void Destory();

	GlobalData Data;

private:
	Config();
	~Config();

	void parse();

private:
	static Config *_This;
};

#endif // CONFIG_H
