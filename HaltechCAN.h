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

  \file HaltechCAN.h
  \brief request and receive messages from Adaptronic Modular via CANBUS (socketcan
  \author Bastian Gschrey & Markus Ippy
 */

#ifndef HaltechCAN_H
#define HaltechCAN_H
#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>


class DashBoard;

class HaltechCAN : public QObject
{
    Q_OBJECT
public:

    explicit HaltechCAN(QObject *parent = 0);
    explicit HaltechCAN(DashBoard *dashboard, QObject *parent = 0);
    ~HaltechCAN();


public slots:
    void openCAN();
    void closeConnection();
public:


private:

    QCanBusDevice *m_canDevice;
    DashBoard *m_dashboard;
    double pkgpayload[8];
    struct payload{
       quint16 CH1;
       quint16 CH2;
       quint16 CH3;
       quint16 CH4;
       payload parse(const QByteArray &);
    };


signals:



public slots:
    void readyToRead();


};

#endif // HaltechCAN_H
