#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMouseEvent>

#include "msgbox.h"
#include "inputbox.h"
#include "aboutusbox.h"

#include "wsroute.h"

#include "nlohmann/json.hpp"
#include "easylog/easylogging++.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    ui->TitleBar->installEventFilter(this);

    this->initStyle();
//	this->initConnect();
}

MainWindow::~MainWindow()
{
	if (this->_WsThread.isRunning()) {
		WsRoute::Destroy();
		this->_WsThread.quit();
		this->_WsThread.wait();
	}

	delete ui;
}

void MainWindow::initStyle()
{
	this->setWindowFlags(Qt::FramelessWindowHint);

	/* 设置标题、LOGO */
	this->setWindowTitle("T-Mix");
	this->setWindowIcon(QIcon(":/static/images/icon_logo.svg"));
	/****************/

	/* 以线程方式启动Websocket路由 */
	WsRoute *wsroute = WsRoute::Instance();
	connect(wsroute, SIGNAL(SignalCallUI(const QString&)),
		this, SLOT(onCallUI(const QString&)));

	connect(this, SIGNAL(StartWsRouter()),
		wsroute, SLOT(StartWork()));

	wsroute->moveToThread(&this->_WsThread);
	this->_WsThread.start();
	emit this->StartWsRouter();
	/****************************/

	// this->showMaximized();
	// this->showFullScreen();

	ui->SWBallotView->setCurrentIndex(0);
	ui->SWBodyPages->setCurrentIndex(0);
}

void MainWindow::initConnect()
{
	foreach (auto &btn, ui->ToolBtnboxes->findChildren<QPushButton *>()) {
		connect(btn, SIGNAL(clicked()), this, SLOT(onSwitchPages()));
	}

	connect(WsRoute::Instance(), SIGNAL(SignalStarted(const QString&)),
		this, SLOT(onStarted(const QString &)));
}

void MainWindow::doubleClieckd()
{
	bool max = ui->BtnMaximized->isChecked();
	ui->BtnMaximized->clicked(!max);
	ui->BtnMaximized->setChecked(!max);
}

void MainWindow::resizeEvent(QResizeEvent */*event*/)
{
	this->isFullScreen() ? ui->TitleBar->hide() : ui->TitleBar->show();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F
			&& (event->modifiers() & Qt::ControlModifier)
			&& (event->modifiers() & Qt::AltModifier)) {
		if (this->windowState() & Qt::WindowFullScreen) {
			this->showNormal();
		} else {
			this->showFullScreen();
		}
	}
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	bool ret = false;

	do {
		if (obj != ui->TitleBar) {
			break;
		}

		if (event->type() == QEvent::MouseButtonDblClick) {
			this->doubleClieckd();
			ret = true;
		} else if (event->type() == QEvent::MouseButtonPress
			   && !this->isMaximized()
			   && reinterpret_cast<QMouseEvent *>(event)->button() == Qt::LeftButton
			   ) {
			this->_MousePressed = true;
			this->_MousePoint = reinterpret_cast<QMouseEvent *>(event)->globalPos() - this->pos();
			reinterpret_cast<QMouseEvent *>(event)->accept();
			ret = true;
		} else if (event->type() == QEvent::MouseButtonRelease
			   && !this->isMaximized()
			   && reinterpret_cast<QMouseEvent *>(event)->button() == Qt::LeftButton
			   ) {
			this->_MousePressed = false;
			ret = true;
		} else if (event->type() == QEvent::MouseMove
			   && this->_MousePressed
			   && (reinterpret_cast<QMouseEvent *>(event)->buttons() & Qt::LeftButton)
			   ) {
			this->move(reinterpret_cast<QMouseEvent *>(event)->globalPos() - this->_MousePoint);
			event->accept();
			ret = true;
		}
	} while (false);

	return ret ? ret : QObject::eventFilter(obj, event);
}

void MainWindow::onStarted(const QString &msg)
{
	ui->TestPage->UpdataItemList(msg);
	ui->SWBodyPages->setCurrentIndex(1);
//	this->showMaximized();
	this->showFullScreen();
}

void MainWindow::onSwitchPages()
{
	QList<QPushButton *> btnlist = ui->ToolBtnboxes->findChildren<QPushButton *>();
	ui->SWBallotView->setCurrentIndex(btnlist.indexOf(reinterpret_cast<QPushButton *>(sender())));
}

void MainWindow::onCallUI(const QString &msg)
{
	try {
		nlohmann::json json = nlohmann::json::parse(msg.toUtf8());
		LOG(DEBUG) << json.dump(4);

		QString method = QString::fromUtf8(json["Type"].get<std::string>().c_str());
		if (method == "MsgBox") {
			int ret = MsgBox::MsgFromJson(json, this);
			nlohmann::json response = {
				{ "Method", "RecvCallUI" },
				{ "Content", {
					  {"Type", "MsgBox"},
					  {"Id", json["Id"].get<int>()} ,
					  {"Code", ret},
					  {"Msg", ""}
				  }
				}
			};
			WsRoute::Instance()->SendMsg(response.dump());
		} else if (method == "InputBox") {
			QString ret = InputBox::MsgFromJson(json, this);
			nlohmann::json response = {
				{ "Method", "RecvCallUI" },
				{ "Content", {
					  {"Type", "InputBox"},
					  {"Id", json["Id"].get<int>()} ,
					  {"Msg", ret.toUtf8()}
				  }
				}
			};
			WsRoute::Instance()->SendMsg(response.dump());
		}
	} catch (std::exception &e) {
		LOG(ERROR) << e.what();
	}
}

void MainWindow::on_BtnClose_clicked()
{
	this->close();
}

void MainWindow::on_BtnMaximized_clicked(bool checked)
{
	if (checked) {
		this->showMaximized();
	} else {
		this->showNormal();
	}
}

void MainWindow::on_BtnMinimized_clicked()
{
	this->showMinimized();
}

void MainWindow::on_BtnAboutUS_clicked()
{
	AboutUSBox aboutus(this);
	aboutus.exec();
}
