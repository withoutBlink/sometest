#ifndef CTLBTNBOX_H
#define CTLBTNBOX_H

#include <QWidget>

namespace Ui {
class CtlBtnBox;
}

class CtlBtnBox : public QWidget
{
	Q_OBJECT

public:
	explicit CtlBtnBox(QWidget *parent = nullptr);
	~CtlBtnBox();

private:
	Ui::CtlBtnBox *ui;
};

#endif // CTLBTNBOX_H
