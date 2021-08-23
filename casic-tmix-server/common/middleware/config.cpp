#include "config.h"

#include "inifile/inifile.h"
#include "easylog/easylogging++.h"

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

	if (inifile.HasKey("Service", "Port")) {
		inifile.GetIntValue("Service", "Port", &this->Data.Port);
	}
}
