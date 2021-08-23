#include "mdbmanager.h"

MDBManager *MDBManager::_This = nullptr;

MDBManager *MDBManager::Instance()
{
	if (!_This) {
        _This = new MDBManager;
	}
	return _This;
}

bool MDBManager::InitDB(){
    bool ret=false;
    auto now = std::chrono::system_clock::now();
    time_t curtime = std::chrono::system_clock::to_time_t(now);
    std::string timestr = std::ctime(&curtime);
    std::replace(timestr.begin(), timestr.end(),' ','_');
    std::replace(timestr.begin(), timestr.end(),':','_');
    this->_ResultTable = "Result" + timestr;
    ret = this->ResultListChk();
    return ret;
}

bool MDBManager::ResetItemList(){
    bool ret = false;
    try {
        std::unique_ptr<sql::Statement> stmnt;
        stmnt->executeQuery("update itemlist set test_index=NULL");
        return ret = true;
    } catch (sql::SQLException &e) {
        LOG(ERROR) << "InitTestList failed: " << e.what();
        return ret = false;
    }
}

bool MDBManager::ResultListChk(){
    LOG(INFO) << "Start checking db result list";
    try {
        std::unique_ptr<sql::Statement> crtmptbl(this->_Conn->createStatement());
        crtmptbl->executeQuery("drop table if exists "+this->_ResultTable);
    } catch (sql::SQLException &e) {
        LOG(ERROR) << "Removing table Error: " << e.what();
        return false;
    }
    try {
        LOG(INFO) << "Create new table for testing";
        std::unique_ptr<sql::Statement> crtmptbl(this->_Conn->createStatement());
        crtmptbl->executeQuery("create table "+this->_ResultTable+" (mac_addr varchar(20), test_id int, test_result boolean, test_status boolean)");
        LOG(INFO) <<"New result table created";
        return true;
    } catch (sql::SQLException &e) {
        LOG(ERROR) << "InitResultList Error: " << e.what();
        return false;
    }
}



bool MDBManager::SetTestList(std::vector<IDINT> config){
    try {
        std::unique_ptr<sql::PreparedStatement>
                stmnt(this->_Conn->prepareStatement(
                          "update itemlist set test_select = 1,test_index = ? where id = ?"
                          )
                      );
        u_int index = 0;
        while (index < config.size()){
            stmnt->setUInt(2, config[index]);
            stmnt->setUInt(1, ++index);
            stmnt->executeQuery();
        }
        return true;
    }
    catch(sql::SQLException &e){
        LOG(ERROR) << "SetTestList error" << e.what() ;
        return false;
    }
}



nlohmann::json MDBManager::GetAllTest()
{
	nlohmann::json ret;
	try {
        std::unique_ptr<sql::Statement> stmnt(this->_Conn->createStatement());
        sql::ResultSet *output = stmnt->executeQuery("select * from itemlist");
        while (output->next()) {
            nlohmann::json temp ={
                {"test_id", output->getInt(1)},
                {"test_type", output->getInt(2)},
                {"test_name", output->getString(3)},
                {"test_key", output->getString(4)},
                {"test_info", output->getString(5)},
                {"test_standard", output->getString(6)},
                {"test_start_prog", output->getString(7)},
                {"test_stop_prog", output->getString(8)},
                {"test_select", output->getBoolean(9)},
                {"test_index", output->getInt(10)}
            };
			ret.push_back(temp);
		}
	} catch (std::exception &e) {
        LOG(ERROR) << "GetTestList error" <<e.what();
	}
	return ret;
}


nlohmann::json MDBManager::GetTestList(){
    nlohmann::json testlist;
    try {
        for(size_t index=0; this->GetIDList().size(); index++){
            IDINT id = this->GetIDList()[index];
            nlohmann::json partret = {
                {"test_id", id},
                {"test_start_prog", this->GetItemCMD(id)}
            };
            testlist.push_back(partret);
        }
    } catch (std::exception &e) {
        LOG(ERROR) << "GetTestList failed: " << e.what();
    }
    return testlist;
}

bool MDBManager::NewResult(std::string MAC, IDINT id){
    try {
        std::unique_ptr<sql::PreparedStatement>
                stmnt(this->_Conn->prepareStatement(
                          "insert into "+this->_ResultTable+" (mac_addr, test_id, test_status, test_result) values(?, ?, 0, False)"
                          )
                      );
        stmnt->setString(1, MAC);
        stmnt->setUInt(2, id);
        stmnt->executeQuery();
        return true;
    } catch (sql::SQLException &e) {
        LOG(ERROR) << "GetCurItemID for: " << MAC <<" error:" << e.what();
    }
    return false;
}



