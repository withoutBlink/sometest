#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();


private:
	void initStyle();
	void initConnect();
	void doubleClieckd();

protected:
	bool eventFilter(QObject *obj, QEvent *event);
	void resizeEvent(QResizeEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

signals:
	void StartWsRouter();

private slots:
	void onStarted(const QString& msg);
	void onSwitchPages();
	void onCallUI(const QString& msg);
	void on_BtnClose_clicked();
	void on_BtnMaximized_clicked(bool checked);
	void on_BtnMinimized_clicked();
	void on_BtnAboutUS_clicked();

private:
	Ui::MainWindow *ui;
	bool _MousePressed;
	QPoint _MousePoint;
	QThread _WsThread;
};
#endif // MAINWINDOW_H
