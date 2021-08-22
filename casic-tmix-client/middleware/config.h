#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "utils/softwareabout.h"

class GlobalData
{
public:
	GlobalData()
		: Port(PORT_SERVICE)
//		, PortServerHTTP(PORT_SERVER_HTTP)
//		, PortServerWS(PORT_SERVER_WS)
//		, PortService(PORT_SERVICE)
//		, ErrIntereupt(true)
//		, ErrRepetitionCount(3)
//		, ErrRepetitionTime("after_current_group")
	{

	}

	int Port;
//	int PortScanServer;
//	int PortServerHTTP;
//	int PortServerWS;
//	int PortService;
//	bool ErrIntereupt;
//	int ErrRepetitionCount;
//	std::string ErrRepetitionTime;
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
