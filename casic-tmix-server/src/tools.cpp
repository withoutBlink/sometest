#include "tools.h"

#include "src/dbmanager.h"
#include "src/testworker.h"
#include "easylog/easylogging++.h"

Tools *Tools::_This = nullptr;

Tools *Tools::Instance()
{
	if (!_This) {
		_This = new Tools;
	}
	return _This;
}

void Tools::GetItemList()
{
	try {
		nlohmann::json itemlist = DBManager::Instance()->GetTestItems();
		nlohmann::json json = {
			{ "Method", "ItemList" },
			{ "Content", itemlist }
		};

		WSSrvRoute::Instance()->SendMsgToUI(json.dump());
	}  catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}
}

void Tools::InitUi()
{
	TestWorker::Instance()->Reload();
//	DBManager::Instance()->
//	if (DBManager::Instance()->GetStarted()) {
//		this->Started();
//	}
}

void Tools::Started()
{
	try {
		nlohmann::json itemlist = DBManager::Instance()->GetTestItems();
		nlohmann::json json = {
			{ "Method", "Started" },
			{ "Content", itemlist }
		};
		WSSrvRoute::Instance()->SendMsgToUI(json.dump());

		DBManager::Instance()->SetStarted(true);

	}  catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}
}

Tools::Tools()
{

}

Tools::~Tools()
{

}

