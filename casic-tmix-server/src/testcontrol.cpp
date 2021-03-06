// global
#include "testcontrol.h"

TestControl *TestControl::_This = nullptr;
//global end

TestItem::TestItem(IDINT id)
    :_test_id(id){
    nlohmann::json iteminfo = MDBManager::Instance()->GetTestItem(this->_test_id);
    LOG(INFO) << "Get data from database" << iteminfo.dump();
    this->_test_type = iteminfo["test_type"];
    LOG(INFO) << "Get test type" ;
    this->_test_name = iteminfo["test_name"];
    LOG(INFO) << "Get test name" ;
    this->_test_key = iteminfo["test_key"];
    LOG(INFO) << "Get test key" ;
    this->_test_info = iteminfo["test_info"];
    LOG(INFO) << "Get test info" ;
    this->_test_standard = iteminfo["test_standard"];
    LOG(INFO) << "Get test standard" ;
    this->_test_start_prog = iteminfo["test_start_prog"];
    LOG(INFO) << "Get test start_prog" ;
    this->_test_stop_prog = iteminfo["test_stop_prog"];
    LOG(INFO) << "Get test stop_prog" ;
    // this->_test_select = iteminfo["test_select"];
    // LOG(INFO) << "Get test selected" ;
    LOG(INFO) << "Finish get test info";
    this->_test_select = true;// useless or duplicated, because if some TestItem instance has been created which means it had been selected already.
    this->_test_result = false;// pass or not pass
    this->_repaired = false;// variable only exists in mem not db
    this->_test_status = 0;
}

size_t TestItem::GetStatus(){
    this->_Lock.LockR();
    size_t status = this->_test_status;
    this->_Lock.UNLock();
    return status;
}

void TestItem::SetStarted(){
    this->_Lock.TryLockW();
    if (this->_test_status == 0){
        this->_test_status = 1;
    }
    else if (_test_status == 3){
        this->_test_status = 1;
        this->_repaired =1;
    }
    this->_Lock.UNLock();
}

void TestItem::SetResult(bool result){
    this->_Lock.TryLockW();
    if(this->_test_status == 1){
        if (result){
            this->_test_result = result;
            this->_test_status = 2;
        }
        else {
            this->_test_result = result;
            this->_test_status = 3;
        }
    }
    else if (this->_test_status == 3){
        if (result){
            this->_test_result = result;
            this->_test_status = 2;
            this->_repaired = 1;
        }
    }
    this->_Lock.UNLock();
}

bool TestItem::GetResult(){
    this->_Lock.LockR();
    nlohmann::json json_tmp = {
        {"test_status", this->_test_status},
        {"test_result", this->_test_result},
        {"test_repaired", this->_repaired}
    };
    this->_Lock.UNLock  ();
    return this->_test_result;
}

IDINT TestItem::GetTestID(){
    this->_Lock.LockR();
    IDINT id = this->_test_id;
    this->_Lock.UNLock();
    return id;
}

std::string TestItem::GetTestCMD(){
    this->_Lock.LockR();
    std::string cmd = this->_test_start_prog;
    this->_Lock.UNLock();
    return cmd;
}

int32_t TestItem::GetStandard(){
    this->_Lock.LockR();
    int32_t standard = this->_test_standard;
    this->_Lock.UNLock();
    return standard;
}

bool TestItem::GetRepaired(){
    this->_Lock.LockR();
    bool repair = this->_repaired;
    this->_Lock.UNLock();
    return repair;
}

std::string TestItem::GetTestKey(){
    this->_Lock.LockR();
    std::string key = this->_test_key;
    this->_Lock.UNLock();
    return key;
}

//TargetDEV:
std::string TargetDev::GetMac(){
    this->_Lock.LockR();
    std::string mac = this->_MAC;
    this->_Lock.UNLock();
    return mac;
}

std::string TargetDev::GetIP(){
    this->_Lock.LockR();
    std::string ipaddr = this->_IP;
    this->_Lock.UNLock();
    return ipaddr;
}

std::vector<TestItem> TargetDev::GetItemlist(){
    this->_Lock.LockR();
    std::vector<TestItem> list = this->_ItemList;
    this->_Lock.UNLock();
    return list;
}

