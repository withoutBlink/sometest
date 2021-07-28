// global
#include "testcontrol.h"

TestControl *TestControl::_This = nullptr;
//global end


TestItem::TestItem(IDINT id)
    :_test_id(id){
    nlohmann::json iteminfo = MDBManager::Instance()->GetTestItem(this->_test_id);
    this->_test_type = iteminfo["test_type"];
    this->_test_name = iteminfo["test_name"];
    this->_test_key = iteminfo["test_key"];
    this->_test_info = iteminfo["test_info"];
    this->_test_standard = iteminfo["test_standard"];
    this->_test_start_prog = iteminfo["test_start_prog"];
    this->_test_stop_prog = iteminfo["test_stop_porg"];
    this->_test_select = iteminfo["test_select"];
}

TestItem::~TestItem(){}

size_t TestItem::GetStatus(){
    this->_Lock.LockR();
    size_t status = this->_Status;
    this->_Lock.UNLock();
    return status;
}

void TestItem::SetStarted(){
    this->_Lock.LockW();
    this->_Status = 1;
    this->_Lock.UNLock();
}

IDINT TestItem::GetTestID(){
    this->_Lock.LockR();
    IDINT id = this->_test_id;
    this->_Lock.UNLock();
    return id;
}

std::string TestItem::GetTestKey(){
    this->_Lock.LockR();
    std::string key = this->_test_key;
    this->_Lock.UNLock();
    return key;
}

bool TestItem::SetResult(bool result){
    this->_Lock.LockW();
    if (this->_Status == 3 && result == true){
        this->_Repaired = true;
        this->_Result = true;
    }else {
        this->_Result = result;
        this->_Lock.UNLock();
    }
    return this->_Result;
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

std::vector<TestItem> TargetDev::GetErrlist(){
    this->_Lock.LockR();
    std::vector<TestItem> errlist = this->_ErrItemList;
    this->_Lock.UNLock();
    return errlist;
}

TargetDev::TargetDev(std::string mac, std::string ipaddr)
    :_MAC(mac),_IP(ipaddr){
    this->_ItemList = this->InitItemlist();
    this->_Curitem = _ItemList.begin()-1;
}

TargetDev::~TargetDev(){

}

std::vector<TestItem> TargetDev::InitItemlist(){
    std::vector<TestItem> retlist;
    std::vector<IDINT> idlist = MDBManager::Instance()->GetIDList();
    for (IDINT id : idlist){
        TestItem testitem(id);
        retlist.push_back(testitem);
    }
    return retlist;
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

void TestControl::Reload(){}

bool TestControl::Start(std::string ipaddr, nlohmann::json content)
{
   if(!MDBManager::Instance()->InitDB()){return false;}// check if DB is ready
   if(!TestControl::Instance()->CheckReady(content, ipaddr)){return false;}//check client is ready
   nlohmann::json json = {
       { "Method", "Start" },
       { "Content", MDBManager::Instance()->GetTestList()}
   };
   WSSrvRoute::Instance()->SendMsg(ipaddr, json.dump());
   return true;
}

bool TestControl::SetStarted(std::string ipaddr, nlohmann::json content){
    if (content["test_id"].is_null()){return false;}
    IDINT testid = content["test_id"];
    MDBManager::Instance()->SetStatus(testid, this->_DevMap[ipaddr].GetMac(),2);
    return true;
}

void TestControl::Stop(std::string){};

nlohmann::json TestControl::ItemResults(std::string ipaddr)
{

}

TestControl::TestControl(){}

TestControl::~TestControl(){}



std::string TestControl::GetSystime(){
    auto now = std::chrono::system_clock::now();
    time_t curtime = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&curtime);
};


bool TestControl::CheckReady(nlohmann::json content, std::string ipaddr){
    if (content.contains("MAC")  && !content["MAC"].is_null()){
        TargetDev dev(ipaddr, content["MAC"]);
        this->_DevMap[ipaddr]=dev;// add ready device to device map
        return true;
    }
    else {
        return false;
    }
};


nlohmann::json TestControl::ItemList(std::string ipaddr)
{
    this->_Lock.LockR();
    std::string MAC = this->_DevMap[ipaddr].GetMac();
    nlohmann::json tmpjson = MDBManager::Instance()->GetTestList();
    this->_Lock.UNLock();
    return tmpjson;
}
