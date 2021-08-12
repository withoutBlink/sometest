#include "tstatus.h"
#include "ui_tstatus.h"

#include <QStyle>

TStatus::TStatus(QWidget *parent, uint status) :
	QWidget(parent),
	ui(new Ui::TStatus)
{
	ui->setupUi(this);

	this->SetStatus(status);
}

TStatus::~TStatus()
{
	delete ui;
}

void TStatus::SetStatus(uint status)
{
	this->setProperty(ui->LBStatus, status);
	switch (status) {
	case 0: ui->LBStatus->setText("待测试"); break;
	case 1: ui->LBStatus->setText("通过"); break;
	case 2: ui->LBStatus->setText("待重测"); break;
	case 3: ui->LBStatus->setText("测试中"); break;
	}
}

int TStatus::GetStatus()
{
	return this->getProperty(ui->LBStatus);
}

template<typename T>
void TStatus::setProperty(T obj, uint status)
{
	obj->setProperty("XUIStatus", status);
	obj->style()->unpolish(obj);
	obj->style()->polish(obj);
	obj->update();
	this->setStyle(QApplication::style());
}

template<typename T>
uint TStatus::getProperty(T obj)
{
	return obj->property("XUIStatus").toUInt();
}
