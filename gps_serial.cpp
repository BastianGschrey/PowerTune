#include "gps_serial.h"

GPSSerial::GPSSerial(): QObject() {
    gps_serialPort = new QSerialPort(this);
    gps_serialPortInfo = new QSerialPortInfo();
    gps_serialBuffer = new QString;

    connect(gps_serialPort, SIGNAL(readyRead()), this, SLOT(readSerial()));
    connect(gps_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleSerialError(QSerialPort::SerialPortError)));
}

GPSSerial::~GPSSerial() {
    this->closeSerialPort();
    delete gps_serialPort;
    delete gps_serialPortInfo;
    delete gps_serialBuffer;
}

bool GPSSerial::openSerialPort(QString portName,
                            QSerialPort::BaudRate baudRate,
                            QSerialPort::DataBits dataBits,
                            QSerialPort::Parity parity,
                            QSerialPort::StopBits stopBits,
                            QSerialPort::FlowControl flowControl) {
    this->closeSerialPort();
    gps_serialPort->setPortName(portName);
    gps_serialPort->setBaudRate(baudRate);
    gps_serialPort->setDataBits(dataBits);
    gps_serialPort->setParity(parity);
    gps_serialPort->setStopBits(stopBits);
    gps_serialPort->setFlowControl(flowControl);
    if (gps_serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened!";
        return true;
    } else {
        qDebug() << "Could not open Serial!";
        return false;
    }
}

void GPSSerial::closeSerialPort() {
    if (gps_serialPort->isOpen()) {
        gps_serialPort->close();
        qDebug() << "Serial port closed!";
    }
}

void GPSSerial::handleSerialError(QSerialPort::SerialPortError error) {
    if (error == QSerialPort::ResourceError) {
        this->closeSerialPort();
        qDebug() << "ERROR: Serial port Closed!";
    }
}

void GPSSerial::readSerial() {
    gps_serialBuffer->append(gps_serialPort->readAll());
    if(gps_serialBuffer->size()) {
        this->parseSerialBuffer();
    }
}

void GPSSerial::parseSerialBuffer() {
    if(gps_serialBuffer->left(6).compare("$GPGGA") == 0) {
        unsigned char subPackages = 0;
        for(int index = 0; index < gps_serialBuffer->size(); index++) {
            if(gps_serialBuffer->at(index) == '\n') {
                subPackages++;
                if(subPackages == 6) {
                    emit serialReadyRead(gps_serialBuffer->left(index + 1).toLocal8Bit());
                    gps_serialBuffer->remove(0, index + 1);
                }
            }
        }
    } else {
        qDebug() << "Removing incomplete package from gps serial buffer!";
        while(gps_serialBuffer->left(6).compare("$GPGGA") && gps_serialBuffer->size()) {
            gps_serialBuffer->remove(0, 1);
        }
    }
}

QList<QSerialPortInfo> GPSSerial::listSerialPortsAvailable() {
    return gps_serialPortInfo->availablePorts();
}

QString GPSSerial::getSerialPortName() {
    return gps_serialPort->portName();
}

int GPSSerial::getSerialPortBaudRate() {
    return gps_serialPort->baudRate();
}