IDINT MDBManager::GetCurItemId(std::string MAC)
{
	try {
        std::unique_ptr<sql::PreparedStatement>
                stmnt(this->_Conn->prepareStatement(
                          "select test_id, test_status from result where mac_addr=?"
                          )
                      );
        stmnt->setString(1, MAC);
        sql::ResultSet *output = stmnt->executeQuery();
        IDINT curid = this->GetIDList().front();
        while(output->next()){
            if (output->getInt(2)==2){
                curid = output->getUInt(1);
            }
        }
        return curid;
    } catch (sql::SQLException &e) {
        LOG(ERROR) << "GetCurItemID for: " << MAC <<" error:" << e.what();
	}
    return 0;
}



bool MDBManager::SetStatus(IDINT id, std::string MAC, size_t status){
    bool ret=false;
    try {
    std::unique_ptr<sql::PreparedStatement>
            stmnt(this->_Conn->prepareStatement(
                      "update "+this->_ResultTable+" set test_status=? where mac_addr=? and test_id=?;"
                      )
                  );
    stmnt->setUInt64(1, status);
    stmnt->setString(2, MAC);
    stmnt->setUInt(3, id);
    stmnt->executeQuery();
    return ret=true;
    } catch (sql::SQLException &e) {
        LOG(ERROR) << "failed in setting status of test: " << id << "of machine: " << MAC << e.what();
        return ret=false;
    }
}



bool MDBManager::SetItemResult(IDINT id, std::string MAC, bool result){
    try {
    std::unique_ptr<sql::PreparedStatement>
            stmnt(this->_Conn->prepareStatement(
                      "update "+this->_ResultTable+" set test_result=? where test_id=? and mac_addr=?"
                      )
                  );
    stmnt->setBoolean(1, result);
    stmnt->setUInt(2, id);
    stmnt->setString(3, MAC);
    stmnt->executeQuery();
    return true;
    }
    catch (sql::SQLException &e) {
    LOG(ERROR) << "SetItemResult failed in test id: " << id << "from: " << MAC << e.what();
    return false;
    }

}



bool MDBManager::GetItemResult(IDINT id, std::string MAC){
    bool ret = false;
    try {
    std::unique_ptr<sql::PreparedStatement>
            stmnt(this->_Conn->prepareStatement(
                      "select test_result from "+this->_ResultTable+" where test_id=? and mac_addr=?"
                      )
                  );
    stmnt->setUInt(1, id);
    stmnt->setString(2, MAC);
    sql::ResultSet *output = stmnt->executeQuery();
    return ret = output->getBoolean(1);
    }
    catch (sql::SQLException &e) {
        LOG(ERROR) << "GetItemResult failed in test id: " << id << "from: " << MAC << e.what();
    }
    return ret;
}



bool MDBManager::InsertItem(nlohmann::json newitem){
    try {
    std::unique_ptr<sql::PreparedStatement> stmnt(this->_Conn->prepareStatement(
                                                      "insert into itemlist (test_id, test_type, test_name, test_key, test_info, test_standard, test_start_prog, test_stop_prog, test_select) values (?,?,?,?,?,?,?,?,?)"
                                                      )
                                                  );
    stmnt->setInt(1, newitem["test_id"].get<int>());
    stmnt->setInt(2, newitem["test_type"].get<int>());
    stmnt->setString(3, newitem["test_name"].get<std::string>());
    stmnt->setString(4, newitem["test_key"].get<std::string>());
    stmnt->setString(5, newitem["test_info"].get<std::string>());
    stmnt->setString(6, newitem["test_standard"].get<std::string>());
    stmnt->setString(7, newitem["test_start_prog"].get<std::string>());
    stmnt->setString(8, newitem["test_stop_prog"].get<std::string>());
    stmnt->setBoolean(9, newitem["test_select"].get<bool>());
    stmnt->executeQuery();
    return true;
    }
    catch (sql::SQLException &e) {
        LOG(ERROR) << "InsertList failed: " << e.what();
        return false;
    }
}

