#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <mutex>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

#include "nlohmann/json.hpp"
#include "fmt/format.h"
#include "easylog/easylogging++.h"
#include "utils/softwareabout.h"
#include "src/wssrvroute.h"
#include "src/config.h"
#include "src/mdbmanager.h"

#ifdef __cplusplus
extern "C"  {
#endif

#include <unistd.h>
#include <sys/types.h>

#ifdef __cplusplus
}
#endif


class TestItem
{
public:
    TestItem(IDINT id);
    ~TestItem();

    size_t GetStatus();
    void SetStarted();
    IDINT GetTestID();
    std::string GetTestKey();
    bool SetResult(bool result);
    nlohmann::json GetCurResult();

private:
    RWLock _Lock;
    IDINT _test_id;// same as document described, MAC as id
    size_t _test_type;
    std::string _test_name;
    std::string _test_key;
    std::string _test_info;
    std::string _test_standard;
    std::string _test_start_prog;
    std::string _test_stop_prog;
    bool _test_select = false;
    bool _Result = false;
    bool _Repaired = false;
    size_t _Status;//ready=0, running=1, finished=2, error=3
};

class TargetDev
{
public:

    std::string GetMac();
    std::string GetIP();
    std::vector<TestItem> GetItemlist();
    std::vector<TestItem>::iterator GetCuritem();
    std::vector<TestItem> GetErrlist();

    TargetDev(std::string mac, std::string ipaddr);
    ~TargetDev();

private:
    std::vector<TestItem> InitItemlist();
private:
    RWLock _Lock;
    std::string _MAC;
    std::string _IP;
    std::vector<TestItem> _ItemList;
    std::vector<TestItem>::iterator _Curitem;
    std::vector<TestItem> _ErrItemList;
};

class TestControl
{
public:
    static TestControl *Instance();
	static void Destory();

    std::string GetSystime(); // send system time to client for time settings
    nlohmann::json GetItemConf();// get test list itemconf from database
    bool Start(std::string ipaddr, nlohmann::json content); // start specific machine test process
    bool SetStarted(std::string ipaddr, nlohmann::json content);// set test status 1
    void Stop(std::string ipaddr);// stop specific machine test process
    float Status(std::string ipaddr);// check test complete ratio
    nlohmann::json ItemList(std::string ipaddr);
    TestItem* CurItem(std::string ipaddr);
    nlohmann::json ItemResults(std::string ipaddr);// get specific machine test result from database
    bool SetItemResult(const nlohmann::json& msg);

    void Task(std::string cmd);
    void Reload();

private:
    TestControl();
    ~TestControl();

    bool CheckReady(nlohmann::json content, std::string ipaddr);// check client machine if it is ready
    void SetItemConf(nlohmann::json conf);
    void AddDev(TargetDev dev);// bind connection remote ip address with MAC address, write to _MACbind
    void ReleaseDev(TargetDev dev);// release binding after test error or interuption


private:
    static TestControl *_This;
    RWLock _Lock;
    std::map<std::string, TargetDev> _DevMap;// ipaddr and targetdev map
};

#endif // TESTCONTROL_H
