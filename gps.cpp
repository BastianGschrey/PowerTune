#include "gps.h"
#include "dashboard.h"
#include "connect.h"
#include <QDebug>
#include <QByteArrayMatcher>
#include <QTime>
#include <QTimer>

int initialized = 0;
int rateset = 0 ;
int baudrate;
QByteArray ACK10HZ = QByteArray::fromHex("b562050102");
QByteArray NACK10HZ = QByteArray::fromHex("b562050002");

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
    //connect(&m_timer, &QTimer::timeout, this, &GPS::handleTimeout);

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

    // now open the connection with the user settings again
    m_dashboard->setgpsFIXtype("open Serial " + portName);
    baudrate = Baud.toInt();
    //qDebug()<<"open GPS Port: "+portName;
    m_serialport->setPortName(portName);
    if (initialized == 1)
    {
      qDebug()<<"Already initialized";
      baudrate = 115200;
    }

    m_dashboard->setgpsFIXtype("Try Baudrate " );
    switch (baudrate)
    {
    case 2400:
        m_serialport->setBaudRate(QSerialPort::Baud2400);
        break;
    case 4800:
        m_serialport->setBaudRate(QSerialPort::Baud4800);
        break;
    case 9600:
        m_serialport->setBaudRate(QSerialPort::Baud9600);
        qDebug()<<"opening at 9600 Baud";
        break;
    case 19200:
        m_serialport->setBaudRate(QSerialPort::Baud19200);
        break;
    case 38400:
        m_serialport->setBaudRate(QSerialPort::Baud38400);
        qDebug()<<"opening at 38400 Baud";
        break;
    case 57600:
        m_serialport->setBaudRate(QSerialPort::Baud57600);
        qDebug()<<"opening at 57K Baud";
        break;
    case 115200:
        m_serialport->setBaudRate(QSerialPort::Baud115200);
        qDebug()<<"opening at 115K Baud";
        break;
    default:
        m_serialport->setBaudRate(QSerialPort::Baud9600);
        qDebug()<<"opening at default Baud";
        break;
    }

    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setStopBits(QSerialPort::OneStop);
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);


    if(m_serialport->open(QIODevice::ReadWrite) == false)
    {
        qDebug()<<"serial closed straight after opening ";
        GPS::closeConnection();
    }
    if (initialized == 0)
    {
        removeNMEAmsg();
        setGPSBAUD115();
    }
    if (initialized == 1)
    {
        setGPS10HZ();
    }

    // Timeout timer
    //m_timer.start(1000);

    //defineFinishLine();

}

void GPS::removeNMEAmsg()
{
    //disables all the NMEA mesages that we don't need ( we only need RMC and  GGA)
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
    //qDebug()<<"Sending command to initialize at 115K";
    m_dashboard->setgpsFIXtype("GPS set 115k");
    m_serialport->write(QByteArray::fromHex("b5620600140001000000d008000000c201000700070000000000c496"));
    m_serialport->waitForBytesWritten(4000);

    closeConnection1();

}
void GPS::setGPS10HZ()
{
    //Set Ublox GPS Update Rate to 10Hz
    //qDebug()<<"Switching to 10HZ";
    m_dashboard->setgpsFIXtype("GPS set 10HZ");
    m_serialport->write(QByteArray::fromHex("b562060806006400010001007a12"));
    m_serialport->waitForBytesWritten(4000);

}
void GPS::closeConnection()
{
    //qDebug()<<"close connection GPS";
    disconnect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    disconnect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
               this, &GPS::handleError);
        m_serialport->close();
    m_dashboard->setgpsFIXtype("close serial");
}
void GPS::closeConnection1()
{

    m_dashboard->setgpsFIXtype("close connection");
    disconnect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    disconnect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
               this, &GPS::handleError);
        m_serialport->close();
        initialized =1;
        m_dashboard->setgpsFIXtype("close serial");
   openConnection("ttyAMA0","115200");

}


void GPS::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
       m_dashboard->setgpsFIXtype(m_serialport->errorString());
        qDebug()<<" GPS Error ";
    }
}



void GPS::readyToRead()
{

 //   m_timer.stop();
   if(this->m_serialport->canReadLine()){
       QByteArray line = m_serialport->readLine();
    //   qDebug() <<"receiving "+ line  << endl;
   //QString line = QString(m_serialport->readLine());
       if(line.startsWith("$GPRMC"))
           processGPRMC(line);
       if(line.startsWith("$GPGGA"))
           processGPGGA(line);
       if(line.startsWith("$GNRMC"))
           processGPRMC(line);
       if(line.startsWith("$GNGGA"))
           processGPGGA(line);

       if ( rateset == 0)
       {
       if (line.contains(ACK10HZ))
       {
          m_dashboard->setgpsFIXtype("10Hz ACK");
          rateset = 1;
         // closeConnection1();

       }
       if (line.contains(NACK10HZ))
       {
          m_dashboard->setgpsFIXtype("10Hz NOCK");
          setGPS10HZ();

       }
       }

   }
  //  m_timer.start(1000);


}

void GPS::handleTimeout()
{
    m_dashboard->setgpsFIXtype("timeout./");
    closeConnection();
    initialized = 0;
    rateset = 0;
    openConnection("ttyAMA0","115200");
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
    if (speed < 2)
    {
        speed = 0; // this is to ensure we show 0 if we standing as GPS sometimes sends a value greater 0 when standing still
    }
    QString decLat = convertToDecimal(latitude, latDirection);
    QString decLon = convertToDecimal(longitude, lonDirection);


    m_dashboard->setgpsLatitude(decLat.toDouble());
    m_dashboard->setgpsLongitude(decLon.toDouble());
    m_dashboard->setgpsSpeed(qRound(speed));// round speed to the nearest integer
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

QString GPS::convertToDecimal(const QString & coord, const QString & dir){
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
  //  qDebug()<<"Finish Line Settings";
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
//qDebug()<<"current intercept" << currentintercept;
    if ((previousintercept <= 0 && currentintercept >= 0) || (previousintercept >= 0 && currentintercept <= 0) || (currentintercept == 0))
    {

        if (m_dashboard->gpsLongitude() <= startlineX2 && m_dashboard->gpsLongitude() >= startlineX1 )
        {
            qDebug()<<"Checknew Lap";
            if (m_timer.isValid() == true)
            {Laps++;
            qDebug() << "Line Crossed " << " Lap " << Laps;
            QTime y(0, 0);
            y = y.addMSecs(m_timer.elapsed());
            QString Laptime = y.toString("mm:ss.zzz");
            qDebug() << "Laptime" << Laptime;
            m_timer.restart();
            }
            else{
            m_timer.start();
            qDebug() << "Starting Lap Timer ";
            }
        }
    }
    previousintercept = currentintercept;
}
