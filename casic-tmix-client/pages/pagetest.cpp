#include "pagetest.h"
#include "ui_pagetest.h"

#include <QFile>
#include <QTextBlock>
#include <QTextDocument>

#include "nlohmann/json.hpp"
#include "easylog/easylogging++.h"

#include "wsroute.h"

PageTest::PageTest(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PageTest)
{
	ui->setupUi(this);

	ui->CPUThermal->SetTitle("CPU温度");
	ui->GPUThermal->SetTitle("GPU温度");

	this->printWelcome();

	connect(WsRoute::Instance(), SIGNAL(SignalRecvTemp(const QString&))
		, this, SLOT(onRecvTemp(const QString &)));

	connect(WsRoute::Instance(), SIGNAL(SignalMessages(const QString&))
		, this, SLOT(onRecvMessages(const QString &)));
}

PageTest::~PageTest()
{
	delete ui;
}

void PageTest::UpdataItemList(const QString &msg)
{
	ui->TWItemList->SetItemList(msg);
}

void PageTest::printWelcome()
{
	int fontid = QFontDatabase::addApplicationFont(":/static/fonts/JetBrainsMono-Medium.ttf");
	ui->TEMsg->setFont(QFontDatabase::applicationFontFamilies(fontid).at(0));

//	QFile file(":/assets/welcome.txt");
//	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//		ui->TEMsg->setPlainText(file.readAll());
//		file.close();
//	}
}

void PageTest::onRecvTemp(const QString &data)
{
	try {
		nlohmann::json json = nlohmann::json::parse(data.toUtf8());
		LOG(INFO) << json.dump(4);

		double cputemp = 0, gputemp = 0;
		for (auto& var : json["CPU"].items()) {
			cputemp = (cputemp > var.value().get<double>()) ? cputemp : var.value().get<double>();
			LOG(INFO) << var.key() << " : " << var.value();
		}
		ui->CPUThermal->SetValue(cputemp);

		for (auto& var : json["GPU"].items()) {
			gputemp = (gputemp > var.value().get<double>()) ? gputemp : var.value().get<double>();
			LOG(INFO) << var.key() << " : " << var.value();
		}
		ui->GPUThermal->SetValue(gputemp);
	} catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}
}

void PageTest::onRecvMessages(const QString &data)
{
	try {
		nlohmann::json json = nlohmann::json::parse(data.toUtf8());
		LOG(INFO) << json.dump(4);
		QString msg = QString::fromUtf8(json["Msg"].get<std::string>().c_str());
		ui->TEMsg->append(msg.left(msg.lastIndexOf('\n')));
	} catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}
}
