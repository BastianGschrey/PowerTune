
/*
 * Copyright (C) 2016 Bastian Gschrey & Markus Ippy
 *
 * Digital Gauges for Apexi Power FC for RX7 on Raspberry Pi
 *
 *
 * This software comes under the GPL (GNU Public License)
 * You may freely copy,distribute etc. this as long as the source code
 * is made available for FREE.
 *
 * No warranty is made or implied. You use this program at your own risk.
 */

/*!
  \file serial.cpp
  \brief Raspexi Viewer Power FC related functions
  \author Bastian Gschrey
  \credits to Suriyan Laohaprapanon & Jacob Donley
 */


#include "serial.h"
#include <QDebug>

Serial::Serial(QObject *parent) : QObject(parent)
{

//connect(this->serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));

//serialport = new QSerialPort(this); <- Defined in Header, constuctor heap allocation now allowed in a thread - will crash
}

QByteArray Serial::read() const
{
    return serialport->readAll();
}

//function for flushing all serial buffers
void Serial::clear() const
{
    serialport->clear();
}

//function to open serial port
void Serial::openConnection(SerialSetting::Settings p)
{
qDebug() << "Enter openConnection function";
serialport->setBaudRate(QSerialPort::Baud57600);
serialport->setPortName(p.portName);
serialport->setParity(serialport->NoParity);

serialport->setDataBits(QSerialPort::Data8);
serialport->setStopBits(QSerialPort::OneStop);
serialport->setFlowControl(QSerialPort::NoFlowControl);
qDebug() << "Try to open SerialPort:";

if(serialport->open(QIODevice::ReadWrite) == false)
{
qDebug() << serialport->errorString();
}
qDebug() << "Portname: " << p.portName;

}

void Serial::closeConnection()
{
serialport->close();
}


//Serial requests are send via Serial
void Serial::getAdvData()
{
    qDebug() << "getting Adv data...";
    serialport->write(QByteArray::fromHex("F0020D"));
}

void Serial::getSensorData()
{
    serialport->write(QByteArray::fromHex("DE021F"));
}

void Serial::getAux()
{
    serialport->write(QByteArray::fromHex("0002FD"));
}

void Serial::getMapIndices()
{
    serialport->write(QByteArray::fromHex("DB0222"));
}
//End of serial requests


void Serial::readyToRead()
{
    qDebug() <<"Signal readyRead fired by QSerialPort.";
    emit SIG_dataAvailable(this->read());
}


void Serial::sendRequest(int requestIndex)
{
    switch (requestIndex){
    case 0:
        Serial::getAdvData();
        requestIndex++;
        break;
    case 1:
        Serial::getAux();
        requestIndex++;
        break;
    case 2:
        Serial::getMapIndices();
        requestIndex++;
        break;
    case 3:
        Serial::getSensorData();
        requestIndex = 0;
        break;
    }
}

void Serial::process()
{
    serialport = new QSerialPort();
    connect(this->serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    qDebug() << "Hello from thread!!!";
}
