#include "pagehome.h"
#include "ui_pagehome.h"

#include <QFontDatabase>

#include "wsroute.h"
#include "nlohmann/json.hpp"

PageHome::PageHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageHome)
{
    ui->setupUi(this);

    int fontid = QFontDatabase::addApplicationFont(":/static/fonts/runninghand.ttf");
    ui->LBHomeText->setFont(QFontDatabase::applicationFontFamilies(fontid).at(0));

//    connect(ui->BtnStarted, SIGNAL(clicked()), this, SIGNAL(onStarted()));
}

PageHome::~PageHome()
{
    delete ui;
}

void PageHome::on_BtnStarted_clicked()
{
	nlohmann::json json = {
		{ "Method", "Started" },
		{ "Content", "" }
	};
	WsRoute::Instance()->SendMsg(QString::fromUtf8(json.dump().c_str()));
}
