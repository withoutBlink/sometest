#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QMovie>
#include <QDialog>
#include <QMouseEvent>
#include <QRegExpValidator>

#include "nlohmann/json.hpp"

namespace Ui {
class InputBox;
}

class InputBox : public QDialog
{
	Q_OBJECT

public:
	static QString MsgFromJson(const nlohmann::json& json, QWidget *parent = nullptr);

	explicit InputBox(QWidget *parent = nullptr);
	~InputBox();

	void SetTitle(const QString& title);
	void SetText(const QString& text);
	void SetReadOnly(bool readonly);
//	void SetNotEmpty(bool notempty);
	void SetPlaceholderTest(const QString& ptext);
	void AddButton(QPushButton *btns);
	void SetButton(QList<QPushButton *> btns);
	void SetValidator(const QString& validator);

	QString GetResult();

private:
	template<typename T> void setError(T obj, bool err = true);

private slots:
//	void on_BtnClose_clicked();
//	void on_BtnMinimized_clicked();
	void on_BtnAffirm_clicked();
//	void on_BtnCancel_clicked();

	void on_LEText_editingFinished();
	void on_LEText_2_editingFinished();

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *);
	bool eventFilter(QObject *watched, QEvent *event);

private:
	Ui::InputBox *ui;
	bool _NotEmpty;
	bool _MousePressed;
	QPoint _MousePoint;
	QRegExp _CheckOutRegExp;
	QRegExpValidator *_CheckOutRegExpValidator;
};

#endif // INPUTBOX_H
