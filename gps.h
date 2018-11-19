#ifndef GPS_H
#define GPS_H
#include "serialport.h"
#include <QTimer>

class DashBoard;
class Serialport;

class GPS : public QObject
{
    Q_OBJECT

public:
    explicit GPS(QObject *parent = 0);
    explicit GPS(DashBoard *dashboard, QObject *parent = 0);

private:
    DashBoard *m_dashboard;
    SerialPort *m_serialport;
    QByteArray  m_readData;
    QByteArray  m_buffer;
    QTimer      m_timer;
    QString convertToDecimal(const QString & coord, const QString & dir);
    void processLine(const QString &line);
    void processGPGGA(const QString &line);

public slots:
    //void delaytimer();
    void openConnection(const QString &portName,const QString &Baud);
    void closeConnection();
    void clear();

private slots:
    void readyToRead();
    void handleError(QSerialPort::SerialPortError error);
    void initSerialPort();
signals:

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
