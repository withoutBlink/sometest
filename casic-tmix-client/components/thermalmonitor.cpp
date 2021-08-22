#include "thermalmonitor.h"
#include "ui_thermalmonitor.h"

ThermalMonitor::ThermalMonitor(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ThermalMonitor)
{
	ui->setupUi(this);

	ui->WGDashBoard->SetUnit("℃");
}

ThermalMonitor::~ThermalMonitor()
{
	delete ui;
}

void ThermalMonitor::SetTitle(const QString &title)
{
	ui->Title->setText(title + "(℃)");
}

void ThermalMonitor::SetValue(const double value)
{
	ui->WGDashBoard->SetValue(value);
}
