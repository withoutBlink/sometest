#include "aboutusbox.h"
#include "ui_aboutusbox.h"

#include <QMouseEvent>

AboutUSBox::AboutUSBox(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AboutUSBox)
{
	ui->setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

	ui->TitleBar->installEventFilter(this);
}

AboutUSBox::~AboutUSBox()
{
	delete ui;
}

bool AboutUSBox::eventFilter(QObject *obj, QEvent *event)
{
	bool ret = true;

	do {
		if (event->type() == QEvent::MouseButtonPress && reinterpret_cast<QMouseEvent *>(event)->button() == Qt::LeftButton ) {
			this->_MousePressed = true;
			this->_MousePoint = reinterpret_cast<QMouseEvent *>(event)->globalPos() - this->pos();
			reinterpret_cast<QMouseEvent *>(event)->accept();
		} else if (event->type() == QEvent::MouseButtonRelease && reinterpret_cast<QMouseEvent *>(event)->button() == Qt::LeftButton) {
			this->_MousePressed = false;
		} else if (event->type() == QEvent::MouseMove && (reinterpret_cast<QMouseEvent *>(event)->buttons() & Qt::LeftButton)) {
			this->move(reinterpret_cast<QMouseEvent *>(event)->globalPos() - this->_MousePoint);
			event->accept();
		}

	} while (false);

	return ret ? ret : QObject::eventFilter(obj, event);
}

void AboutUSBox::on_pushButton_3_clicked()
{
	this->close();
}
