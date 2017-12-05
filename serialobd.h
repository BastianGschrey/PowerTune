#ifndef SERIALOBD_H
#define SERIALOBD_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QProcess>
#include <QThread>
#include <QObject>
#include <QTimer>

#include "pids.h"


class SerialOBD : public QObject
{
    Q_OBJECT
public:

    void RequestClusterData();
    void ParseAndReportClusterData(QByteArray data);
    void HexToDecimal(QByteArray sRPM, QByteArray sSpeed, QByteArray sFuelStatus, QByteArray sECoolantTemp,
                      QByteArray sThrottlePosition, QByteArray sTroubleCode);







signals:
    void obdRPM(int rpm);
    void obdMPH(int speed);
    void obdFuelStatus(int fuel);
    void obdCoolantTemp(int coolantTemp);
    void obdTroubleCode(QByteArray troublecode);
    void onEngineOff();

public slots:
    void ConnectToSerialPort();
    void EngineOff();

private:
    PIDs PID;
    QSerialPort m_serial;

    bool ArrayEngineOff[3] = {false};
    int m_tCodeCounter = 0;
    int m_engineOffcount = 0;
};

#endif // SERIALOBD_H
