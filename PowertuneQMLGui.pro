TEMPLATE = app

QT += qml quick serialport serialbus
CONFIG += c++11

SOURCES += main.cpp \
    serial.cpp \
    dashboard.cpp \
    decoder.cpp \
    serialport.cpp \
    appsettings.cpp \
    adaptronic_decoder.cpp

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
    adaptronic_decoder.h

FORMS +=

DISTFILES +=

