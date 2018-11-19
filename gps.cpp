#include "gps.h"
#include "dashboard.h"
#include "connect.h"
#include <QDebug>
#include <QByteArrayMatcher>
#include <QTime>
#include <QTimer>


GPS::GPS(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)
{
}

GPS::GPS(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}
/*
void GPS::delaytimer()
{
    qDebug()<<"Delay";
    connect(&m_timer, &QTimer::timeout, this, &GPS::openConnection);
    qDebug()<<"start timer";
    m_timer.start(6000);
}
*/
void GPS::initSerialPort()
{
    m_serialport = new SerialPort(this);
    connect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    connect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &GPS::handleError);

}

//function for flushing all serial buffers
void GPS::clear()
{
    m_serialport->clear();
}


//function to open serial port
void GPS::openConnection(const QString &portName,const QString &Baud)
{
    int baudrate = Baud.toInt();
    m_timer.stop();
    qDebug()<<"open GPS Port: "+portName;
    initSerialPort();
    m_serialport->setPortName(portName);
    switch (baudrate) {
    case 2400:
        m_serialport->setBaudRate(QSerialPort::Baud2400);
        break;
    case 4800:
        m_serialport->setBaudRate(QSerialPort::Baud4800);
        break;
    case 9600:
        m_serialport->setBaudRate(QSerialPort::Baud9600);
        break;
    case 19200:
        m_serialport->setBaudRate(QSerialPort::Baud19200);
        break;
    case 38400:
        m_serialport->setBaudRate(QSerialPort::Baud38400);
        break;
    case 57600:
        m_serialport->setBaudRate(QSerialPort::Baud57600);
        break;
    case 115200:
        m_serialport->setBaudRate(QSerialPort::Baud115200);
        break;
    default:
        m_serialport->setBaudRate(QSerialPort::Baud9600);
        break;
    }

    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setStopBits(QSerialPort::OneStop);
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);;


    if(m_serialport->open(QIODevice::ReadWrite) == false)
    {
        qDebug()<<"serial closed straight after opening ";
        GPS::closeConnection();
    }

}
void GPS::closeConnection()
{
    qDebug()<<"close connection GPS";
    disconnect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    disconnect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
               this, &GPS::handleError);
        m_serialport->close();

}



void GPS::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
    qDebug()<<" GPS Error ";
    }
}



void GPS::readyToRead()
{

  //qDebug()<<"read GPS";
   if(this->m_serialport->canReadLine()){
       QString line = QString(m_serialport->readLine());
       if(line.startsWith("$GPRMC"))
           processLine(line);
       if(line.startsWith("$GPGGA"))
           processGPGGA(line);
      //qDebug()<< line;

   }

}



void GPS::processLine(const QString & line){
    QStringList fields = line.split(',');
    QString time = fields[1];
    time.insert(2,":");
    time.insert(5,":");
    QString latitude = fields[3];
    QString latDirection = fields[4];
    QString longitude = fields[5];
    QString lonDirection = fields[6];
    QString groundspeedknots = fields[7];
    double speed = groundspeedknots.toDouble() * 1.852;
    QString decLat = convertToDecimal(latitude, latDirection);
    QString decLon = convertToDecimal(longitude, lonDirection);


    m_dashboard->setgpsLatitude(decLat.toDouble());
    m_dashboard->setgpsLongitude(decLon.toDouble());
    m_dashboard->setgpsSpeed(speed);
    m_dashboard->setgpsTime(time);

}

void GPS::processGPGGA(const QString & line){
    //qDebug() <<"GPGGA "+ line  << endl;
    QStringList fields = line.split(',');
    int fixquality = fields[6].toInt();
    switch (fixquality) {
    case 0:
        m_dashboard->setgpsFIXtype("No fix !");
        break;
    case 1:
         m_dashboard->setgpsFIXtype("GPS only");
        break;
    case 2:
         m_dashboard->setgpsFIXtype("DGPS");
        break;
    default:
         m_dashboard->setgpsFIXtype("No fix !");
        break;
    }
    QString satelitesinview = fields[7];
    QString altitude = fields[9];
    m_dashboard->setgpsVisibleSatelites(satelitesinview.toInt());
    m_dashboard->setgpsAltitude(altitude.toDouble());


}

QString GPS::convertToDecimal(const QString & coord, const QString & dir){
    int decIndex = coord.indexOf('.');

    QString minutes = coord.mid(decIndex- 2);
    QString seconds = coord.mid(decIndex+1,2);
    double dec = minutes.toDouble() * 60 / 3600;
    double degrees = coord.mid(0, decIndex -2).toDouble();
    double decCoord = dec + degrees;
    if(dir == "W" || dir == "S")
        decCoord *= -1.0;
    return QString::number(decCoord);
}



