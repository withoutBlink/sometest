#ifndef THERMALMONITOR_H
#define THERMALMONITOR_H

#include <QWidget>

namespace Ui {
class ThermalMonitor;
}

class ThermalMonitor : public QWidget
{
	Q_OBJECT

public:
	explicit ThermalMonitor(QWidget *parent = nullptr);
	~ThermalMonitor();

	void SetTitle(const QString& title);

public slots:
	void SetValue(const double value);

private:
	Ui::ThermalMonitor *ui;
};

#endif // THERMALMONITOR_H