std::vector<TestItem>::iterator TargetDev::GetCuritem(){
    this->_Lock.LockR();
    std::vector<TestItem>::iterator curitem = this->_Curitem;
    this->_Lock.UNLock();
    return curitem;
}

bool TargetDev::NextCuritem(){
    this->_Lock.TryLockW();
    TestItem tmpitem = *this->_Curitem;
    if (tmpitem.GetResult() == false){
        _ErrItemList.push_back(tmpitem);
    }
    this->UpdateDB();
    if (++this->_Curitem == this->_ItemList.end()){// work condition
        this->_Lock.UNLock();
        return false;
    }
    // this->_Curitem++;
    if (this->_Curitem->GetTestKey() == "reboot"){
        this->_Times = this->_Curitem->GetStandard();
        LOG(INFO) << this->GetMac() << "is going to Reboot " << this->_Times << " times";
    }
    this->_Lock.UNLock();
    return true;
}

IDINT TargetDev::GetCuritemID(){
    this->_Lock.LockR();
    auto tmpmid = this->GetCuritem();
    IDINT curid = (*tmpmid).GetTestID();
    this->_Lock.UNLock();
    return curid;
}

int32_t TargetDev::GetTimes(){
    this->_Lock.LockR();
    int32_t rtimes = this->_Times;
    this->_Lock.UNLock();
    return rtimes;
}

bool TargetDev::GetReady(){
    this->_Lock.LockR();
    bool testready = this->_Ready;
    this->_Lock.UNLock();
    return testready;
}

void TargetDev::UpdateDB_ALL(){// TODO update db for which mac-id pair exists
    this->_Lock.LockR();
    for (TestItem item : this->_ItemList){
        IDINT id = item.GetTestID();
        size_t status = item.GetStatus();
        bool result = item.GetResult();
        bool repair = item.GetRepaired();
        MDBManager::Instance()->SetStatus(id,this->GetMac(),status);
        MDBManager::Instance()->SetItemResult(id,this->GetMac(),result,repair);
    }
    this->_Lock.UNLock();
}

void TargetDev::UpdateDB(){
    this->_Lock.LockR();
    IDINT id = (*this->_Curitem).GetTestID();
    bool result = (*this->_Curitem).GetResult();// repair
    bool repair = (*this->_Curitem).GetRepaired();
    size_t status = (*this->_Curitem).GetStatus();
    LOG(INFO) << "Upload id: " << id << " Result: " << result << " Status: " << status;
    MDBManager::Instance()->SetStatus(id,this->_MAC,status);
    MDBManager::Instance()->SetItemResult(id,this->_MAC,result,repair);
    this->_Lock.UNLock();
}

void TargetDev::Reboot(){
    LOG(INFO) << "Start reboot";
    this->_Lock.TryLockW();// Lock fail!!!, try lock success, but lock fail
    LOG(INFO) << "Lock success";
    int32_t timesleft = this->_Times - 1;
    this->_Times = timesleft;
    LOG(INFO) << "Reboot remaining: " << this->_Times;
    this->_Lock.UNLock();
}

void TargetDev::finReboot(){
    this->_Lock.TryLockW();
    this->_Times = -1;
    this->_Lock.UNLock();
}

std::vector<TestItem> TargetDev::GetErrlist(){
    this->_Lock.LockR();
    std::vector<TestItem> errlist = this->_ErrItemList;
    this->_Lock.UNLock();
    return errlist;
}

TargetDev::TargetDev(std::string mac, std::string ipaddr)
    :_MAC(mac),_IP(ipaddr){
    LOG(INFO) << mac <<" Ready to init itemlist";
    this->_ItemList = this->InitItemlist();
    this->_Times = 0;
    // CurItem is not set during initiation;
    std::vector<TestItem>::iterator curitem;
    IDINT curid = MDBManager::Instance()->GetCurItemId(mac);
    for (curitem = this->_ItemList.begin();curitem != this->_ItemList.end();curitem++){
        if (curitem->GetTestID() == curid){
            this->_Curitem = curitem;
            break;
        }
    }
    std::vector<IDINT> idlist = MDBManager::Instance()->GetIDList();
        for (IDINT id : idlist){
            MDBManager::Instance()->NewResult(this->GetMac(), id);
        }
    LOG(INFO) << "Finish upload device: " << mac << " to database";
    this->_Ready = true;
    this->_Times = -1;
    this->_Alive = true;
}

