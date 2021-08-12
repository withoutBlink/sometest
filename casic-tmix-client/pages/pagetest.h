#ifndef PAGETEST_H
#define PAGETEST_H

#include <QWidget>

namespace Ui {
class PageTest;
}

class PageTest : public QWidget
{
	Q_OBJECT

public:
	explicit PageTest(QWidget *parent = nullptr);
	~PageTest();

	void UpdataItemList(const QString& msg);

private:
	void printWelcome();

private slots:
	void onRecvTemp(const QString& data);
	void onRecvMessages(const QString& data);

private:
	Ui::PageTest *ui;
};

#endif // PAGETEST_H
