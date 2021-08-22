#ifndef WSROUTE_H
#define WSROUTE_H

#include <QThread>

#include "webserver/client_ws.hpp"
using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;

class WsRoute : public QObject
{
	Q_OBJECT
public:
	static WsRoute *Instance();
	static void Destroy();

//	void dowork();

	std::shared_ptr<WsClient::Connection> GetConnection();
	void SetConnection(std::shared_ptr<WsClient::Connection> connection);
	void SendMsg(const QString& msg);
	void SendMsg(const std::string& msg);

signals:
	void SignalResultReady();
	void SignalRecvTemp(const QString&);
	void SignalCallUI(const QString&);
	void SignalMessages(const QString&);
	void SignalItemList(const QString&);
	void SignalStarted(const QString&);
	void SignalItemResult(const QString&);

public slots:
	void StartWork();
	void StopWork();

//protected:
//	void run();

private:
	WsRoute();
	~WsRoute();

	static void onOpen(std::shared_ptr<WsClient::Connection> connection);
	static void onClose(std::shared_ptr<WsClient::Connection> connection, int status, const std::string & /*reason*/);
	static void onError(std::shared_ptr<WsClient::Connection> connection, const SimpleWeb::error_code &ec);
	static void onMessage(std::shared_ptr<WsClient::Connection> connection, std::shared_ptr<WsClient::Message> message);

private:
	static WsRoute *_This;
	bool _Run;
	WsClient *_Client;
	std::shared_ptr<WsClient::Connection> _Connection;
};

#endif // WSROUTE_H
