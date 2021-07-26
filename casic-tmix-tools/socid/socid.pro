TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

PROJECTPATH = $$PWD/../..

DEFINES += \
        OPENSSL_NO_KRB5 \
        ASIO_STANDALONE \           # 使用本地asio库
        USE_STANDALONE_ASIO         # 使用本地asio库

unix {
LIBS += \
        -lpthread \
        -ldl \
        -luuid \
        -ludev
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
    -lcrypto \
    -lpthread

INCLUDEPATH += \
        $$PROJECTPATH/common \
        $$PROJECTPATH/common/asio

SOURCES += \
        $$PROJECTPATH/common/easylog/easylogging++.cc \
        main.cpp \
        worker.cpp \
#        wsroute.cpp

HEADERS += \
        $$PROJECTPATH/common/easylog/easylogging++.h \
        worker.h \
#        wsroute.h
