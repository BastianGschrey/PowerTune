#ifndef GPS_SERIAL_H
#define GPS_SERIAL_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>


class GPSSerial: public QObject {
    Q_OBJECT
private:
    QSerialPort *gps_serialPort;
    QSerialPortInfo *gps_serialPortInfo;
    QString *gps_serialBuffer;

    void parseSerialBuffer();

public:


    GPSSerial();
    ~GPSSerial();
    bool openSerialPort(QString portName,
                        QSerialPort::BaudRate baudRate = QSerialPort::Baud115200,
                        QSerialPort::DataBits dataBits = QSerialPort::Data8,
                        QSerialPort::Parity parity = QSerialPort::NoParity,
                        QSerialPort::StopBits stopBits = QSerialPort::OneStop,
                        QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl);
    void closeSerialPort();
    QList<QSerialPortInfo> listSerialPortsAvailable();
    QString getSerialPortName();
    int getSerialPortBaudRate();

signals:
    void serialReadyRead(QByteArray gpsPackage);

private slots:
    void handleSerialError(QSerialPort::SerialPortError error);
    void readSerial();
};

#endif // GPS_SERIAL_H
