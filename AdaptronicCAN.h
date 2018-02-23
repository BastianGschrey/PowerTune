/*
 * Copyright (C) 2018 Markus Ippy, Bastian Gschrey,
 * use this program at your own risk.
  \file AdaptronicCAN.h
  \brief Receive Messages from Adaptronic Modular via CAN
  \author Markus Ippy, Bastian Gschrey
  \based on the information from http://www.adaptronic.com.au/files/Adap_config/Adaptronic_Full_Configuration.htm
 */

#ifndef AdaptronicCAN_H
#define AdaptronicCAN_H
#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>

class DashBoard;


class AdaptronicCAN : public QObject
{
    Q_OBJECT
public:

    explicit AdaptronicCAN(QObject *parent = 0);
    explicit AdaptronicCAN(DashBoard *dashboard, QObject *parent = 0);
    ~AdaptronicCAN();


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

#endif // AdaptronicCAN_H
