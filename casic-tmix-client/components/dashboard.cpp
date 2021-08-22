#include "dashboard.h"

#include <QRect>
#include <QtMath>
#include <QEvent>
#include <QString>
#include <QPainter>
#include <QPainterPath>

DashBoard::DashBoard(QWidget *parent)
	: QWidget(parent)
	, _Value(0)
	, _Min(0.0)
	, _Max(100.0)
{
}

void DashBoard::SetRange(const double min, const double max)
{
	this->_Min = min;
	this->_Max = max;
	update();
}

void DashBoard::SetMinRange(const double min)
{
	this->_Min = min;
	update();
}

void DashBoard::SetMaxRange(const double max)
{
	this->_Max = max;
	update();
}

void DashBoard::SetUnit(const QString& unit)
{
	this->_Unit = unit;
	update();
}

void DashBoard::SetText(const QString& text)
{
	this->_Text = text;
	update();
}

void DashBoard::SetValue(const double value)
{
	if (value < this->_Min) {
		this->_Value = _Min;
	} else if (value > _Max) {
		this->_Value = _Max;
	} else {
		this->_Value = value;
	}
	update();
}

void DashBoard::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);

	int side = qMin(int(height() / 8.5 * 10.0), width());

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(width() / 2, height() / 2);
	painter.scale(side / 200.0, side / 200.0);
	painter.translate(0, 15);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::NoBrush);

	drawDashBoard(painter);
	drawHand(painter);
	drawValue(painter);
	//	drawText(painter);
}

void DashBoard::drawDashBoard(QPainter &painter)
{
	painter.save();

	painter.setPen(QPen(QColor(96, 96, 96, 196), 12, Qt::SolidLine));
	QRectF rectangle(-67, -67, 134, 134);
	int startAngle = -40 * 16;
	int spanAngle = 260 * 16;
	painter.drawArc(rectangle, startAngle, spanAngle);

	painter.save();
	painter.setPen(QPen(QColor(164, 181, 255, 225), 0.75, Qt::SolidLine));
	painter.rotate(-220);
	for (int i = 0; i < 11; ++i) {
		painter.drawLine(76, 0, 86, 0);
		painter.rotate(26.0);
	}
	painter.restore();

	painter.save();
	painter.setPen(QPen(QColor(164, 181, 255, 225), 0.5, Qt::SolidLine));
	painter.rotate(-220);
	for (int i = 0; i < 50; ++i) {
		painter.drawLine(76, 0, 82, 0);
		painter.rotate(5.2);
	}
	painter.restore();

	double range = _Max - _Min;
	double step = range / 10.0;
	for (int i = 0; i < 11; ++i) {
		painter.save();
		painter.setPen(QColor(164, 181, 255, 225));
		painter.setFont(QFont("Times", 10));
		painter.rotate(-220.0);
		painter.rotate(26.0 * i);
		painter.translate(95, 0);
		painter.rotate(90.0);
		painter.drawText(QRect(-19, -7, 38, 14), Qt::AlignCenter, QString::number(this->_Min + i * step));
		painter.restore();
	}

	painter.restore();
}

void DashBoard::drawHand(QPainter &painter)
{
	static const QPoint hand[] = {
		QPoint(-5, 0),
		QPoint(0, -75),
		QPoint(5, 0),
		QPoint(0, 7)
	};

	painter.save();
	painter.rotate(-130.0);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0, 144, 255));
	painter.rotate(260.0 / (_Max - _Min) * _Value);
	painter.drawConvexPolygon(hand, 4);
	painter.restore();
}

void DashBoard::drawValue(QPainter &painter)
{
	painter.save();
	painter.setPen(QColor(164, 181, 255));
	painter.setFont(QFont("Times", 18));
	QString unit;
	if (!this->_Unit.isEmpty()) {
		unit = QString::number(this->_Value) + " " + this->_Unit;
	} else {
		unit = QString::number(this->_Value);
	}
	painter.drawText(QRect(-100, 30, 200, 20), Qt::AlignCenter, unit);
	painter.restore();
}

void DashBoard::drawText(QPainter &painter)
{
	painter.save();
	painter.setPen(QColor(164, 181, 255));
	painter.setFont(QFont("Times", 10));
	painter.drawText(QRect(-100, 50, 200, 20), Qt::AlignCenter, QString::number(this->_Value));
	painter.restore();
}

