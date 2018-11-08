#include "speedo.h"
#include "dashboard.h"
#include "connect.h"
#include <QDebug>

Speedo::Speedo(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)
{
}

Speedo::Speedo(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}
void Speedo::initSerialPort()
{
    m_serialport = new SerialPort(this);
    connect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
 //   connect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
 //           this, &Speedo::handleError);
 //   connect(m_serialport, &QSerialPort::bytesWritten, this, &Apexi::handleBytesWritten);
 //   connect(&m_timer, &QTimer::timeout, this, &Apexi::handleTimeout);
    m_readData.clear();
    qDebug() << "initialized";
}
void Speedo::openConnection(const QString &portName)
{

    initSerialPort();
    m_serialport->setPortName("COM16");
    m_serialport->setBaudRate(QSerialPort::Baud57600);
    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setStopBits(QSerialPort::OneStop);
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);
   // m_dashboard->setSpeed(200);
    qDebug() << "connected";

}
void Speedo::readyToRead()
{
    qDebug() << "data available";
    m_readData = m_serialport->readLine();
    qDebug() << "test" << m_readData.toInt();
    m_dashboard->setSpeed(m_readData.toInt());


}
