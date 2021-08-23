TEMPLATE = app
CONFIG += c++14
CONFIG -= app_bundle
CONFIG -= console
CONFIG -= qt

PROJECTPATH = $$PWD/..

DEFINES += \
#        OPENSSL_NO_KRB5 \
        ASIO_STANDALONE \           # local asio lib
        USE_STANDALONE_ASIO \       # local asio lib

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

#macx {
#INCLUDEPATH += \
#        /usr/local/opt/openssl@1.1/include

#LIBS += \
#        -L /usr/local/opt/openssl@1.1/lib
#}

#win32 {

#}

LIBS += \
        -lcrypto \
#        -lsensors \
        -lmariadbcpp


INCLUDEPATH += \
        $$PROJECTPATH/common \
        $$PROJECTPATH/common/asio

HEADERS += \
        $$PROJECTPATH/common/easylog/easylogging++.h \
        $$PROJECTPATH/common/utils/softwareabout.h \
        $$PROJECTPATH/common/utils/base64.hpp \
        $$PWD/src/wssroute.h \
        $$PWD/src/config.h \
        $$PWD/src/mdbmanager.h \
        $$PWD/src/rwlock.h \
        $$PWD/src/testcontrol.h \ \ \
    src/format.h


SOURCES += \
        $$PROJECTPATH/common/easylog/easylogging++.cc \
        $$PWD/src/wssroute.cpp \
	$$PWD/main.cpp \
        $$PWD/src/config.cpp \
        $$PWD/src/mdbmanager.cpp \
        $$PWD/src/rwlock.cpp \
        $$PWD/src/testcontrol.cpp \
    src/format.cpp
