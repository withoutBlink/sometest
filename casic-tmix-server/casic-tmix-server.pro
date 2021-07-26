TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= console
CONFIG -= qt

PROJECTPATH = $$PWD/..

DEFINES += \
        OPENSSL_NO_KRB5 \
        ASIO_STANDALONE \           # 使用本地asio库
        USE_STANDALONE_ASIO \       # 使用本地asio库

#contains(DEFINES, KOS) {
#    contains(DEFINES, SERVER) {
#        LIBS += -lrpm
#    }
#}

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
        -lcrypto \
        -lsensors \


INCLUDEPATH += \
        $$PROJECTPATH/common \
        $$PROJECTPATH/common/asio \

HEADERS += \
        $$PROJECTPATH/common/easylog/easylogging++.h \
        $$PROJECTPATH/common/utils/softwareabout.h \
        $$PROJECTPATH/common/utils/base64.hpp \
        $$PWD/src/wssrvroute.h \
        $$PWD/src/config.h \
    src/mdbmanager.h \
        src/rwlock.h \
    src/testcontrol.h


SOURCES += \
        $$PROJECTPATH/common/easylog/easylogging++.cc \
        $$PWD/src/wssrvroute.cpp \
	$$PWD/main.cpp \
        $$PWD/src/config.cpp \
    src/mdbmanager.cpp \
        src/rwlock.cpp \
    src/testcontrol.cpp
