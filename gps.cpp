#include "gps.h"
#include "dashboard.h"
#include "connect.h"
#include <QDebug>
#include <QByteArrayMatcher>
#include <QTime>
#include <QTimer>

int initialized = 0;
int rateset = 0 ;
int raterequ = 0;
int baudrate;
QByteArray ACK10HZ = QByteArray::fromHex("0501020006");
QByteArray NACK10HZ = QByteArray::fromHex("050002");
QByteArray line;
int Laps = 0;
double startlineX1 ; //Longitude
double startlineX2 ; //Longitude
double startlineY1 ; //Latitude
double startlineY2 ; //Latitude
double m;
double b;
double interrim;
double intercept;
double currentintercept;
double previousintercept;
int linedirection; // Direction of the finish line 0 = Latitude 1 = Longitude

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

void GPS::initSerialPort()
{
    m_serialport = new SerialPort(this);
    connect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    connect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &GPS::handleError);
    connect(&m_timeouttimer, &QTimer::timeout, this, &GPS::handleTimeout);
}

//function for flushing all serial buffers
void GPS::clear()
{
    m_serialport->clear();
}
//function to open serial port
void GPS::openConnection(const QString &portName,const QString &Baud)
{   
    initSerialPort();
    m_timeouttimer.start(5000);
    m_dashboard->setgpsFIXtype("open Serial " + portName);
    baudrate = Baud.toInt();
    m_serialport->setPortName(portName);

    m_dashboard->setgpsFIXtype("open with " + Baud );
    switch (baudrate)
    {
    case 9600:
        m_serialport->setBaudRate(QSerialPort::Baud9600);
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
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);


    if(m_serialport->open(QIODevice::ReadWrite) == false)
    {
        GPS::closeConnection();
    }


}

void GPS::removeNMEAmsg()
{
    //disables all the NMEA mesages that we don't need ( we only need RMC and  GGA)
    setGPSOnly();
    m_dashboard->setgpsFIXtype("Disable messages");
    m_serialport->write(QByteArray::fromHex("B56206010800F0050000000000000446")); //VTG OFF
    m_serialport->waitForBytesWritten(4000);
    m_serialport->write(QByteArray::fromHex("B56206010800F0020000000000000131")); //GSA_Off
    m_serialport->waitForBytesWritten(4000);
    m_serialport->write(QByteArray::fromHex("B56206010800F0030000000000000238")); //GSV_Off
    m_serialport->waitForBytesWritten(4000);
    m_serialport->write(QByteArray::fromHex("B56206010800F001000000000000002A")); //GLL_Off
    m_serialport->waitForBytesWritten(4000);
    m_serialport->write(QByteArray::fromHex("B56206010800F008000000000000075B")); //ZDA_Off
    m_serialport->waitForBytesWritten(4000);

}
void GPS::setGPSBAUD115()
{
    //Set Ublox GPS to use baudrate of 115200
    m_dashboard->setgpsFIXtype("GPS set 115k");
    m_serialport->write(QByteArray::fromHex("B5620600140001000000D008000000C201000700020000000000BF78"));
    m_serialport->waitForBytesWritten(4000);
    closeConnection1();
}
void GPS::setGPS10HZ()
{
    //Set Ublox GPS Update Rate to 10Hz
    m_dashboard->setgpsFIXtype("GPS set 10HZ");
    m_serialport->write(QByteArray::fromHex("b562060806006400010001007a12"));
    m_serialport->waitForBytesWritten(4000);

}
void GPS::setGPSOnly()
{
    // Switch on GPS only
    m_serialport->write(QByteArray::fromHex("B562063E2C0000201005000810000100010101010300000001010308100000000101050003000000010106080E00000001010CD1")); //GPS Only
    m_serialport->waitForBytesWritten(4000);

}
void GPS::closeConnection()
{
    disconnect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    disconnect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
               this, &GPS::handleError);
    disconnect(&m_timeouttimer, &QTimer::timeout, this, &GPS::handleTimeout);
    m_serialport->close();
    m_dashboard->setgpsFIXtype("close serial");
}
void GPS::closeConnection1()
{
    m_dashboard->setgpsFIXtype("close connection");
    disconnect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    disconnect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
               this, &GPS::handleError);
    disconnect(&m_timeouttimer, &QTimer::timeout, this, &GPS::handleTimeout);
    m_serialport->close();
    initialized =1;
    m_dashboard->setgpsFIXtype("close serial");
    openConnection("ttyAMA0","115200");
}

void GPS::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError)
    {
        m_dashboard->setgpsFIXtype(m_serialport->errorString());
    }
}

void GPS::readyToRead()
{    

    QByteArray rawData = m_serialport->readAll();          // read data from serial port
    //qDebug()<< "chunk " << rawData;
    line.append(rawData);
    if (line.contains("\r\n"))
    {
        int end = line.lastIndexOf("\r\n") + 2;
        QByteArray message = line;
        //qDebug()<< "line raw" << line;
        message.remove(end, line.length());
        //qDebug()<< "Processed Message" << message;
        line.remove(0,end);
        //qDebug()<< "line new" << line;
        ProcessMessage(message);
    }


/*
    for (int i=0; i < rawData.size(); i++)
    {
       //line << rawData[i];
       line.append(rawData);
       if (line.size() >= 2 && line[line.size()-2] == '\r' && line[line.size()-1] == '\n')
       {
          qDebug()<< "line " << line;
          //emit(line);
          line.clear();
       }
    }
*/
    /*
    if(this->m_serialport->canReadLine()){
        QByteArray line = m_serialport->readLine();
        if(line.startsWith("$GPRMC"))
            processGPRMC(line);
        m_timeouttimer.stop();


        */
    }
