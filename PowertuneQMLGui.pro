TEMPLATE = app

QT += qml quick serialport serialbus network charts location positioning sensors multimedia widgets

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
    datalogger.cpp \
    HaltechCAN.cpp \
    AdaptronicCAN.cpp \
    Apexi.cpp \
    Nissanconsult.cpp \
    AdaptronicSelect.cpp \
    connect.cpp \
    calculations.cpp \
    udpreceiver.cpp


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
    datalogger.h \
    HaltechCAN.h \
    AdaptronicCAN.h \
    Apexi.h \
    Nissanconsult.h \
    AdaptronicSelect.h \
    connect.h \
    calculations.h \
    udpreceiver.h


FORMS +=

DISTFILES +=


