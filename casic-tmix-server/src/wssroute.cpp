// global
#include "wssroute.h"
WSSRoute *WSSRoute::_This = nullptr;
// global end

// public
WSSRoute *WSSRoute::Instance()
{
	if (!_This) {
        _This = new WSSRoute;
	}
	return _This;
}

void WSSRoute::Init(WsServer::Endpoint &ep)
{
	ep.on_open = onOpen;
	ep.on_close = onClose;
	ep.on_error = onError;
	ep.on_message = onMessage;
}

void WSSRoute::SendMsg(std::string& ipaddr, const std::string& msg){
    this->SendMsg(this->GetConnection(ipaddr), msg);
}

void WSSRoute::BroadCast(const std::string& msg){
    nlohmann::json message = {
        {"Method","BroadCast"},
        {"Content",msg}};
    for (auto map : this->_ItemConnection){
        this->SendMsg(map.second, message);
    }
}
// public end


// private function
WSSRoute::WSSRoute(){

}

WSSRoute::~WSSRoute(){}

void WSSRoute::SetConnection(std::shared_ptr<WsServer::Connection> connection)
{
    std::lock_guard<std::mutex>(this->_ConnectionMutex);
    std::string addr = connection->remote_endpoint_address();

    if (connection->path == WS_URL_SVCUI) {
        this->_UIConnection[addr] = connection;
        // this->InitUi();
    }
    else if (connection->path == WS_URL_SVCITEMS) {
        this->_ItemConnection[addr] = connection;
        // this->InitItem();
    }
    else
        LOG(WARNING) << "Connection from: "
                     << addr
                     << " Error";

    //this->_ConnectionMutex.unlock();
}

std::shared_ptr<WsServer::Connection> WSSRoute::GetConnection(const std::string& addr)
{
//    if (this->_Connection[addr] != nullptr)
//        return this->_UIConnection[addr];
//    else
        return this->_ItemConnection[addr];
}

std::shared_ptr<WsServer::Connection> WSSRoute::GetConnection(const std::uint16_t& id){};

void WSSRoute::SendMsg(std::shared_ptr<WsServer::Connection> connection, const std::string &msg)
{
    if (msg.empty())
        return ;

    LOG(INFO) << "\nUI SendMsg:\n" << msg;

    auto sendstream = std::make_shared<WsServer::SendStream>();
    *sendstream << msg;
    if (connection != nullptr){
        try {
            connection->send(sendstream);
        } catch (std::exception &e) {
            LOG(ERROR) << e.what();
        }
    }
    else
        LOG(WARNING) << "Connection not found"
                     << "sending "
                     << msg
                     << "message failed";
}

void WSSRoute::ErrorRespond(std::string err, std::shared_ptr<WsServer::Connection> connection){
    nlohmann::json respond = {
        {"Method","Error"},
        {"Content",err}
    };
    _This->SendMsg(connection, respond.dump());
}

void WSSRoute::CloseConnection(std::shared_ptr<WsServer::Connection> connection){
    LOG(INFO) << "Disconnect from"
              << connection->remote_endpoint_address();
    this->_UIConnection[connection->remote_endpoint_address()] = nullptr;
    this->_ItemConnection[connection->remote_endpoint_address()] = nullptr;
}

void WSSRoute::onOpen(std::shared_ptr<WsServer::Connection> connection)
{
    std::string remote_address = connection->remote_endpoint_address();
    uint remote_port = connection->remote_endpoint_port();
    std::string local_path = connection->path;
	LOG(DEBUG) << "Opened connection "
           << remote_address
		   << ":"
           << remote_port;
    _This->SetConnection(connection);
}

void WSSRoute::onClose(std::shared_ptr<WsServer::Connection> connection,
			 int status, const std::string &)
{
    LOG(DEBUG) << "Closed connection: "
               << connection->remote_endpoint_address()
               << ":"
               << connection->remote_endpoint_port()
               << connection->path
               << ":"
               << connection.get()
               << " with status code "
               << status;
    _This->CloseConnection(connection);
    WSSRoute::Instance()->SendMsg(connection, "disconnected");
}

