
#include "serialport.h"

SerialPort::SerialPort(QObject *parent) : QSerialPort(parent)
{
}

void SerialPort::setParity(const int &parity)
{
    switch (parity) {
    case 0:
        QSerialPort::setParity(QSerialPort::NoParity);
        break;
    case 1:
        QSerialPort::setParity(QSerialPort::EvenParity);
        break;
    case 2:
        QSerialPort::setParity(QSerialPort::OddParity);
        break;
    case 3:
        QSerialPort::setParity(QSerialPort::SpaceParity);
        break;
    case 4:
        QSerialPort::setParity(QSerialPort::MarkParity);
        break;
    default:
        break;
    }
}
