#include "config.h"

#include "inifile/inifile.h"
#include "easylog/easylogging++.h"

#include "src/mdbmanager.h"
#include "utils/softwareabout.h"


Config *Config::_This = nullptr;

Config *Config::Instance()
{
	if (!_This) {
		_This = new Config;
	}
	return _This;
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
		this->parse();
	}  catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}
}

Config::~Config()
{

}

void Config::parse()
{
	inifile::IniFile inifile;
	if (inifile.Load(SOFTWARE_PATH_CONFIG)) {
		throw std::invalid_argument("failed parse config.");
	}

	if (inifile.HasKey("Service", "ErrIntereupt")) {
		inifile.GetBoolValue("Service", "ErrIntereupt", &this->Data.ErrIntereupt);
	}
	if (inifile.HasKey("Service", "ErrRepetitionCount")) {
		inifile.GetIntValue("Service", "ErrRepetitionCount", &this->Data.ErrRepetitionCount);
	}
	if (inifile.HasKey("Service", "ErrRepetitionTime")) {
		inifile.GetStringValue("Service", "ErrRepetitionTime", &this->Data.ErrRepetitionTime);
	}
	if (inifile.HasKey("Service", "Port")) {
		inifile.GetIntValue("Service", "Port", &this->Data.PortService);
	}
	if (inifile.HasKey("Server", "IP")) {
		inifile.GetStringValue("Server", "IP", &this->Data.IP);
	}
	if (inifile.HasKey("Server", "PortScanServer")) {
		inifile.GetIntValue("Server", "PortScanServer", &this->Data.PortScanServer);
	}
	if (inifile.HasKey("Server", "PortServerHttp")) {
		inifile.GetIntValue("Server", "PortServerHttp", &this->Data.PortServerHTTP);
	}
	if (inifile.HasKey("Server", "ProtServerWs")) {
		inifile.GetIntValue("Server", "ProtServerWs", &this->Data.PortServerWS);
	}
}

