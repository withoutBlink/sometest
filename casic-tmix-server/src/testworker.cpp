#include "testworker.h"

#ifdef __cplusplus
extern "C"  {
#endif

#include <unistd.h>
#include <sys/types.h>

#ifdef __cplusplus
}
#endif

#include "fmt/format.h"
#include "nlohmann/json.hpp"
#include "easylog/easylogging++.h"
#include "utils/softwareabout.h"
#include "src/wssrvroute.h"
#include "src/config.h"

TestControl *TestControl::_This = nullptr;

TestControl *TestControl::Instance()
{
	if (!_This) {
        _This = new TestControl;
	}
	return _This;
}

void TestControl::Destory()
{
	if (_This) {
		delete _This;
		_This = nullptr;
	}
}

void TestControl::Reload()
{
	if (Config::Instance()->Item.GetStarted()) {
		this->Start();
	}
}

nlohmann::json TestControl::Start()
{
	nlohmann::json json = {
		{ "Method", "Started" },
		{ "Content", Config::Instance()->Item.ItemList() }
	};
    Config::Instance()->Item.SetStarted(true);
    this->itemStart();
}

nlohmann::json TestControl::GetItemConf()
{
	nlohmann::json json = {
		{ "Method", "ItemConf" },
		{ "Content", Config::Instance()->Item.CurItem() }
	};
    return json;
}

nlohmann::json TestControl::ItemResult(const nlohmann::json &msg)
{
	nlohmann::json curitem = Config::Instance()->Item.CurItem();
    int rescode = msg["Result"]["Status"].get<bool>() ? 1 : 2;// test pass or not pass
    curitem["Result"] = rescode;
	Config::Instance()->Item.SetCurResult(rescode);
	nlohmann::json json = {
		{ "Method", "ItemResult" },
		{ "Content", curitem }
	};
    WSSrvRoute::Instance()->SendMsgToUI(json.dump());

//	json.clear();
//	json = {
//		{ "Method", "ItemClose" },
//		{ "Content", "" }
//	};
//	WSSrvRoute::Instance()->SendMsgToItem(json.dump());

//    this->itemStop();
//    if (this->itemNext()) {
//        this->itemStart();
//    }
}

TestControl::TestControl()
{
}

TestControl::~TestControl()
{

}

bool TestControl::itemNext()
{
	return Config::Instance()->Item.NextItem();
}

void TestControl::itemStart()
{
	nlohmann::json json = {
		{ "Method", "ItemResult" },
		{ "Content", Config::Instance()->Item.CurItem() }
	};
	json["Content"]["Result"] = 3;
    // WSSrvRoute::Instance()->SendMsgToUI(json.dump());
	this->_WorkThread = new std::thread([=](){
		try {
			LOG(DEBUG) << Config::Instance()->Item.CurItem();
			std::string cmd = fmt::format("{0}/{1}", SOFTWARE_PATH_BIN, Config::Instance()->Item.CurItem()["Exec"].get<std::string>());
			std::system(cmd.c_str());
		}  catch (std::exception &e) {
			LOG(ERROR) << e.what();
		}
	});
}

void TestControl::itemStop()
{
	if (this->_WorkThread) {
		this->_WorkThread->join();
		delete this->_WorkThread;
		this->_WorkThread = nullptr;
	}
}



