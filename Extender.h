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

  \file Extender.h
  \brief request and receive messages from Adaptronic Modular via CANBUS (socketcan
  \author Bastian Gschrey & Markus Ippy
 */

#ifndef Extender_H
#define Extender_H
#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>


class DashBoard;

class Extender : public QObject
{
    Q_OBJECT
public:

    explicit Extender(QObject *parent = 0);
    explicit Extender(DashBoard *dashboard, QObject *parent = 0);
    ~Extender();


public slots:
    void openCAN(const int &ExtenderBaseID,const int &RPMCANBaseID);
     Q_INVOKABLE void variables(const qreal &Cylinder);
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
    double pkgpayload1[8];
    struct payload1{
       quint8 CH10;
       quint8 CH11;
       quint8 CH12;
       quint8 CH13;
       quint8 CH14;
       quint8 CH15;
       quint8 CH16;
       quint8 CH17;
       payload1 parse(const QByteArray &);
    };
    int         m_units;


signals:



public slots:
    void readyToRead();


};

#endif // Extender_H
