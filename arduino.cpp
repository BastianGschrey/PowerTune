#include "arduino.h"
#include "dashboard.h"
#include "connect.h"
#include <QDebug>
#include <QByteArrayMatcher>

Arduino::Arduino(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)
{
}

Arduino::Arduino(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}

void Arduino::initSerialPort()
{
    m_serialport = new SerialPort(this);
    connect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    connect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &Arduino::handleError);
    m_readData.clear();
}

//function for flushing all serial buffers
void Arduino::clear()
{
    m_serialport->clear();
}


//function to open serial port
void Arduino::openConnection(const QString &portName)
{
    qDebug()<<"open Arduino  "+portName;

    initSerialPort();
    m_serialport->setPortName(portName);
    m_serialport->setBaudRate(QSerialPort::Baud38400);
    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setStopBits(QSerialPort::OneStop);
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);;

    if(m_serialport->open(QIODevice::ReadWrite) == false)
    {
        Arduino::closeConnection();
    }

}
void Arduino::closeConnection()
{
    disconnect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    disconnect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
               this, &Arduino::handleError);
        m_serialport->close();
}



void Arduino::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        QString fileName = "Errors.txt";
        QFile mFile(fileName);
        if(!mFile.open(QFile::Append | QFile::Text)){
        }
        QTextStream out(&mFile);
        out << "Serial Error " << (m_serialport->errorString()) <<endl;
        mFile.close();
        m_dashboard->setSerialStat(m_serialport->errorString());

    }
}



void Arduino::readyToRead()
{
    QByteArray test;
    test =m_readData = m_serialport->readAll();
    QString fileName = "AdaptronicOutputTest.txt";
    QFile mFile(fileName);
    if(!mFile.open(QFile::Append | QFile::Text)){
    }
    QTextStream out(&mFile);
    out  << (test.toHex()) <<endl;
    mFile.close();
    m_dashboard->setSerialStat(test.toHex());
    //qDebug()<< "Arduino"+m_readData;
    //Arduino::assemblemessage(m_readData);
}


void Arduino::assemblemessage(const QByteArray &buffer)
{


/*
    m_buffer.append(buffer);
    QByteArray startpattern = //828180//QByteArray::fromStdString("\r\n");
    QByteArrayMatcher endmatcher(endpattern);

    int pos = 0;
    while((pos = endmatcher.indexIn(m_buffer, pos)) != -1)
    {
        if (pos !=0)
        {
        QString raw = m_buffer;
         m_buffer.clear();
        if (raw.isEmpty())
        {raw ="0,0";}
        QStringList list = raw.split( "," );
        int ident =list[0].toInt();
        float Value =list[1].toFloat();

        switch(ident) {

        case 199:
            m_dashboard->setSpeed(Value);
            break;
        default:
            break;
        }

        }


}*/
}
