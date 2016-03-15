
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
serialport = new QSerialPort(this);
connect(this->serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));


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

Serial::getAdvData();
}

void Serial::closeConnection()
{
serialport->close();
}

void Serial::getAdvData()
{
    qDebug() << "Enter getAdvData function";
    serialport->write(QByteArray::fromHex("F0020D"));
}

void Serial::readyToRead()
{
    qDebug() <<"Signal readyRead fired be QSerialPort.";
    emit readyRead();
}
