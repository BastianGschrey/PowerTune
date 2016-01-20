#include "serial.h"


serial::serial(QObject *parent) : QObject(parent)
{
serialport = new QSerialPort(this);
}

