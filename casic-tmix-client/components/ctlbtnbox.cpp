#include "ctlbtnbox.h"
#include "ui_ctlbtnbox.h"

CtlBtnBox::CtlBtnBox(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CtlBtnBox)
{
	ui->setupUi(this);
}

CtlBtnBox::~CtlBtnBox()
{
	delete ui;
}
