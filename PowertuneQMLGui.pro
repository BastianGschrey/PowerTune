TEMPLATE = app

QT += qml quick serialport serialbus network charts location positioning
CONFIG += c++11
static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}


SOURCES += main.cpp \
    serial.cpp \
    dashboard.cpp \
    decoder.cpp \
    serialport.cpp \
    appsettings.cpp \
    gopro.cpp \
    gps.cpp \
    nissanconsultcom.cpp \
    obd.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    serial.h \
    dashboard.h \
    decoder.h \
    serialport.h \
    appsettings.h \
    gopro.h \
    gps.h \
    nissanconsultcom.h \
    obd.h


FORMS +=

DISTFILES += \


