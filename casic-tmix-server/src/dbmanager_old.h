#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "SQLiteCpp.h"
#include "nlohmann/json.hpp"

#include <mutex>

class DBManager
{
public:
	static DBManager *Instance();

	nlohmann::json GetTestItems();
//	std::size_t GetCurItemId();
	nlohmann::json GetItem(std::size_t id);
	bool GetStarted();
	uint GetUpdate();
	bool SetStarted(bool started);
	bool SetItemResult(uint id, uint result);
	std::vector<std::size_t> GetIdList();

private:
	DBManager();
	~DBManager();

private:
	static DBManager *_This;
	SQLite::Database *_DB;
	std::mutex _Mutex;
};

#endif // DBMANAGER_H
