#ifndef CONNECT_H
#define CONNECT_H

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
  \
  \author Bastian Gschrey & Markus Ippy
 */

#include <QtSerialPort/QSerialPort>
#include <QObject>
#include <QModbusDataUnit>
#include <QTimer>
#include <QProcess>
#include "calculations.h"
#include <QFileSystemModel>


class SerialPort;
class Sensors;
class DashBoard;
class AdaptronicSelect;
class Apexi;
class datalogger;
class calculations;
class AppSettings;
class GoPro;
class GPS;
class udpreceiver;
class Arduino;
class WifiScanner;


class Connect : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList portsNames READ portsNames WRITE setPortsNames NOTIFY sig_portsNamesChanged)

public:
    ~Connect();
    explicit Connect(QObject *parent = 0);
    Q_INVOKABLE void saveDashtoFile(const QString &filename,const QString &dashstring);
    Q_INVOKABLE void setfilename1(const QString &file1);
    Q_INVOKABLE void setfilename2(const QString &file2);
    Q_INVOKABLE void setfilename3(const QString &file3);
    Q_INVOKABLE void checkifraspberrypi();
    Q_INVOKABLE void readavailabledashfiles();
    Q_INVOKABLE void readavailablebackrounds();
    Q_INVOKABLE void setrpm(const int &dash1,const int &dash2,const int &dash3);
    Q_INVOKABLE void readMaindashsetup();
    Q_INVOKABLE void readdashsetup3();
    Q_INVOKABLE void readdashsetup2();
    Q_INVOKABLE void readdashsetup1();
    Q_INVOKABLE void setSreenbrightness(const int &brightness);
    Q_INVOKABLE void setSpeedUnits(const int &units1);
    Q_INVOKABLE void setUnits(const int &units);
    Q_INVOKABLE void setPressUnits(const int &units2);
    Q_INVOKABLE void setWeight(const int &weight);
    Q_INVOKABLE void setOdometer(const qreal &Odometer);
    Q_INVOKABLE void qmlTreeviewclicked(const QModelIndex &index);
    Q_INVOKABLE void clear() const;
    Q_INVOKABLE void checkReg();
    Q_INVOKABLE void checkOBDReg();
    Q_INVOKABLE void LiveReqMsgOBD(const QString &obdpids);
    Q_INVOKABLE void daemonstartup(const int &daemon);
    Q_INVOKABLE void canbitratesetup(const int &cansetting);
    Q_INVOKABLE void LiveReqMsg(const int &val1, const int &val2, const int &val3, const int &val4, const int &val5, const int &val6, const int &val7, const int &val8, const int &val9, const int &val10, const int &val11, const int &val12, const int &val13, const int &val14, const int &val15, const int &val16, const int &val17, const int &val18, const int &val19, const int &val20, const int &val21, const int &val22, const int &val23, const int &val24, const int &val25, const int &val26, const int &val27, const int &val28, const int &val29, const int &val30, const int &val31, const int &val32, const int &val33, const int &val34, const int &val35, const int &val36, const int &val37, const int &val38, const int &val39, const int &val40, const int &val41, const int &val42, const int &val43, const int &val44, const int &val45);
    Q_INVOKABLE void openConnection(const QString &portName, const int &ecuSelect);
    Q_INVOKABLE void closeConnection();
    Q_INVOKABLE void update();
    Q_INVOKABLE void changefolderpermission();
    Q_INVOKABLE void shutdown();
    Q_INVOKABLE void reboot();
    Q_INVOKABLE void turnscreen();
    Q_INVOKABLE void candump();
    Q_INVOKABLE void minicom();
    Q_INVOKABLE void RequestLicence();
    Q_INVOKABLE void restartDaemon();


public:

    QStringList portsNames() const { return m_portsNames; }

private:
    SerialPort *m_serialport;
    DashBoard *m_dashBoard;
    AppSettings *m_appSettings;
    GoPro *m_gopro;
    GPS *m_gps;
    udpreceiver *m_udpreceiver;
    AdaptronicSelect *m_adaptronicselect;
    Apexi *m_apexi;
    Sensors *m_sensors;
    datalogger *m_datalogger;
    calculations *m_calculations;
    QStringList m_portsNames;
    QStringList *m_ecuList;
    QProcess process;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    Arduino *m_arduino;
    WifiScanner *m_wifiscanner;



signals:
    void sig_portsNamesChanged(QStringList portsNames);

public slots:
    void updatefinished(int exitCode, QProcess::ExitStatus exitStatus);
    void getPorts();
    void setPortsNames(QStringList portsNames)
    {
        if (m_portsNames == portsNames)
            return;

        m_portsNames = portsNames;
        emit sig_portsNamesChanged(portsNames);
    }
    void processOutput();

};



#endif // CONNECT_H