std::vector<TestItem> TargetDev::InitItemlist(){
    std::vector<TestItem> retlist;
    try {
        std::vector<IDINT> idlist = MDBManager::Instance()->GetIDList();
        LOG(INFO) << "Get testids from database";
        for (IDINT id : idlist){
            TestItem testitem(id);
            retlist.push_back(testitem);
        }
        LOG(INFO) << "Generate testlist";
        return retlist;
    } catch (std::exception &e) {
        LOG(ERROR) << "load id list failed" << e.what();
        return retlist;
    }
}


//public
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


bool TestControl::Prepare(std::string ipaddr, nlohmann::json content)
{
   // check if client is ready
    if (this->_DevMap[ipaddr] && this->_DevMap[ipaddr]->GetReady()){
        return true;
    }
    else if (content.contains("MAC") && !content["MAC"].is_null()){
        LOG(INFO) << ipaddr << ": Ready";
        TargetDev* dev = new TargetDev(content["MAC"], ipaddr);
        this->_DevMap[ipaddr] = dev;// add ready device to device map
        LOG(INFO) << ipaddr <<" Add to TargetDEV list done";
        return true;
    }
    else {
        LOG(ERROR) << "Client device info not correct";
        LOG(ERROR) << "Check Ready failed from: " << ipaddr;
        return false;
    }
}

bool TestControl::isFresh(std::string ipaddr){
    LOG(INFO) << "Check if "<< ipaddr << "is a fresh start";
    bool ret = true;
    if (_DevMap.find(ipaddr) == _DevMap.end()){
        LOG(INFO) << "Fresh start from: " << ipaddr;
    }
    else if (_DevMap[ipaddr]->GetCuritemID() ==_DevMap[ipaddr]->GetItemlist().front().GetTestID()){
        LOG(INFO) << "Fresh start from: " << ipaddr;
    }
    else{
        ret = false;
    }
    return ret;
}

bool TestControl::isRebooting(std::string ipaddr){
    LOG(INFO) << "Check if " << this->_DevMap[ipaddr]->GetMac() << " is Rebooting";
    bool ret = false;
    int reboottimes = this->_DevMap[ipaddr]->GetTimes();
    if (reboottimes >= 0){
        LOG(INFO) << this->_DevMap[ipaddr]->GetMac() <<" is Rebooting";
        ret = true;
    }
    return ret;
}


nlohmann::json TestControl::Start(std::string ipaddr){
    nlohmann::json json_ret;
    if (isRebooting(ipaddr)){
        try {
            if (this->_DevMap[ipaddr]->GetTimes() == 0 &&
                    this->_DevMap[ipaddr]->GetCuritem()->GetTestKey()=="reboot"){
                this->_DevMap[ipaddr]->GetCuritem()->SetResult(true);
                json_ret = this->StartNextTest(ipaddr);
                this->_DevMap[ipaddr]->finReboot();
                return json_ret;
            }
            else {
                json_ret = {
                    {"Method", "Reboot"},
                    {"Content", ""}
                };
                this->_DevMap[ipaddr]->Reboot();
                return json_ret;
            }
        } catch (std::exception &e) {
            LOG(ERROR) << "Reboot error: " << e.what();
        }
    }
    else if (isFresh(ipaddr)){
        try {
            json_ret = FreshStart(ipaddr);
        } catch (std::exception &e) {
            LOG(ERROR) << "Start fresh test from" << ipaddr << "failed" <<e.what();
        }
    }
    else {// resume existing test routine
        try {
            LOG(INFO) << ipaddr <<" Try to resume test";

            json_ret = Resume(ipaddr);
        } catch (std::exception &e) {
            LOG(ERROR) << "Resume test for "
                       << this->_DevMap[ipaddr]->GetMac()
                       << " failed" <<e.what();
        }
    }
    return json_ret;
}

nlohmann::json TestControl::FreshStart(std::string ipaddr){
    auto mid_tmp = this->_DevMap[ipaddr]->GetItemlist();
    nlohmann::json idlist;
    for (TestItem testitem : mid_tmp){
        nlohmann::json json_tmp = {
            {"test_id", testitem.GetTestID()},
            {"test_prog_start", testitem.GetTestCMD()}
        };
        idlist.push_back(json_tmp);
    }
    nlohmann::json json_ret = {
        { "Method", "Start" },
        { "Content", idlist}
    };
    return json_ret;
}

