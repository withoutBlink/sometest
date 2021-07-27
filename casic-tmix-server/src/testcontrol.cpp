// global
#include "testcontrol.h"

TestControl *TestControl::_This = nullptr;
//global end


TestItem::TestItem(IDINT id)
    :_test_id(id){
    nlohmann::json iteminfo = MDBManager::Instance()->GetTestItem(this->_test_id);

}

TestItem::~TestItem(){}

size_t TestItem::GetStatus()
{
    this->_Lock.LockR();
    size_t status = this->_Status;
    this->_Lock.UNLock();
    return status;
}

void TestItem::SetStarted()
{
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

bool TestItem::SetResult(bool result)
{
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
   this->SetStarted(this->GetMAC(ipaddr));
   WSSrvRoute::Instance()->SendMsg(ipaddr, json.dump());
   return true;
}

void TestControl::Stop(std::string){};

nlohmann::json TestControl::ItemResults(std::string ipaddr)
{
    nlohmann::json curitem = TestControl::Instance()->CurItem(ipaddr);
    int rescode = msg["Result"]["Status"].get<bool>() ? 1 : 2;// test pass or not pass
    curitem["Result"] = rescode;
    TestControl::Instance()->SetCurResult(rescode);
	nlohmann::json json = {
		{ "Method", "ItemResult" },
		{ "Content", curitem }
	};
    return json;

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

TestControl::TestControl(){}

TestControl::~TestControl(){}

void SetStarted(std::string mac){

}


bool TestControl::itemNext()
{
    return TestControl::Instance()->Item.NextItem();
}

void TestControl::itemStart()
{
	nlohmann::json json = {
		{ "Method", "ItemResult" },
        { "Content", TestControl::Instance()->Item.CurItem() }
	};
	json["Content"]["Result"] = 3;
    // WSSrvRoute::Instance()->SendMsgToUI(json.dump());
	this->_WorkThread = new std::thread([=](){
		try {
            LOG(DEBUG) << TestControl::Instance()->Item.CurItem();
            std::string cmd = fmt::format("{0}/{1}", SOFTWARE_PATH_BIN, TestControl::Instance()->Item.CurItem()["Exec"].get<std::string>());
			std::system(cmd.c_str());
		}  catch (std::exception &e) {
			LOG(ERROR) << e.what();
		}
	});
}

void TestControl::itemStop(){
	if (this->_WorkThread) {
		this->_WorkThread->join();
		delete this->_WorkThread;
		this->_WorkThread = nullptr;
	}
}

std::string TestControl::GetSystime(){
    auto now = std::chrono::system_clock::now();
    time_t curtime = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&curtime);
};

void TestControl::Task(){
};

bool TestControl::CheckReady(nlohmann::json content, std::string ipaddr){
    if (content.contains("MAC")  && !content["MAC"].is_null()){
        bindMAC(ipaddr, content["MAC"]);
        return true;
    }
    else {
        return false;
    }
};

void TestControl::bindMAC(std::string ipaddr, std::string macaddr){
    this->_MACbind[macaddr] = ipaddr;
};


nlohmann::json TestControl::ItemList(std::string ipaddr)
{
    this->_Lock.LockR();
    std::string MAC = this->GetMAC(ipaddr);
    nlohmann::json json = MDBManager::Instance()->GetTestItems(MAC);
    this->_Lock.UNLock();
    return json;
}

nlohmann::json TestControl::CurItem()
{
    nlohmann::json json;
    this->_Lock.LockR();
    json = MDBManager::Instance()->GetItem(this->_CurItem);
    this->_Lock.UNLock();
    return json;
}


bool TestControl::NextItem()
{
    bool ret = false;
    this->_Lock.LockR();

    std::vector<size_t> idlist = MDBManager::Instance()->GetIDList();
    auto it = find(idlist.begin(), idlist.end(), this->_CurItem);
    if (it != idlist.end()) {
        std::size_t index = it - idlist.begin();
        if (index < idlist.size()) {
            this->_CurItem = idlist.at(index + 1);
            ret = true;
        }
    }

    this->_Lock.UNLock();
    return ret;
}

std::string TestControl::GetMAC(std::string ipaddr){
    return this->_MACbind.find(ipaddr)->first;
}
