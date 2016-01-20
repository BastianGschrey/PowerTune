#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


class serial : public QObject
{
    Q_OBJECT
public:
    explicit serial(QObject *parent = 0);

private:
QSerialPort *serialport;

signals:

public slots:
};

#endif // SERIAL_H
