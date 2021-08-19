#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <mutex>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <algorithm>

#include "nlohmann/json.hpp"
#include "fmt/format.h"
#include "easylog/easylogging++.h"
#include "utils/softwareabout.h"
#include "src/wssroute.h"
#include "src/config.h"
#include "src/mdbmanager.h"
#include "format.h"

#ifdef __cplusplus
extern "C"  {
#endif

#include <unistd.h>
#include <sys/types.h>

#ifdef __cplusplus
}
#endif


class TestItem
{ // determine test results and status internal logic
public:
    TestItem(IDINT id);
    // ~TestItem();

    size_t GetStatus();
    void SetStarted();
    void SetResult(bool result);
    bool GetResult();
    IDINT GetTestID();
    std::string GetTestKey();
    std::string GetTestCMD();


private:
    RWLock _Lock;
    IDINT _test_id;// same as document described, MAC as id
    size_t _test_type;// define wether the procedure is interactive, and determine the item is belong to function test group or performance group
    std::string _test_name;
    std::string _test_key;
    std::string _test_info;
    std::string _test_standard;
    std::string _test_start_prog;// cmd to start test
    std::string _test_stop_prog;// some how useless, because we use some brutal way to do it
    bool _test_select = true;// some how useless, because if some TestItem instance has been created which means it had been selected already.
    bool _Result = false;// pass or not pass
    bool _Repaired = false;// variable only exists in mem not db
    size_t _Status = 0;// ready=0, running=1, finished=2, error=3, vairable
};

class TargetDev
{ // establish connection between test items and test device, manage test result upload to db
public:
    std::string GetMac();
    std::string GetIP();
    std::vector<TestItem> GetItemlist();
    std::vector<TestItem>::iterator GetCuritem();
    void SetNextitem();
    IDINT GetCuritemID();

    void UpdateDB_ALL();// update items already exists
    void UpdateDB();
    void UpdateDB(IDINT id);

    std::vector<TestItem> GetErrlist();

    TargetDev(std::string mac, std::string ipaddr);

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
{ // manage the whole test procedure
public:
    static TestControl *Instance();
	static void Destory();

    std::string GetSystime(); // send system time to client for time settings
    bool Prepare(std::string ipaddr, nlohmann::json content);// preparation before start test
    nlohmann::json Start(std::string ipaddr);// start specific machine test process
    bool SetStarted(std::string ipaddr, nlohmann::json content);// set test status 1
    void Stop(std::string ipaddr);// stop specific device test process
    float Status(std::string ipaddr);// check test complete ratio, TODO
    nlohmann::json ItemList();// return a minimal version of test list, used for task distribution
    nlohmann::json ItemResults(std::string ipaddr);// get specific device test result from database
    bool SetItemResult(std::string ipaddr, const nlohmann::json content);// process result uploaded by client
    void NextTest(std::string ipaddr);
    bool Reload(std::string ipaddr);// reload test process for specific device

    //For program testing

private:
    TestControl();
    ~TestControl();

    bool isFresh(std::string ipaddr);// get test list itemconf from database
    nlohmann::json FreshStart(std::string ipaddr);// fresh start a new test
    nlohmann::json Resume(std::string ipaddr);// start from last saved
    bool CheckReady(nlohmann::json content, std::string ipaddr);// check client if it is ready
    void SetItemConf(nlohmann::json conf);// reverted interface for init test list according to messages from web
    void AddDev(TargetDev dev);// bind connection remote ip address with MAC address, write to _MACbind
    void ReleaseDev(TargetDev dev);// release binding after test error or interuption


private:
    static TestControl *_This;
    RWLock _Lock;
    std::map<std::string, TargetDev*> _DevMap;// ipaddr and targetdev map
};

#endif // TESTCONTROL_H
