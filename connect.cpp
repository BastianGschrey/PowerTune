/*
* Copyright (C) 2017 Bastian Gschrey & Markus Ippy
*
* Digital Gauges for Apexi Power FC for RX7 on Raspberry Pi
*
*
* This software comes under the GPL (GNU Public License)
* You may freely copy,distribute etc. this as long as the source code
* is made available for FREE.
*
* No warranty is made or implied. You use this program at your own risk.
*/

/*!
  \file Connect.cpp
  \brief Raspexi Viewer Power FC related functions
  \author Bastian Gschrey & Markus Ippy
*/

#include "datalogger.h"
#include "connect.h"
#include "calculations.h"
#include "sensors.h"
#include "AdaptronicSelect.h"
#include "AdaptronicCAN.h"
#include "Apexi.h"
#include "Nissanconsult.h"
#include "obd.h"
#include "dashboard.h"
#include "serialport.h"
#include "appsettings.h"
#include "gopro.h"
#include "gps.h"
#include "udpreceiver.h"
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QByteArrayMatcher>
#include <QProcess>







int ecu; //0=apex, 1=adaptronic;2= OBD; 3= Dicktator ECU
int logging; // 0 Logging off , 1 Logging to file
int connectclicked =0;
QByteArray checksumhex;
QByteArray recvchecksumhex;


Connect::Connect(QObject *parent) :
    QObject(parent),
    m_serialport(Q_NULLPTR),
    m_dashBoard(Q_NULLPTR),
    m_gopro(Q_NULLPTR),
    m_gps(Q_NULLPTR),
    m_udpreceiver(Q_NULLPTR),
    m_adaptronicselect(Q_NULLPTR),
    m_apexi(Q_NULLPTR),
    m_nissanconsult(Q_NULLPTR),
    m_OBD(Q_NULLPTR),
    m_sensors(Q_NULLPTR),
    m_adaptronicCAN(Q_NULLPTR),
    m_datalogger(Q_NULLPTR),
    m_calculations(Q_NULLPTR)

{

    getPorts();
    m_dashBoard = new DashBoard(this);
    m_appSettings = new AppSettings(this);
    m_gopro = new GoPro(this);
    m_gps = new GPS(m_dashBoard, this);
    m_adaptronicselect= new AdaptronicSelect(m_dashBoard, this);
    m_udpreceiver= new udpreceiver(m_dashBoard, this);
    m_apexi= new Apexi(m_dashBoard, this);
    m_nissanconsult = new Nissanconsult(m_dashBoard, this);
    m_OBD = new OBD(m_dashBoard, this);
    m_sensors = new Sensors(m_dashBoard, this);
    m_adaptronicCAN = new AdaptronicCAN(m_dashBoard, this);
    m_datalogger = new datalogger(m_dashBoard, this);
    m_calculations = new calculations(m_dashBoard, this);
    QString mPath = "/";
    // DIRECTORIES
    dirModel = new QFileSystemModel(this);
    // Set filter
    dirModel->setFilter(QDir::NoDotAndDotDot |QDir::AllDirs);
    // QFileSystemModel requires root path
    dirModel->setRootPath(mPath);
    fileModel = new QFileSystemModel(this);
    // Set filter
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    // QFileSystemModel requires root path
    fileModel->setRootPath(mPath);



    QQmlApplicationEngine *engine = dynamic_cast<QQmlApplicationEngine*>( parent );
    if (engine == Q_NULLPTR)
        return;
    engine->rootContext()->setContextProperty("Dashboard", m_dashBoard);
    engine->rootContext()->setContextProperty("AppSettings", m_appSettings);
    engine->rootContext()->setContextProperty("GoPro", m_gopro);
    engine->rootContext()->setContextProperty("GPS", m_gps);
    engine->rootContext()->setContextProperty("Nissanconsult",m_nissanconsult);
    engine->rootContext()->setContextProperty("Sens", m_sensors);
    engine->rootContext()->setContextProperty("Logger", m_datalogger);
    engine->rootContext()->setContextProperty("Calculations", m_calculations);
    engine->rootContext()->setContextProperty("Dirmodel", dirModel);
    engine->rootContext()->setContextProperty("Filemodel", fileModel);
    engine->rootContext()->setContextProperty("Apexi", m_apexi);  
}



Connect::~Connect()
{


}
void Connect::checkifraspberrypi()
{
  QString path = "/sys/class/backlight/rpi_backlight/brightness";
  if (QFileInfo::exists(path))
  {

       m_dashBoard->setscreen(true);

  }
  else
  {
      m_dashBoard->setscreen(false);
  }
}

void Connect::readdashsetup()
{
    QString path = "UserDash.txt";// this is just for testing
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList list = line.split(QRegExp("\\,"));
          m_dashBoard->setdashsetup(list);
       }
       inputFile.close();
    }

}

void Connect::setSreenbrightness(const int &brightness)
{

    //This works only on raspberry pi
    QFile f("/sys/class/backlight/rpi_backlight/brightness");
    //f.close();
    f.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream out(&f);
    out << brightness;
    //qDebug() << brightness;
    f.close();
}

void Connect::setUnits(const int &units)
{
    switch (units)
    {
    case 0:
        m_dashBoard->setunits("metric");
        break;
    case 1:
        m_dashBoard->setunits("imperial");
        break;

    default:
        break;
    }

}

void Connect::setWeight(const int &weight)
{
    m_dashBoard->setWeight(weight);
}

void Connect::setOdometer(const qreal &Odometer)
{
    m_dashBoard->setOdo(Odometer);
    m_calculations->start();
}
void Connect::qmlTreeviewclicked(const QModelIndex &index)
{
    QString mPath = dirModel->fileInfo(index).absoluteFilePath();
    //mPath.remove(0, 2); //this is needed for windows
    QString mPathnew = "file://" + mPath;
    m_dashBoard->setmusicpath(mPathnew);
}

