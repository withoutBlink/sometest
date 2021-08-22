#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

class DashBoard : public QWidget
{
	Q_OBJECT
public:
	explicit DashBoard(QWidget *parent = nullptr);

	void SetRange(const double min, const double max);
	void SetMinRange(const double min);
	void SetMaxRange(const double max);
	void SetUnit(const QString& unit);
	void SetText(const QString& text);

public slots:
	void SetValue(const double value);

protected:
	void paintEvent(QPaintEvent *event);

private:
	void drawDashBoard(QPainter& painter);
	void drawHand(QPainter& painter);
	void drawValue(QPainter& painter);
	void drawText(QPainter& painter);

private:
	double _Value;
	double _Min;
	double _Max;
	QString _Unit;
	QString _Text;
};

#endif // DASHBOARD_H
