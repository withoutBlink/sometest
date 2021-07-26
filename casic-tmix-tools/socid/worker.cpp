#include "worker.h"

#include "nlohmann/json.hpp"
#include "easylog/easylogging++.h"

Worker *Worker::_This = nullptr;

Worker *Worker::Instance()
{
	if (!_This) {
		_This = new Worker;
	}
	return _This;
}

void Worker::Destory()
{
	if (_This) {
		delete _This;
		_This = nullptr;
	}
}

Worker::Worker()
{

}

Worker::~Worker()
{

}

void Worker::sendMessage(const nlohmann::json &message)
{
	if (message.empty()) {
		return ;
	}

	LOG(INFO) << "Client: Sending message: \n" << message.dump(4) << "\n";

	auto send_stream = std::make_shared<WsClient::SendStream>();
	*send_stream << message.dump();
	this->_Connection->send(send_stream);
}

void Worker::Start(std::shared_ptr<WsClient::Connection> connection)
{
	this->_Connection = connection;

	nlohmann::json json;
	json["Method"] = "CallUI";
	json["Content"]["Id"] = 1;
	json["Content"]["Type"] = "InputBox";
	json["Content"]["Title"] = "对话窗口标题";
	json["Content"]["Text"] = "对话窗口提示";
	json["Content"]["PlaceholderText"] = "对话窗口占位符";
	json["Content"]["Btns"][0]["Id"] = 1;
	json["Content"]["Btns"][0]["Text"] = "确认";
	json["Content"]["Btns"][0]["Property"] = "Affirm";
	json["Content"]["Btns"][1]["Id"] = 2;
	json["Content"]["Btns"][1]["Text"] = "取消";
	json["Content"]["Btns"][1]["Property"] = "Cancel";

	this->sendMessage(json);
}

void Worker::WSUiRoute(const nlohmann::json &msg)
{

}

void Worker::WSSrvRoute(const nlohmann::json &msg)
{

}



