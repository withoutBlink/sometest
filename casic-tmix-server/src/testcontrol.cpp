// global
#include "testcontrol.h"

TestControl *TestControl::_This = nullptr;
//global end

TestItem::TestItem(IDINT id)
    :_test_id(id){
    nlohmann::json iteminfo = MDBManager::Instance()->GetTestItem(this->_test_id);
    LOG(INFO) << "Get test info from database" << iteminfo.dump();
    this->_test_type = iteminfo["test_type"];
    this->_test_name = iteminfo["test_name"];
    this->_test_key = iteminfo["test_key"];
    this->_test_info = iteminfo["test_info"];
    this->_test_standard = iteminfo["test_standard"];
    this->_test_start_prog = iteminfo["test_start_prog"];
    this->_test_stop_prog = iteminfo["test_stop_porg"];
    this->_test_select = iteminfo["test_select"];
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
    if ( this->_Status == 0){
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

nlohmann::json TestItem::GetResult(){
    this->_Lock.LockR();
    nlohmann::json json_tmp = {
        {"test_id", this->_test_id},
        {"test_result", this->_Result},
        {"test_repaired", this->_Repaired}
    };
    this->_Lock.UNLock  ();
    return json_tmp;
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

IDINT TargetDev::GetCuritemID(){
    auto tmpmid = this->GetCuritem();
    IDINT curid = (*tmpmid).GetTestID();
    return curid;
}

std::vector<TestItem> TargetDev::GetErrlist(){
    this->_Lock.LockR();
    std::vector<TestItem> errlist = this->_ErrItemList;
    this->_Lock.UNLock();
    return errlist;
}

TargetDev::TargetDev(std::string mac, std::string ipaddr)
    :_MAC(mac),_IP(ipaddr){
    LOG(INFO) << "Ready to init itemlist";
    this->_ItemList = this->InitItemlist();
    LOG(INFO) << this->_ItemList.front().GetTestID();
    std::vector<TestItem>::iterator curitem;
    IDINT curid = MDBManager::Instance()->GetCurItemId(mac);
    for (curitem = this->_ItemList.begin();curitem != this->_ItemList.end();curitem++){
        if (curitem->GetTestID() == curid){
            this->_Curitem = curitem;
            break;
        }
    }
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

bool TestControl::Reload(){ return false; }

bool TestControl::Prepare(std::string ipaddr, nlohmann::json content)
{
   LOG(INFO) << "Starting preparation for: " << ipaddr <<":" << content["MAC"];
   if (content.contains("MAC") && !content["MAC"].is_null()){
       LOG(INFO) << ipaddr << ": Ready";
       try {
           TargetDev * dev = new TargetDev(ipaddr, content["MAC"]);
           this->_DevMap[ipaddr] = dev;// add ready device to device map
       } catch (std::exception &e) {
           LOG(ERROR) << e.what();
       }
       LOG(INFO) << ipaddr <<" Add to TargetDEV list";
   }
   else {
       LOG(ERROR) << "CheckReady Fault";
   }
   if(this->CheckReady(content, ipaddr)){LOG(INFO) << "Ready to start from: " << ipaddr;return true;}//check if client is ready
   // check if db is ready
   LOG(ERROR) << "Check Ready failed from: " << ipaddr;
   return false;
}

bool TestControl::isFresh(std::string ipaddr){
    TargetDev* targetdev = this->_DevMap[ipaddr];
    IDINT curid = targetdev->GetCuritemID();
    IDINT firstid = this->_DevMap[ipaddr]->GetItemlist().front().GetTestID();
    if (curid == firstid){LOG(INFO) << "Fresh start from: " << ipaddr;return true;}
    else {return false;}
}

nlohmann::json TestControl::Start(std::string ipaddr){
    nlohmann::json json_ret;
    if (/* DISABLES CODE */ (true)){//isFresh(ipaddr)){
        try {
            json_ret = FreshStart(ipaddr);
        } catch (std::exception &e) {
            LOG(ERROR) << "Start fresh test from" << ipaddr << "failed" <<e.what();
        }

    }
    else {
        try {
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
    if (content["test_id"].is_null()){return false;}
    IDINT testid = content["test_id"];
    MDBManager::Instance()->SetStatus(testid, this->_DevMap[ipaddr]->GetMac(),2);
    return true;
}

void TestControl::Stop(std::string ipaddr){}

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

bool TestControl::SetItemResult(std::string ipaddr, const nlohmann::json& msg){
    bool ret = false;
    if (!msg["Content"]["Result"].is_null()){
        if (msg["Content"]["Result"]["test_id"].is_number() && msg["Content"]["Result"]["test_result"].is_boolean()){
            IDINT id = msg["Content"]["Result"]["test_id"];
            bool result = msg["Content"]["Result"]["test_result"];
            (*this->_DevMap[ipaddr]->GetCuritem()).SetResult(result);
            // MDBManager::Instance()->SetItemResult(id, this->_DevMap[ipaddr].GetMac(), result);
            ret = true;
        }
    }
    return ret;
}

TestControl::TestControl(){}

TestControl::~TestControl(){}

std::string TestControl::GetSystime(){
    auto now = std::chrono::system_clock::now();
    time_t curtime = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&curtime);
}

bool TestControl::CheckReady(nlohmann::json content, std::string ipaddr){

}

nlohmann::json TestControl::ItemList(std::string ipaddr)
{
    this->_Lock.LockR();
    std::string MAC = this->_DevMap[ipaddr]->GetMac();
    nlohmann::json tmpjson = MDBManager::Instance()->GetTestList();
    this->_Lock.UNLock();
    return tmpjson;
}
