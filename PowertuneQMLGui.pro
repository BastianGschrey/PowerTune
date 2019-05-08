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
    sensors.cpp \
    datalogger.cpp \
    Apexi.cpp \
    AdaptronicSelect.cpp \
    connect.cpp \
    calculations.cpp \
    udpreceiver.cpp \
    arduino.cpp \
    wifiscanner.cpp


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
    sensors.h \
    datalogger.h \
    Apexi.h \
    AdaptronicSelect.h \
    connect.h \
    calculations.h \
    udpreceiver.h \
    arduino.h \
    wifiscanner.h


FORMS +=

DISTFILES +=


