
/*
 * OBD Communication by Claudio Tejada
 * Original code can be found on https://github.com/cjtejada/QtDigitalInstrumentCluster
 *
*/


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


class DashBoard;

class SerialOBD : public QObject
{
    Q_OBJECT
public:
    explicit SerialOBD(QObject *parent = 0);
    explicit SerialOBD(DashBoard *dashboard, QObject *parent = 0);
    Q_INVOKABLE void SelectPort(const QString &portName);



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
    DashBoard *m_dashboard;

    bool ArrayEngineOff[3] = {false};
    int m_tCodeCounter = 0;
    int m_engineOffcount = 0;
};

#endif // SERIALOBD_H
