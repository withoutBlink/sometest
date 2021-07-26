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


class TestItem
{
public:
	TestItem();
	~TestItem();

	bool GetStarted();
	bool SetStarted(bool start);

	nlohmann::json ItemList();
	nlohmann::json CurItem();
	bool SetCurResult(uint result);
	bool NextItem();

private:
	RWLock _Lock;
	std::size_t _CurItem;
	std::vector<std::size_t> _GroupErrList;
};


class Config
{
public:
	static Config *Instance();
	static void Destory();

	GlobalData Data;
	TestItem Item;

private:
	Config();
	~Config();

	void parse();

private:
	static Config *_This;
};

#endif // CONFIG_H