nlohmann::json MDBManager::GetTestItem(IDINT id){
    nlohmann::json testitem;
    try {
    std::unique_ptr<sql::PreparedStatement> stmnt(this->_Conn->prepareStatement(
                                                      "select * from itemlist where test_id=?"
                                                      )
                                                  );

    stmnt->setUInt(1, id);
    sql::ResultSet *output = stmnt->executeQuery();
    output->next();
    testitem = {
        {"test_id", output->getInt(1)},
        {"test_type", output->getInt(2)},
        {"test_name", output->getString(3)},
        {"test_key", output->getString(4)},
        {"test_info", output->getString(5)},
        {"test_standard", output->getString(6)},
        {"test_start_prog", output->getString(7)},
        {"test_stop_prog", output->getString(8)},
        {"test_select", output->getBoolean(9)},
        {"test_index", output->getInt(10)}
    };

    return testitem;
    }
    catch (sql::SQLException &e) {
        LOG(ERROR) << "GetTestItem failed: " << e.what();
        return testitem;
    }
}


nlohmann::json MDBManager::GetServerConf(){
    nlohmann::json serverconf;
    try {
    std::unique_ptr<sql::PreparedStatement> stmnt(this->_Conn->prepareStatement(
                                                      "select * from config"
                                                      )
                                                  );
    sql::ResultSet *output = stmnt->executeQuery();
    output->next();
    serverconf = {
        {"ErrInterupt", output->getInt(1)},
        {"ErrRepetitionCount", output->getInt(2)},
        {"ErrRepetitionTime", output->getString(3)},
        {"PortService", output->getInt(4)},
        {"IP", output->getString(5)},
        {"PortScanServer", output->getInt(6)},
        {"PortServerHttp", output->getInt(7)},
        {"PortServerWs", output->getInt(8)},
    };
    }
    catch (sql::SQLException &e) {
        LOG(ERROR) << "GetServerConf failed: " << e.what();
        serverconf = {
            {"PortService", "7063"}
        };
    }
    return serverconf;
}


MDBManager::MDBManager()
{
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://localhost:3306/casic_tmix_db");
        sql::Properties properties({{"user", "admin"}, {"password", "password"}});
        this->_Conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));

    } catch(sql::SQLException &e) {
        LOG(ERROR) << "connect to mariadb server failed!" << e.what();
    }
}



MDBManager::~MDBManager()
{
    if (this->_Conn) {
        this->_Conn->close();
    }
}



std::vector<IDINT> MDBManager::GetIDList(){
    std::vector<IDINT> idlist;
    try {
        std::unique_ptr<sql::PreparedStatement>
                stmnt(this->_Conn->prepareStatement(
                          "select test_id from itemlist where test_index order by test_index asc"
                          )
                      );
        sql::ResultSet *output = stmnt->executeQuery();
        while(output->next()){
            IDINT id = output->getUInt(1);
            idlist.push_back(id);
        }
    } catch (sql::SQLException &e) {
        LOG(ERROR) << "GetIDList failed: " << e.what();
        return idlist;
    }
    return idlist;
}



std::string MDBManager::GetItemCMD(IDINT id)
{
    try {
        std::string ret;
        std::unique_ptr<sql::PreparedStatement>
                stmnt(this->_Conn->prepareStatement(
                          "select test_start_prog from itemlist where test_id=?"
                          )
                      );
        stmnt->setUInt(1, id);
        sql::ResultSet *output = stmnt->executeQuery();
        ret = output->getString(1);
        return ret;

    } catch (sql::SQLException &e) {
        LOG(ERROR) << "GetItemCMD from test item: "<< id << "error: " << e.what();
    }
    return " ";
}



u_int8_t MDBManager::GetStatus(IDINT id, std::string MAC)
{
    try {
        std::unique_ptr<sql::PreparedStatement>
                stmnt(this->_Conn->prepareStatement(
                          "select test_status from ? where mac_addr=? and test_id=?"
                          )
                      );
        stmnt->setString(1, this->_ResultTable);
        stmnt->setString(2, MAC);
        stmnt->setUInt(3, id);
        sql::ResultSet *output = stmnt->executeQuery();
        bool status = output->getUInt(1);
        return status;
    } catch (sql::SQLException &e) {
        LOG(ERROR) << "GetStatus error from: " << MAC << "test id: " << id <<e.what();
    }
    return false;
}



//void MDBManager::errSetpass(IDINT id, std::string MAC){

//}



//void MDBManager::errSeterr(IDINT id, std::string MAC){

//}
