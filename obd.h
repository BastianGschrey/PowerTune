/*
* file obd.h
* Copyright (C) 2018 Markus Ippy
*
* Communications class for OBD2 Live readouts
*
* No warranty is made or implied. You use this program at your own risk.
*/
#ifndef OBD_H
#define OBD_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QtSerialPort/QSerialPort>




namespace PIDS {
enum ENUM {
    SupportedPids0to20	= 0x00,
    Monitorstatus 		= 0x01,
    FreezeDTC 			= 0x02,
    FuelsystemStatus 	= 0x03,
    CalcEngLoad 		= 0x04,
    EngCoolantTemp 		= 0x05,
    ShortTermFueltrimB1 = 0x06,
    LongTermFueltrimB1 	= 0x07,
    ShortTermFueltrimB2 = 0x08,
    LongTermFueltrimB2  = 0x09,
    FuelPressure		= 0x0A,
    IntakeManifoldPress = 0x0B,
    EngineRPM			= 0x0C,
    VehicleSpeed	    = 0x0D,
    TimingAdvance 		= 0x0E,
    IntakeAirTemp		= 0x0F,
    MAFrate				= 0x10,
    ThrottlePosition	= 0x11,
    ComsecAirStatus		= 0x12,
    OxygenSenspresent	= 0x13,
    O2sensor1			= 0x14

};
}

class SerialPort;
class DashBoard;




class OBD : public QObject
{
    Q_OBJECT
public:


    explicit OBD(QObject *parent = 0);
    explicit OBD(DashBoard *dashboard, QObject *parent = 0);

    Q_INVOKABLE void clear() const;
    Q_INVOKABLE void initSerialPort();
    Q_INVOKABLE void openConnection(const QString &portName);
    Q_INVOKABLE void closeConnection();

public slots:


public:
    void writeRequest(QByteArray);

private:
    DashBoard *m_dashboard;
    SerialPort *m_serial;
    QStringList *m_ecuList;
    qint64      m_bytesWritten;
    QByteArray  m_readData;
    QTimer      m_timer;
    QByteArray  m_buffer;
    QByteArray  m_message;
    QByteArray  m_writeData;
    int         m_units;

signals:
    void sig_finished();
    void sig_error(QString err);
    void sig_ApexiDataAvailable(QByteArray);



public slots:
    void readyToRead();
    void handleTimeout();
    void handleBytesWritten(qint64 bytes);
    void handleError(QSerialPort::SerialPortError error);
    void messageconstructor(const QByteArray &buffer);
    void sendRequest(int requestIndex);
    void readData(QByteArray serialdata);

};

#endif // OBD_H
