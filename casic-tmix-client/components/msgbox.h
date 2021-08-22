#ifndef MSGBOX_H
#define MSGBOX_H

#include <QMovie>
#include <QDialog>
#include <QMouseEvent>

#include "nlohmann/json.hpp"

namespace Ui {
class MsgBox;
}

class MsgBox : public QDialog
{
	Q_OBJECT

public:
	enum Icon {
		NoIcon = 0,		/* 没有图标 */
		Information = 1, 	/* 普通提示 */
		Warning = 2,		/* 警告图标 */
		Critical = 3,		/* 错误图标 */
		Question = 4		/* 疑问图标 */
	};
//	Q_DECLARE_FLAGS(Icons, Icon)
//	Q_DECLARE_OPERATORS_FOR_FLAGS(Icons)

	static int MsgFromJson(const nlohmann::json& json, QWidget *parent = nullptr);

//	static int InformationBox(MsgBox::Icon icon, const QString &title,
//				   const QString& text, QWidget *parent = nullptr);

//	static int WarningBox(MsgBox::Icon icon, const QString &title,
//			       const QString& text, QWidget *parent = nullptr);

//	static int CriticalBox(MsgBox::Icon icon, const QString &title,
//				const QString& text, QWidget *parent = nullptr);

//	static int QuestionBox(MsgBox::Icon icon, const QString &title,
//				const QString& text, QWidget *parent = nullptr);


	explicit MsgBox(QWidget *parent = nullptr);
	~MsgBox();

	void SetIcon(MsgBox::Icon icon);
	void SetTitle(const QString& title);
	void SetText(const QString& text);
	void AddButton(QPushButton *btns);
	void SetButton(QList<QPushButton *> btns);

private slots:
	void on_BtnClose_clicked();
	void on_BtnMinimized_clicked();

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *);

private:
	Ui::MsgBox *ui;
	QMovie _Movie;
	bool _MousePressed;
	QPoint _MousePoint;
};

#endif // MSGBOX_H