void Connect::getPorts()
{
    QStringList PortList;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        PortList.append(info.portName());
    }
    setPortsNames(PortList);
    // Check available ports every 1000 ms
    QTimer::singleShot(1000, this, SLOT(getPorts()));
}
//function for flushing all Connect buffers
void Connect::clear() const
{
   // m_Connectport->clear();
}


//function to open Connect port
void Connect::openConnection(const QString &portName, const int &ecuSelect)
{


    ecu = ecuSelect;

    //Apexi
    if (ecuSelect == 0)
    {

        m_apexi->openConnection(portName);

    }


    //Adaptronic
    if (ecuSelect == 1)
    {
       m_adaptronicselect->openConnection(portName);

    }
    //OBD
    if (ecuSelect == 2)
    {
       m_OBD->openConnection(portName);
    }
    //Nissan Consult
    if (ecuSelect == 3)
    {
        //m_nissanconsult->LiveReqMsg(1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
        m_nissanconsult->openConnection(portName);

    }

    //UDP receiver
    if (ecu == 4)
    {
        m_udpreceiver->startreceiver();
    }
    //Adaptronic ModularCAN protocol
    if (ecuSelect == 5)
    {

        m_adaptronicCAN->openCAN();


    }

   /* //Dicktator
    if (ecuSelect == 9)
    {

        initConnectPort();
        m_Connectport->setPortName(portName);
        m_Connectport->setBaudRate(QConnectPort::Baud19200);
        m_Connectport->setParity(QConnectPort::NoParity);
        m_Connectport->setDataBits(QConnectPort::Data8);
        m_Connectport->setStopBits(QConnectPort::OneStop);
        m_Connectport->setFlowControl(QConnectPort::NoFlowControl);

        if(m_Connectport->open(QIODevice::ReadWrite) == false)
        {
            m_dashBoard->setConnectStat(m_Connectport->errorString());
        }
        else
        {
            m_dashBoard->setConnectStat(QString("Connected to Connectport"));
        }
    }*/

}
void Connect::closeConnection()
{

    m_calculations->stop();
    //Apexi
    if (ecu == 0)
    {

        m_apexi->closeConnection();

    }


    //Adaptronic Select
    if (ecu == 1)
    {
         m_adaptronicselect->closeConnection();

    }
    //OBD
    if (ecu == 2)
    {
       m_OBD->closeConnection();
    }
    //Nissan Consult
    if (ecu == 3)
    {
        m_nissanconsult->closeConnection();

    }
    //UDP receiver
    if (ecu == 4)
    {
        m_udpreceiver->closeConnection();
    }

    //Adaptronic ModularCAN protocol
    if (ecu == 5)
    {

        m_adaptronicCAN->closeConnection();

    }
}

void Connect::update()
{
    m_dashBoard->setSerialStat("Update started");
    QProcess *process = new QProcess(this);
    connect(process , SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(updatefinished(int, QProcess::ExitStatus)));
    process->start("/home/pi/updatePowerTune.sh");
    process->waitForFinished(6000000); // 10 minutes time before timeout
}

void Connect::shutdown()
{
    m_dashBoard->setSerialStat("Shutting Down");
    QProcess *process = new QProcess(this);
    process->start("sudo shutdown");
    process->waitForFinished(100); // 10 minutes time before timeout
}
void Connect::updatefinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "code" <<exitCode;
    qDebug() << "status" <<exitStatus;
    QString fileName = "/home/pi/build/PowertuneQMLGui";
    QFile file(fileName);
    if(QFileInfo::exists(fileName))
    {
        m_dashBoard->setSerialStat("Update Successful");
        file.close();
    }
    else
    {
        m_dashBoard->setSerialStat("Update Unsuccessful");
    }
}
/*
void Connect::handleError(QConnectPort::ConnectPortError ConnectPortError)
{
    if (ConnectPortError == QConnectPort::ReadError) {
        QString fileName = "Errors.txt";
        QFile mFile(fileName);
        if(!mFile.open(QFile::Append | QFile::Text)){
        }
        QTextStream out(&mFile);
        out << "Connect Error " << (m_Connectport->errorString()) <<endl;
        mFile.close();
        m_dashBoard->setConnectStat(m_Connectport->errorString());

    }
}

*/
/*
void Connect::readyToRead()
{

    if(ecu == 1)
    {


    }

    if(ecu == 9) //Dicktator ECU
    {
        m_readData = m_Connectport->readAll();
        Connect::dicktatorECU(m_readData);
        m_readData.clear();
    }

}

void Connect::dicktatorECU(const QByteArray &buffer)
{
    //Appending the message until the patterns Start and End Are found , then removing all bytes before and after the message
    m_buffer.append(buffer);
    QByteArray startpattern("START");
    QByteArrayMatcher startmatcher(startpattern);
    QByteArray endpattern("END");
    QByteArrayMatcher endmatcher(endpattern);
    int pos = 0;
    while((pos = startmatcher.indexIn(m_buffer, pos)) != -1)
    {

        if (pos !=0)
        {
            m_buffer.remove(0, pos);
        }
        if (pos == 0 ) break;
    }
    int pos2 = 0;
    while((pos2 = endmatcher.indexIn(m_buffer, pos2)) != -1)
    {


    if (pos2 > 30)
        {
            m_buffer.remove(0,pos2-30);
        }

        if (pos2 == 30 )
        {
            m_dicktatorMsg = m_buffer;
            m_buffer.clear();
            m_decoder->decodeDicktator(m_dicktatorMsg);
            break;
        }
    }

}
*/
