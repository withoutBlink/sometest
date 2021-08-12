#ifndef TSTATUS_H
#define TSTATUS_H

#include <QWidget>

namespace Ui {
class TStatus;
}

class TStatus : public QWidget
{
	Q_OBJECT

public:
	explicit TStatus(QWidget *parent = nullptr, uint status = 0);
	~TStatus();

	void SetStatus(uint status);
	int GetStatus();

private:
	template<typename T> void setProperty(T obj, uint status = 0);
	template<typename T> uint getProperty(T obj);

private:
	Ui::TStatus *ui;
//	int _Status;
};

#endif // TSTATUS_H
