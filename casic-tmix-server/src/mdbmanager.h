#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "nlohmann/json.hpp"
#include "utils/softwareabout.h"
#include "easylog/easylogging++.h"
#include "testcontrol.h"

#include <vector>
#include <mutex>
#include <iostream>
#include <cstring>
#include <mariadb/conncpp.hpp>

#define IDINT u_int16_t

class MDBManager
{
public:
    static MDBManager *Instance();
    // ID for test item primary key
    // MAC for test machine primary key
    bool InitDB();// Init database include itemlist table and result_%startdatetime table
    bool TestListChk();// Init itemlist table
    bool ResultListChk();// create new result table in database include selected test and sort by index

    bool SetTestList(std::vector<IDINT> config);// config is test id array

    // testlist
    nlohmann::json GetAllTest();
    nlohmann::json GetTestList();// send this to client for task init, keep the same to all machines being tested
    bool InsertItem(nlohmann::json newitem);// add item to testlist
    nlohmann::json GetTestItem(IDINT id);// get testitem info

    // results
    IDINT GetCurItemId(std::string MAC);// which test item status is 2
    bool SetStatus(IDINT id, std::string MAC, u_int8_t status);// 0: not tested, 1: tested, 2: testing, 3: error
    bool SetItemResult(IDINT id, std::string MAC, bool result);// 0: not pass, 1: pass
    bool GetItemResult(IDINT id, std::string MAC);



private:
    MDBManager();
    ~MDBManager();


    std::vector<IDINT> GetIDList();// sort itemlist table by test_index, return sorted ids
    std::string GetItemCMD(IDINT id);
    // std::string GetItemStop(IDINT id);
    u_int8_t GetStatus(IDINT id, std::string MAC);
    // for error
    void errSetpass(IDINT id, std::string MAC);
    void errSeterr(IDINT id, std::string MAC);


private:
    static MDBManager *_This;
    std::unique_ptr<sql::Connection> _Conn;
	std::mutex _Mutex;
    std::string _ResultTable;// result table name
};

#endif // DBMANAGER_H
