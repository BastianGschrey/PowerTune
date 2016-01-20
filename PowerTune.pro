#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T18:23:49
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PowerTune
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serial.cpp \
    serialsetting.cpp

HEADERS  += mainwindow.h \
    serial.h \
    serialsetting.h

FORMS    += mainwindow.ui \
    serialsetting.ui