void WSSRoute::onError(std::shared_ptr<WsServer::Connection> connection,
			 const SimpleWeb::error_code &ec)
{
	LOG(WARNING) << "Error in connection "
             << connection->path
		     << ":"
		     << connection.get()
		     << ". "
		     << "Error: "
		     << ec
		     << ", error message: "
		     << ec.message();
}

void WSSRoute::onMessage(std::shared_ptr<WsServer::Connection> connection,
			   std::shared_ptr<WsServer::Message> message)
{
    std::string msg = message->string();
    std::string from = connection->path;

    LOG(DEBUG) << "\n"
		   << ">>>>> Message received <<<<<\n"
           << "from: " << connection->path //
		   << ":"
           << connection->remote_endpoint_address()
           << ":"
           << connection->remote_endpoint_port()<< "\n"
           << "message: \n"
		   << msg << "\n"
		   << "----------------------------\n";

    //_This->SendMsgToItem(msg); // echo test

    try { // json based message frame test
		nlohmann::json request = nlohmann::json::parse(msg);
		if (request.is_null() || !request.is_object()
				|| !request.contains("Method") || !request["Method"].is_string()
				|| !request.contains("Content") || request["Content"].is_null()
				) {
            throw std::invalid_argument("Illegal message.");
        }
        if (from == "/tmix/items"){
            _This->onItemMesg(msg, connection);// add thread!!!
            
        }
        else if (from == "/tmix/ui"){
            _This->onUIMesg(msg, connection);// add thread!!!
            
        }
        else
            LOG(WARNING) << "Illegal path visited by:"
                         << connection->remote_endpoint_address();
    } catch (std::exception &e) {
        _This->ErrorRespond(e.what(), connection);
        LOG(ERROR) << e.what();
	}
}

void WSSRoute::onUIMesg(const std::string& msg, std::shared_ptr<WsServer::Connection> connection){
    std::lock_guard<std::mutex>(this->_ConnectionMutex);
    nlohmann::json msg_obj = nlohmann::json::parse(msg);
    std::string method = msg_obj["Method"];
    nlohmann::json content;
    std::string content_str;
    if (msg_obj["Content"].is_string() ){
        content_str = msg_obj["Content"];
    }
    else if (msg_obj["Content"].is_object()){
        content = msg_obj["Content"];
    }
    else
        throw std::invalid_argument("Content illegal");
}// end of onUIMesg

void WSSRoute::onItemMesg(const std::string& msg, std::shared_ptr<WsServer::Connection> connection){
    std::lock_guard<std::mutex>(this->_ConnectionMutex);
    nlohmann::json msg_obj = nlohmann::json::parse(msg);
    std::string method = msg_obj["Method"];
    nlohmann::json content;
    std::string content_str;
    std::string ipaddr = connection->remote_endpoint_address();
    if (msg_obj["Content"].is_string() ){
        content_str = msg_obj["Content"];
    }
    else if (msg_obj["Content"].is_object()){
        content = msg_obj["Content"];
    }
    else
        throw std::invalid_argument("Content illegal or not exists");

    if(method == "TestReady"){ // decide the test machine is ready or not after recieve
        if (TestControl::Instance()->Prepare(ipaddr, content)){SendMsg(connection, TestControl::Instance()->Start(ipaddr).dump());}
        else {this->ErrorRespond("client not ready", connection);}
    } else if (method == "Started"){
        if (TestControl::Instance()->SetStarted(ipaddr,content)){}
        else {ErrorRespond("Illegal testitem or Itemlist not ready", connection);}
    } else if (method == "RelaodTest"){

    } else if (method == "TimeSync"){
        _This->SendMsg(connection, TestControl::Instance()->GetSystime());
    } else if (method == "BroadCast"){
        this->BroadCast(content_str);
    } else if (method == "SetItemResult"){
        if(!TestControl::Instance()->SetItemResult(ipaddr, content)){this->ErrorRespond("WrongResultContent",connection);}
        else {this->ErrorRespond("illegal result content", connection);}
    } else if (method == ""){

    } else{
        WSSRoute::Instance()->SendMsg(connection, "Illegal Message");
        LOG(WARNING) << "Unrecongnized method:"
                     << method;
    }
}// end of onItemMesg

