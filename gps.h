#ifndef GPS_H
#define GPS_H
#include "serialport.h"
#include <QElapsedTimer>
#include <QTimer>

class DashBoard;
class Serialport;

class GPS : public QObject
{
    Q_OBJECT

public:
    explicit GPS(QObject *parent = 0);
    explicit GPS(DashBoard *dashboard, QObject *parent = 0);
    Q_INVOKABLE void defineFinishLine(const qreal & Y1,const qreal & X1,const qreal & Y2,const qreal & X2);
    Q_INVOKABLE void defineFinishLine2(const qreal & Y1,const qreal & X1,const qreal & Y2,const qreal & X2);
    Q_INVOKABLE void resetLaptimer();

private:
    DashBoard *m_dashboard;
    SerialPort *m_serialport;
    QByteArray  m_readData;
    QByteArray  m_buffer;
    QElapsedTimer m_timer;
    QTimer m_timeouttimer;
    QString convertToDecimal(const QString & coord, const QString & dir);
    void processGPRMC(const QString &line);
    void checklinecrossed();
    void linecrossed();
    void processGPGGA(const QString &line);
    void processGPVTG(const QString & line);
    void checknewLap();



public slots:
    //void delaytimer();
    void openConnection(const QString &portName,const QString &Baud);
    void ProcessMessage(QByteArray messageline);
    void removeNMEAmsg();
    void setGPSBAUD115();
    void setGPS10HZ();
    void setGPSOnly();
    void closeConnection();
    void closeConnection1();
    void clear();

private slots:
    void readyToRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);
    void initSerialPort();
signals:
    void sig_linecrossed();

};

#endif // GPS_H


/*
#ifndef GPS_H
#define GPS_H
#define _USE_MATH_DEFINES

#include <QDebug>
#include <vector>
#include <QDesktopServices>
#include <QUrl>
#include <cmath>
#include <map>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QQueue>
#include <QObject>


class DashBoard;

class GPS : public QObject
{

    Q_OBJECT





public:
    explicit GPS(QObject *parent = 0);
    explicit GPS(DashBoard *dashboard, QObject *parent = 0);


public slots:
    void startGPScom(const QString &portName,const int &baud);
    void stopGPScom();

signals:
    void portStatusChange(const bool &portStatus);
    void rmcUpde(const QString & rmcList);
private slots:
    void readLine();
    void printUpdate(const QString & update);
    void initSerialPort();


private:
    DashBoard *m_dashboard;
    QString convertToDecimal(const QString & coord, const QString & dir);
    void processLine(const QString &line);

    QSerialPort *com;
    QByteArray serialData;
    QString serialBuffer;
};

#endif // GPS_H
*/
