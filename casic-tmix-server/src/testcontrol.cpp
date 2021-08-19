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
}

size_t TestItem::GetStatus(){
    this->_Lock.LockR();
    size_t status = this->_Status;
    this->_Lock.UNLock();
    return status;
}

void TestItem::SetStarted(){
    this->_Lock.LockW();
    if (this->_Status == 0){
        this->_Status = 1;
    }
    else if (_Status == 3){
        this->_Status = 1;
        this->_Repaired =1;
    }
    this->_Lock.UNLock();
}

void TestItem::SetResult(bool result){
    this->_Lock.LockW();
    if(this->_Status == 1){
        if (result){
            this->_Result = result;
            this->_Status = 2;
        }
        else {
            this->_Result = result;
            this->_Status = 3;
        }
    }
    else if (this->_Status == 3){
        if (result){
            this->_Result = result;
            this->_Status = 2;
            this->_Repaired = 1;
        }
    }
    this->_Lock.UNLock();
}

bool TestItem::GetResult(){
    this->_Lock.LockR();
    nlohmann::json json_tmp = {
        {"test_status", this->_Status},
        {"test_result", this->_Result},
        {"test_repaired", this->_Repaired}
    };
    this->_Lock.UNLock  ();
    return this->_Result;
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

void TargetDev::SetNextitem(){//DOING
    this->_Lock.LockW();
    TestItem tmpitem = *this->_Curitem;
    if (tmpitem.GetResult() == false){
        _ErrItemList.push_back(tmpitem);
    }
    this->UpdateDB();
    this->_Curitem++;
    this->_Lock.UNLock();
}

IDINT TargetDev::GetCuritemID(){
    auto tmpmid = this->GetCuritem();
    IDINT curid = (*tmpmid).GetTestID();
    return curid;
}

void TargetDev::UpdateDB_ALL(){// TODO update depend on mac-id pair exists
    this->_Lock.LockR();
    for (TestItem item : this->_ItemList){
        IDINT id = item.GetTestID();
        size_t status = item.GetStatus();
        bool result = item.GetResult();
        MDBManager::Instance()->SetStatus(id,this->GetMac(),status);
        MDBManager::Instance()->SetItemResult(id,this->GetMac(),result);
    }
    this->_Lock.UNLock();
}

void TargetDev::UpdateDB(){
    this->_Lock.LockR();
    IDINT id = (*this->_Curitem).GetTestID();
    bool result = (*this->_Curitem).GetResult();// repair
    size_t status = (*this->_Curitem).GetStatus();
    LOG(INFO) << "Upload id: " << id << " Result: " << result << " Status: " << status;
    MDBManager::Instance()->SetStatus(id,this->_MAC,status);
    MDBManager::Instance()->SetItemResult(id,this->_MAC,result);
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
   if (content.contains("MAC") && !content["MAC"].is_null()){
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

nlohmann::json TestControl::Start(std::string ipaddr){
    nlohmann::json json_ret;
    if (isFresh(ipaddr)){
        try {
            json_ret = FreshStart(ipaddr);
        } catch (std::exception &e) {
            LOG(ERROR) << "Start fresh test from" << ipaddr << "failed" <<e.what();
        }
    }
    else {
        try {
            LOG(INFO) << ipaddr <<"Try to resume test";
            json_ret = Resume(ipaddr);
        } catch (std::exception &e) {
            LOG(ERROR) << "Resume test from" << ipaddr << "failed" <<e.what();
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

nlohmann::json TestControl::Resume(std::string ipaddr){
    auto list = this->_DevMap[ipaddr]->GetItemlist();
    auto itlist = this->_DevMap[ipaddr]->GetCuritem();
    nlohmann::json idlist;
    while (itlist != list.end()){
        nlohmann::json json_tmp = {
            {"test_id", (*itlist).GetTestID()},
            {"test_prog_start", (*itlist).GetTestCMD()}
        };
        ++itlist;
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
                (*this->_DevMap[ipaddr]->GetCuritem()).SetResult(result);
                LOG(INFO) << "Result from: " << ipaddr << " Set: "<< result;
                this->_DevMap[ipaddr]->UpdateDB();
                LOG(INFO) << "Upload: " << ipaddr << " result to database";
                ret = true;
            }
        }
    }
    return ret;
}

void TestControl::NextTest(std::string ipaddr){
    this->_Lock.LockW();
    this->_DevMap[ipaddr]->SetNextitem();
    this->_Lock.UNLock();
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
