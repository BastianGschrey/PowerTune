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


class SerialPort;
class Sensors;
class DashBoard;
class AdaptronicCAN;
class AdaptronicSelect;
class Apexi;
class HaltechCAN;
class Nissanconsult;
class OBD;
class datalogger;
class calculations;
class AppSettings;
class GoPro;
class GPS;
class OBD;


class Connect : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList portsNames READ portsNames WRITE setPortsNames NOTIFY sig_portsNamesChanged)

public:
    ~Connect();
    explicit Connect(QObject *parent = 0);
    Q_INVOKABLE void checkifraspberrypi();
    Q_INVOKABLE void readdashsetup();
    Q_INVOKABLE void setSreenbrightness(const int &brightness);
    Q_INVOKABLE void setUnits(const int &units);
    Q_INVOKABLE void setWeight(const int &weight);
    Q_INVOKABLE void clear() const;
    Q_INVOKABLE void openConnection(const QString &portName, const int &ecuSelect);
    Q_INVOKABLE void closeConnection();
    Q_INVOKABLE void update();





public:

    QStringList portsNames() const { return m_portsNames; }

private:
    SerialPort *m_serialport;
    DashBoard *m_dashBoard;
    AppSettings *m_appSettings;
    GoPro *m_gopro;
    GPS *m_gps;
    AdaptronicSelect *m_adaptronicselect;
    Apexi *m_apexi;
    Nissanconsult* m_nissanconsult;
    OBD* m_OBD;
    Sensors *m_sensors;
    HaltechCAN *m_haltechCANV2;
    AdaptronicCAN *m_adaptronicCAN;
    datalogger *m_datalogger;
    calculations *m_calculations;
    QStringList m_portsNames;
    QStringList *m_ecuList;
    QThread* CALCThread;
    QProcess process;



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


};



#endif // CONNECT_H