nlohmann::json TestControl::Resume(std::string ipaddr){// ERROR
    LOG(INFO) << "Resuming";
    auto list = this->_DevMap[ipaddr]->GetItemlist();
    auto itlist = this->_DevMap[ipaddr]->GetCuritem();
    if (itlist == list.end()){
        nlohmann::json json_ret = {
            { "Method", "Stop" },
            { "Content", ""}
        };
        return json_ret;
    }
    nlohmann::json idlist;
    while (++itlist != list.end()){
        nlohmann::json json_tmp = {
            {"test_id", itlist->GetTestID()},
            {"test_prog_start", itlist->GetTestCMD()}
        };
        idlist.push_back(json_tmp);
    }
    nlohmann::json json_ret = {
        { "Method", "Start" },
        { "Content", idlist}
    };
    return json_ret;
}

bool TestControl::SetStarted(std::string ipaddr, nlohmann::json content){
    if (!content.contains("test_id")||content["test_id"].is_null()
            ||!content["test_id"].is_number()){return false;}
    try {
        IDINT testid = content["test_id"];
        if (testid == this->_DevMap[ipaddr]->GetCuritemID()){
            (*this->_DevMap[ipaddr]->GetCuritem()).SetStarted();
            LOG(INFO) << ipaddr <<": Set curitem started";
            return true;
        }
        else
            return false;
    } catch (nlohmann::detail::type_error &e) {
        LOG(ERROR) << e.what();
        return false;
    }
}

// void TestControl::Stop(std::string ipaddr){}

nlohmann::json TestControl::ItemResults(std::string ipaddr)
{
    nlohmann::json results;
    for (IDINT id : MDBManager::Instance()->GetIDList()){
        bool result = MDBManager::Instance()->GetItemResult(id, this->_DevMap[ipaddr]->GetIP());
        nlohmann::json tmp_json = {
            {"test_id", id},
            {"test_result", result}};
        results.push_back(tmp_json);
    }
    return results;
}

bool TestControl::SetItemResult(std::string ipaddr, const nlohmann::json content){
    bool ret = false;
    LOG(INFO) << "SetItemResult: " << ipaddr;
    if (content.contains("test_id") && content.contains("test_result")){
        if (content["test_id"].is_number() && content["test_result"].is_boolean()){
            LOG(INFO) << "Result from: " << ipaddr << " format right";
            IDINT id = content["test_id"];
            bool result = content["test_result"];
            if (id == this->_DevMap[ipaddr]->GetCuritemID()){
                LOG(INFO) << "Result from: " << ipaddr << " content right";
                this->_DevMap[ipaddr]->GetCuritem()->SetResult(result);
                LOG(INFO) << "Result from: " << ipaddr << " Set: "<< result;
                //this->_DevMap[ipaddr]->UpdateDB();
                //LOG(INFO) << "Upload: " << ipaddr << " result to database";
                ret = true;
            }
        }
    }
    return ret;
}

nlohmann::json TestControl::StartNextTest(std::string ipaddr){
    this->_Lock.TryLockW();
    if (!this->_DevMap[ipaddr]->NextCuritem()){
        // reach the end of testlist, respond a finish confirmation message
        nlohmann::json tmp_json = {
            {"Method", "Finish"},
            {"Content", ""}
        };
        return tmp_json;
    }
    IDINT id = this->_DevMap[ipaddr]->GetCuritemID();
    std::string method = "NextStart";
    nlohmann::json tmp_json = {
        {"Method",method},
        {"Content",{"test_id",id}}
    };
    this->_Lock.UNLock();
    return tmp_json;
}

TestControl::TestControl(){}

TestControl::~TestControl(){}

std::string TestControl::GetSystime(){
    LOG(INFO) << "Getting system time";
    auto now = std::chrono::system_clock::now();
    time_t curtime = std::chrono::system_clock::to_time_t(now);
    std::string timestr = std::ctime(&curtime);
    return timestr;
}


nlohmann::json TestControl::ItemList()
{
    this->_Lock.LockR();
    nlohmann::json tmpjson = MDBManager::Instance()->GetTestList();
    this->_Lock.UNLock();
    return tmpjson;
}
