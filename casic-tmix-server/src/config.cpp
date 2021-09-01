#include "config.h"

Config *Config::_This = nullptr;

Config *Config::Instance()
{
	if (!_This) {
		_This = new Config;
	}
	return _This;
}

ushort Config::GetServicePort(){
    return this->PortService;
}


void Config::Destory()
{
	if (_This) {
		delete _This;
		_This = nullptr;
	}
}

Config::Config()
{
	try {
        this->LoadConf();
	}  catch (std::exception &e) {
        LOG(ERROR) << "LoadConf Error: " << e.what();
	}
}

Config::~Config()
{

}

void Config::LoadConf()
{
    nlohmann::json serverconf = MDBManager::Instance()->GetServerConf();
    //this->ServerIP = serverconf["IP"];
    this->PortService = serverconf["PortService"];
    //this->ErrIntereupt = serverconf["ErrInterupt"];
    //this->ErrRepetitionCount = serverconf["ErrRepetitionCount"];
    //this->PortScanServer = serverconf["PortScanServer"];
    //this->PortServerHTTP = serverconf["PortServerHttp"];
    //this->PortServerWS = serverconf["PortServerWs"];
}

