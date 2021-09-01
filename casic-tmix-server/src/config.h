#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <mutex>

#include "src/rwlock.h"
#include "utils/softwareabout.h"
#include "nlohmann/json.hpp"
#include "easylog/easylogging++.h"
#include "src/mdbmanager.h"


class Config
{
public:
	static Config *Instance();
	static void Destory();
    ushort GetServicePort();


private:
	Config();
	~Config();
    void LoadConf();


private:
	static Config *_This;
    std::string ServerIP;
    int PortScanServer;
    int PortServerHTTP;
    int PortServerWS;
    ushort PortService;
    bool ErrIntereupt;
    int ErrRepetitionCount;

};

#endif // CONFIG_H
