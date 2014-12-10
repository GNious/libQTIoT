#-------------------------------------------------
#
# Project created by QtCreator 2014-12-08T22:43:03
#
#-------------------------------------------------

QT       += network

TARGET = QTIoT
TEMPLATE = lib

DEFINES += QTIOT_LIBRARY
CONFIG += staticlib

SOURCES += qtiot.cpp\
    lightbulb.cpp \
    iotgateway.cpp \
    lifxlight.cpp \
    lifxgateway.cpp \
    lightbulbclient.cpp \
    iotgatewayclient.cpp \
    lifxlightclient.cpp \
    lifxgatewayclient.cpp \
    lifxpayload.cpp \
    powerswitchclient.cpp \
    iotobject.cpp \
    iotdiscoveryclient.cpp \
    lifxdiscoveryclient.cpp \
    lifxpacket.cpp \
    iottimer.cpp \
    iottimerclient.cpp

HEADERS += qtiot.h\
        qtiot_global.h\
    lightbulb.h \
    iotgateway.h \
    lifxlight.h \
    lifxgateway.h \
    lightbulbclient.h \
    iotgatewayclient.h \
    lifxlightclient.h \
    lifxgatewayclient.h \
    lifxpayload.h \
    LIFXConstants.h \
    powerswitchclient.h \
    iotobject.h \
    iotdiscoveryclient.h \
    lifxdiscoveryclient.h \
    lifxpacket.h \
    iottimer.h \
    iottimerclient.h \
    qtiotconstants.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
