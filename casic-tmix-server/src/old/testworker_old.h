#ifndef TESTWORKER_H
#define TESTWORKER_H

#include <mutex>
#include <thread>

#include "nlohmann/json.hpp"

class TestControl
{
public:
    static TestControl *Instance();
	static void Destory();

	void Reload();
    nlohmann::json Start();
    nlohmann::json GetItemConf();
    nlohmann::json ItemResult(const nlohmann::json& msg);
    void Task(std::string msg);

private:
    TestControl();
    ~TestControl();

	bool itemNext();
	void itemStart();
	void itemStop();

private:
    static TestControl *_This;
	std::thread *_WorkThread;
};

#endif // TESTWORKER_H
