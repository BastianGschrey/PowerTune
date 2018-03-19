TEMPLATE = app

QT += qml quick serialport serialbus network charts location positioning sensors concurrent
CONFIG += c++11
static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}


SOURCES += main.cpp \
    dashboard.cpp \
    serialport.cpp \
    appsettings.cpp \
    gopro.cpp \
    gps.cpp \
    obd.cpp \
    sensors.cpp \
    udpreceiver.cpp \
    datalogger.cpp \
    HaltechCAN.cpp \
    AdaptronicCAN.cpp \
    Apexi.cpp \
    Nissanconsult.cpp \
    AdaptronicSelect.cpp \
    connect.cpp \
    calculations.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    dashboard.h \
    serialport.h \
    appsettings.h \
    gopro.h \
    gps.h \
    obd.h \
    sensors.h \
    udpreceiver.h \
    datalogger.h \
    HaltechCAN.h \
    AdaptronicCAN.h \
    Apexi.h \
    Nissanconsult.h \
    AdaptronicSelect.h \
    connect.h \
    calculations.h


FORMS +=

DISTFILES +=


