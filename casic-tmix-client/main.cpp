#include "mainwindow.h"

#include <QFile>
#include <QApplication>

#include "utils/softwareabout.h"
#include "easylog/easylogging++.h"
INITIALIZE_EASYLOGGINGPP

/**
 * @brief InitLog - 设置日志格式
 */
void InitLog()
{
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	defaultConf.setGlobally(el::ConfigurationType::ToFile, "true");
	defaultConf.setGlobally(el::ConfigurationType::Enabled, "true");
	defaultConf.setGlobally(el::ConfigurationType::Filename, SOFTWARE_PATH_LOG_MAINUI);
	defaultConf.setGlobally(el::ConfigurationType::Format, "[%datetime | %level] %loc : %msg");
	defaultConf.setGlobally(el::ConfigurationType::MaxLogFileSize, "20971520");
	defaultConf.setGlobally(el::ConfigurationType::LogFlushThreshold, "1");
	el::Loggers::reconfigureAllLoggers(defaultConf);
}

int main(int argc, char *argv[])
{
//	START_EASYLOGGINGPP(argc, argv);

    QApplication a(argc, argv);
//    QFile file(":/assets/basic.css");
//    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        a.setStyleSheet(QString::fromUtf8(file.readAll()));
//        file.close();
//    }

	MainWindow w;
	w.show();

	return a.exec();
}