void GPS::ProcessMessage(QByteArray messageline)
{
    m_timeouttimer.stop();
    if(messageline.contains("$GNGGA"))
        if (rateset == 0)
        {
            //Use only GPS
            setGPS10HZ();
            rateset = 1;
        }
    if(messageline.startsWith("$GPGGA"))
    {
        processGPGGA(messageline);

    }
    if(line.startsWith("$GPRMC"))
    {
        processGPRMC(messageline);
    }
        /*
    if(messageline.startsWith("$GPVTG"))
    {
        processGPVTG(messageline);

    }
    */
    if (messageline.contains(ACK10HZ))
    {
        m_dashboard->setgpsFIXtype("10Hz ACK");
        rateset = 1;
        removeNMEAmsg();
        setGPSBAUD115();
    }


}

void GPS::handleTimeout()
{
    //Timeout will occur if the GPS was already initialized and still opened at 9600 Baud
    m_dashboard->setgpsFIXtype("Timeout");
    setGPSBAUD115();
    // closeConnection();
    // openConnection("ttyAMA0","115200");
}

void GPS::processGPRMC(const QString & line){
    QStringList fields = line.split(',');
    QString time = fields[1];
    time.insert(2,":");
    time.insert(5,":");
    QString latitude = fields[3];
    QString latDirection = fields[4];
    QString longitude = fields[5];
    QString lonDirection = fields[6];
    QString groundspeedknots = fields[7];
    QString bearing = fields[8];
    if (bearing != "")
    {
        //We update bearing only if we have a valid baering
        m_dashboard->setgpsbaering(bearing.toDouble());
    }

    double speed = groundspeedknots.toDouble() * 1.852;
    /*   if (speed < 2)
    {
        speed = 0; // this is to ensure we show 0 if we standing as GPS sometimes sends a value greater 0 when standing still
    }*/
    QString decLat = convertToDecimal(latitude, latDirection);
    QString decLon = convertToDecimal(longitude, lonDirection);


    m_dashboard->setgpsLatitude(decLat.toDouble());
    m_dashboard->setgpsLongitude(decLon.toDouble());
    m_dashboard->setgpsSpeed(qRound(speed));// round speed to the nearest integer
    m_dashboard->setgpsTime(time);
}

void GPS::processGPGGA(const QString & line)
{
    QStringList fields = line.split(',');
    int fixquality = fields[6].toInt();

    switch (fixquality) {
    case 0:
        m_dashboard->setgpsFIXtype("No fix yet");
        break;
    case 1:
        m_dashboard->setgpsFIXtype("GPS only");
        break;
    case 2:
        m_dashboard->setgpsFIXtype("DGPS");
        break;
    default:
        m_dashboard->setgpsFIXtype("No fix yet");
        break;
    }
    QString latitude = fields[2];
    QString latDirection = fields[3];
    QString longitude = fields[4];
    QString lonDirection = fields[5];
    QString decLat = convertToDecimal(latitude, latDirection);
    QString decLon = convertToDecimal(longitude, lonDirection);

    QString satelitesinview = fields[7];
    QString altitude = fields[9];
    m_dashboard->setgpsLatitude(decLat.toDouble());
    m_dashboard->setgpsLongitude(decLon.toDouble());
    m_dashboard->setgpsVisibleSatelites(satelitesinview.toInt());
    m_dashboard->setgpsAltitude(altitude.toDouble());

    checknewLap();
}

void GPS::processGPVTG(const QString & line)
{
    QStringList fields = line.split(',');
    QString speed = fields[7];
   // m_dashboard->setgpsSpeed(speed.toInt());

}
QString GPS::convertToDecimal(const QString & coord, const QString & dir)
{
    int decIndex = coord.indexOf('.');
    QString minutes = coord.mid(decIndex- 2);
    QString seconds = coord.mid(decIndex+1,2);
    double dec = minutes.toDouble() * 60 / 3600;
    double degrees = coord.mid(0, decIndex -2).toDouble();
    double decCoord = dec + degrees;
    if(dir == "W" || dir == "S")
        decCoord *= -1.0;
    return QString::number(decCoord,'f',6);
}


//Laptimer

void GPS::defineFinishLine(const double & Y1,const double & X1,const double & Y2,const double & X2)
{
    linedirection = 0;
    startlineX1 = X1; //Longitude
    startlineX2 = X2; //Longitude
    startlineY1 = Y1; //Latitude
    startlineY2 = Y2; //Latitude
    m = (startlineY1-startlineY2) / (startlineX1-startlineX2);
    b = startlineY1 - (m*startlineX1);
}

void GPS::checknewLap()
{
    currentintercept = m_dashboard->gpsLatitude() -( (m * m_dashboard->gpsLongitude()) + b);
    if ((previousintercept <= 0 && currentintercept >= 0) || (previousintercept >= 0 && currentintercept <= 0) || (currentintercept == 0))
    {

        if (m_dashboard->gpsLongitude() <= startlineX2 && m_dashboard->gpsLongitude() >= startlineX1 )
        {
            if (m_timer.isValid() == true)
            {Laps++;
                QTime y(0, 0);
                y = y.addMSecs(m_timer.elapsed());
                QString Laptime = y.toString("mm:ss.zzz");
                m_timer.restart();
            }
            else{
                m_timer.start();
            }
        }
    }
    previousintercept = currentintercept;
}
