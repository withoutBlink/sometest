QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PROJECTPATH = $$PWD/..

DEFINES += \
        OPENSSL_NO_KRB5 \
        ASIO_STANDALONE \           # 使用本地asio库
        USE_STANDALONE_ASIO \       # 使用本地asio库


unix {
LIBS += \
        -lpthread \
        -luuid \
        -ludev \
        -ldl
}
macx {
INCLUDEPATH += \
        /usr/local/opt/openssl@1.1/include

LIBS += \
        -L/usr/local/opt/openssl@1.1/lib
}
win32 {

}


LIBS += \
    -lcrypto


INCLUDEPATH += \
        $$PROJECTPATH/common \
        $$PROJECTPATH/common/asio \
	$$PWD/pages \
        $$PWD/components \
        $$PWD/middleware


SOURCES += \
        $$PROJECTPATH/common/easylog/easylogging++.cc \
        $$PROJECTPATH/common/inifile/inifile.cpp \
        $$PWD/components/thermalmonitor.cpp \
	$$PWD/components/aboutusbox.cpp \
	$$PWD/components/ctlbtnbox.cpp \
	$$PWD/components/dashboard.cpp \
	$$PWD/components/inputbox.cpp \
        $$PWD/components/msgbox.cpp \
        $$PWD/middleware/wsroute.cpp \
        $$PWD/middleware/config.cpp \
        $$PWD/pages/pagetoolboxes.cpp \
        $$PWD/pages/pagejournal.cpp \
	$$PWD/pages/mainwindow.cpp \
	$$PWD/pages/pagehome.cpp \
	$$PWD/pages/pagetest.cpp \
        $$PWD/main.cpp \
    components/itemlistbox.cpp \
    components/tstatus.cpp


HEADERS += \
        $$PROJECTPATH/common/easylog/easylogging++.h \
	$$PROJECTPATH/common/utils/softwareabout.h \
        $$PROJECTPATH/common/inifile/inifile.h \
        $$PWD/middleware/config.h \
        $$PWD/middleware/wsroute.h \
        $$PWD/components/thermalmonitor.h \
	$$PWD/components/aboutusbox.h \
	$$PWD/components/ctlbtnbox.h \
	$$PWD/components/dashboard.h \
	$$PWD/components/inputbox.h \
	$$PWD/components/msgbox.h \
        $$PWD/pages/pagetoolboxes.h \
	$$PWD/pages/pagejournal.h \
        $$PWD/pages/mainwindow.h \
        $$PWD/pages/pagehome.h \
        $$PWD/pages/pagetest.h \
        components/itemlistbox.h \
    components/tstatus.h


FORMS += \
        $$PWD/components/thermalmonitor.ui \
	$$PWD/components/aboutusbox.ui \
	$$PWD/components/ctlbtnbox.ui \
	$$PWD/components/inputbox.ui \
	$$PWD/components/msgbox.ui \
        $$PWD/pages/pagetoolboxes.ui \
        $$PWD/pages/pagejournal.ui \
	$$PWD/pages/pagehome.ui \
	$$PWD/pages/pagetest.ui \
        $$PWD/pages/mainwindow.ui \
        components/itemlistbox.ui \
    components/tstatus.ui


RESOURCES += \
        $$PWD/resource.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../SendMSG.py


