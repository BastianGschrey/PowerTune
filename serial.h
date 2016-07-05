/*
 * Copyright (C) 2016 Markus Ippy, Bastian Gschrey, Jan
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

/*
  \file serial.h
  \brief Raspexi Viewer Power FC related functions
  \author Suriyan Laohaprapanon & Jacob Donley & Bastian Gschrey & Markus Ippy
 */


#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <serialsetting.h>


class Serial : public QObject
{
    Q_OBJECT

public:
    void clear() const;

public:
    explicit Serial(QObject *parent = 0);


    void closeConnection();
    void getAdvData();
    void getAux();
    void getSensorData();
    void getMapIndices();


private:
QSerialPort *serialport;


signals:
void finished();
void error(QString err);
void SIG_dataAvailable(QByteArray);

public slots:
    void readyToRead();
    void openConnection(SerialSetting::Settings p); //open serial connection with settings
    void sendRequest(int requestIndex);
};

#endif // SERIAL_H
