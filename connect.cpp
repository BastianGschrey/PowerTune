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
  \author Bastian Gschrey & Markus Ippy
*/

#include "datalogger.h"
#include "connect.h"
#include "calculations.h"
#include "sensors.h"
#include "AdaptronicSelect.h"
#include "Apexi.h"
#include "dashboard.h"
#include "serialport.h"
#include "appsettings.h"
#include "gopro.h"
#include "gps.h"
#include "udpreceiver.h"
#include "arduino.h"
#include "wifiscanner.h"
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
QString selectedPort;
QString dashfilename1;
QString dashfilename2;
QString dashfilename3;

Connect::Connect(QObject *parent) :
    QObject(parent),
    m_serialport(Q_NULLPTR),
    m_dashBoard(Q_NULLPTR),
    m_gopro(Q_NULLPTR),
    m_gps(Q_NULLPTR),
    m_udpreceiver(Q_NULLPTR),
    m_adaptronicselect(Q_NULLPTR),
    m_apexi(Q_NULLPTR),
    m_sensors(Q_NULLPTR),
    m_datalogger(Q_NULLPTR),
    m_calculations(Q_NULLPTR),
    m_arduino(Q_NULLPTR),
    m_wifiscanner(Q_NULLPTR)

{

    getPorts();
    m_dashBoard = new DashBoard(this);
    m_appSettings = new AppSettings(this);
    m_gopro = new GoPro(this);
    m_gps = new GPS(m_dashBoard, this);
    m_adaptronicselect= new AdaptronicSelect(m_dashBoard, this);
    m_udpreceiver= new udpreceiver(m_dashBoard, this);
    m_apexi= new Apexi(m_dashBoard, this);
    m_sensors = new Sensors(m_dashBoard, this);
    m_datalogger = new datalogger(m_dashBoard, this);
    m_calculations = new calculations(m_dashBoard, this);
    m_arduino = new Arduino(m_dashBoard, this);
    m_wifiscanner = new WifiScanner(m_dashBoard, this);
   // m_wifiscanner = new WifScanner(this);
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
    engine->rootContext()->setContextProperty("Sens", m_sensors);
    engine->rootContext()->setContextProperty("Logger", m_datalogger);
    engine->rootContext()->setContextProperty("Calculations", m_calculations);
    engine->rootContext()->setContextProperty("Dirmodel", dirModel);
    engine->rootContext()->setContextProperty("Filemodel", fileModel);
    engine->rootContext()->setContextProperty("Apexi", m_apexi);
    engine->rootContext()->setContextProperty("Arduino", m_arduino);
    engine->rootContext()->setContextProperty("Wifiscanner", m_wifiscanner);


}



Connect::~Connect()
{


}
void Connect::saveDashtoFile(const QString &filename,const QString &dashstring)
{
   //      qDebug()<<"Filename" << filename + "txt";
    QStringList fields = dashstring.split(QRegExp("[\r\n]"));
    QFile file( "/home/pi/UserDashboards/"+filename + ".txt" );
    //QFile file(filename + ".txt" );
    file.remove(); //remove file if it exists to avoid appending of existing file
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << dashstring << endl;
    }
    file.close();
}
void Connect::setfilename1(const QString &file1)
{
    dashfilename1 = file1;
}
void Connect::setfilename2(const QString &file2)
{
    dashfilename2 = file2;
}
void Connect::setfilename3(const QString &file3)
{
    dashfilename3 = file3;
}
void Connect::setrpm(const int &dash1,const int &dash2,const int &dash3)
{
    //qDebug()<<"rpm source" << dash1<< dash2<< dash3;
    m_dashBoard->setrpmstyle1(dash1);
    m_dashBoard->setrpmstyle2(dash2);
    m_dashBoard->setrpmstyle3(dash3);
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
void Connect::readavailabledashfiles()
{
    //QDir directory(""); //for Windows
    QDir directory("/home/pi/UserDashboards");
    QStringList dashfiles = directory.entryList(QStringList() << "*.txt",QDir::Files);
    m_dashBoard->setdashfiles(dashfiles);
    //qDebug() <<"files" << dashfiles ;
}

void Connect::readavailablebackrounds()
{
    //QDir directory(""); //for Windows
    QDir directory("/home/pi/Logo");
    QStringList dashfiles = directory.entryList(QStringList() << "*.png",QDir::Files);
    dashfiles.prepend("None");
    m_dashBoard->setbackroundpictures(dashfiles);
}

void Connect::readMaindashsetup()
{
    //QString path = "MainDash.txt";//for Windows
    QString path = "/home/pi/UserDashboards/MainDash.txt";
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list = line.split(QRegExp("\\,"));
            m_dashBoard->setmaindashsetup(list);
        }
        inputFile.close();
    }

}
void Connect::readdashsetup3()
{

    //QString path = dashfilename1;//for Windows
    QString path = "/home/pi/UserDashboards/"+dashfilename3;
    QFile inputFile(path);
    //QStringList list;
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list;
            if (line.contains("gauge")){
            list = line.split(QRegExp("\\,"));
            }
            else
            {
             line.prepend("Square gauge,");
             list = line.split(QRegExp("\\,"));
            }
            list.removeAll(QString(""));
            m_dashBoard->setdashsetup3(list);
        }
        inputFile.close();
    }

}
void Connect::readdashsetup2()
{

    //QString path = dashfilename1;//for Windows
    QString path = "/home/pi/UserDashboards/"+dashfilename2;
    QFile inputFile(path);
    //QStringList list;
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list;
            if (line.contains("gauge")){
            list = line.split(QRegExp("\\,"));
            }
            else
            {
             line.prepend("Square gauge,");
             list = line.split(QRegExp("\\,"));
            }
            list.removeAll(QString(""));
            m_dashBoard->setdashsetup2(list);
        }
        inputFile.close();
    }

}
void Connect::readdashsetup1()
{

    //QString path = dashfilename1;//for Windows
    QString path = "/home/pi/UserDashboards/"+dashfilename1;
    QFile inputFile(path);
    //QStringList list;
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list;
            if (line.contains("gauge")){
            list = line.split(QRegExp("\\,"));
            }
            else
            {
             line.prepend("Square gauge,");
             list = line.split(QRegExp("\\,"));
            }
            list.removeAll(QString(""));
            m_dashBoard->setdashsetup1(list);
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
void Connect::setSpeedUnits(const int &units1)
{
    switch (units1)
    {
    case 0:
        m_dashBoard->setspeedunits("metric");
        break;
    case 1:
        m_dashBoard->setspeedunits("imperial");
        break;

    default:
        break;
    }

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
void Connect::setPressUnits(const int &units2)
{

    switch (units2)
    {
    case 0:
        m_dashBoard->setpressureunits("metric");
        break;
    case 1:
        m_dashBoard->setpressureunits("imperial");
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
// Reads the file of supported OBD PIDS and makes it available to QML for the User to select which PIDS should be polled 
void Connect::checkOBDReg() 
{
    int i = 0;
    bool ok;
    QStringList list;

    QString path = "/home/pi/daemons/OBDPIDS.txt";
    // QString path = "SupportedPIDS.txt";
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            list = line.split(QRegExp("\\,"));
        }
        inputFile.close();
    }
    while (i < list.length()) {
        //qDebug()<< "Enter Loop" <<i;
        int pidread = (list[i].toInt(&ok, 16));
        m_dashBoard->setsupportedReg(pidread);
        //qDebug()<< "Reading" << list[i];
        i ++;
    }

}

void Connect::checkReg()
{
    int i = 0;
    bool ok;
    QStringList list;
    //QString path = "Regs.txt";
    QString path = "/home/pi/daemons/Regs.txt";
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            list = line.split(QRegExp("\\,"));
        }
        inputFile.close();
    }
    while (i < list.length()) {
        qDebug()<< "Read supported Consult Reg" <<list[i];
        switch (list[i].toInt(&ok, 16))
        {

        case 0x00:
            m_dashBoard->setsupportedReg(0);
            i ++;
            break;
        case 0x01:
            m_dashBoard->setsupportedReg(1);
            i ++;
            break;
        case 0x02:
            m_dashBoard->setsupportedReg(2);
            i ++;
            break;
        case 0x03:
            m_dashBoard->setsupportedReg(3);
            i ++;
            break;
        case 0x04:
            m_dashBoard->setsupportedReg(4);
            i ++;
            break;
        case 0x05:
            m_dashBoard->setsupportedReg(5);
            i ++;
            break;
        case 0x06:
            m_dashBoard->setsupportedReg(6);
            i ++;
            break;
        case 0x07:
            m_dashBoard->setsupportedReg(7);
            i ++;
            break;
        case 0x08:
            m_dashBoard->setsupportedReg(8);
            i ++;
            break;
        case 0x09:
            m_dashBoard->setsupportedReg(9);
            i ++;
            break;
        case 0x0a:
            m_dashBoard->setsupportedReg(10);
            i ++;
            break;
        case 0x0b:
            m_dashBoard->setsupportedReg(11);
            i ++;
            break;
        case 0x0c:
            m_dashBoard->setsupportedReg(12);
            i ++;
            break;
        case 0x0d:
            m_dashBoard->setsupportedReg(13);
            i ++;
            break;
        case 0x0f:
            m_dashBoard->setsupportedReg(14);
            i ++;
            break;
        case 0x11:
            m_dashBoard->setsupportedReg(15);
            i ++;
            break;
        case 0x12:
            m_dashBoard->setsupportedReg(16);
            i ++;
            break;
        case 0x13:
            m_dashBoard->setsupportedReg(17);
            i ++;
            break;
        case 0x14:
            m_dashBoard->setsupportedReg(18);
            i ++;
            break;
        case 0x15:
            m_dashBoard->setsupportedReg(19);
            i ++;
            break;
        case 0x16:
            m_dashBoard->setsupportedReg(20);
            i ++;
            break;
        case 0x17:
            m_dashBoard->setsupportedReg(21);
            i ++;
            break;
        case 0x1a:
            m_dashBoard->setsupportedReg(22);
            i ++;
            break;
        case 0x1b:
            m_dashBoard->setsupportedReg(23);
            i ++;
            break;
        case 0x1c:
            m_dashBoard->setsupportedReg(24);
            i ++;
            break;
        case 0x1d:
            m_dashBoard->setsupportedReg(25);
            i ++;
            break;
        case 0x1e:
            m_dashBoard->setsupportedReg(26);
            i ++;
            break;
        case 0x1f:
            m_dashBoard->setsupportedReg(27);
            i ++;
            break;
        case 0x21:
            m_dashBoard->setsupportedReg(28);
            i ++;
            break;
        case 0x22:
            m_dashBoard->setsupportedReg(29);
            i ++;
            break;
        case 0x23:
            m_dashBoard->setsupportedReg(30);
            i ++;
            break;
        case 0x28:
            m_dashBoard->setsupportedReg(31);
            i ++;
            break;
        case 0x29://corrct
            m_dashBoard->setsupportedReg(32);
            i ++;
            break;
        case 0x2a://corrct
            m_dashBoard->setsupportedReg(33);
            i ++;
            break;
        case 0x2e://corrct
            m_dashBoard->setsupportedReg(34);
            i ++;
            break;
        case 0x25://corrct
            m_dashBoard->setsupportedReg(35);
            i ++;
            break;
        case 0x26://corrct
            m_dashBoard->setsupportedReg(36);
            i ++;
            break;
        case 0x27://corrct
            m_dashBoard->setsupportedReg(37);
            i ++;
            break;
        case 0x2f:
            m_dashBoard->setsupportedReg(38);
            i ++;
            break;
        case 0x30:
            m_dashBoard->setsupportedReg(39);
            i ++;
            break;
        case 0x31:
            m_dashBoard->setsupportedReg(40);
            i ++;
            break;
        case 0x32:
            m_dashBoard->setsupportedReg(41);
            i ++;
            break;
        case 0x33:
            m_dashBoard->setsupportedReg(42);
            i ++;
            break;
        case 0x34:
            m_dashBoard->setsupportedReg(43);
            i ++;
            break;
        case 0x35:
            m_dashBoard->setsupportedReg(44);
            i ++;
            break;
        case 0x36:
            m_dashBoard->setsupportedReg(45);
            i ++;
            break;
        case 0x37:
            m_dashBoard->setsupportedReg(46);
            i ++;
            break;
        case 0x38:
            m_dashBoard->setsupportedReg(47);
            i ++;
            break;
        case 0x39:
            m_dashBoard->setsupportedReg(48);
            i ++;
            break;
        case 0x3a:
            m_dashBoard->setsupportedReg(49);
            i ++;
            break;
        case 0x4a:
            m_dashBoard->setsupportedReg(50);
            i ++;
            break;
        case 0x52:
            m_dashBoard->setsupportedReg(51);
            i ++;
            break;
        case 0x53:
            m_dashBoard->setsupportedReg(52);
            i ++;
            break;
        case 0xFE:
            //Not supported Register
            i ++;
            break;

        default:
            break;
        }
    }

}

void Connect::LiveReqMsgOBD(const QString &obdpids)
{
    qDebug()<< "PIDS" <<obdpids;
    QString Message;
    QStringList list = obdpids.split( "," );
    //qDebug()<< "Raw list" <<list;
    QString fileName = "/home/pi/daemons/OBD.cfg";//This will be the correct path on pi
    //QString fileName = "OBD.cfg";//for testing on windows
    QFile mFile(fileName);
    mFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    int i =0;
    while(i < list.length())
    {
        if (list[i] == "2")
        {
            // qDebug()<< "i" <<i;
            QString hexadecimal;
            hexadecimal.setNum(i,16);
            if(hexadecimal.length() %2)hexadecimal.insert(0,QLatin1String("0"));
            // qDebug()<< "Hex" <<hexadecimal;
            Message.append("0x"+hexadecimal);
            Message.append(",");
        }
        i++;
    }
    Message.remove(Message.length()-1,1); //Remove the last Comma
    //qDebug()<< "PID LST" <<Message;
    QTextStream out(&mFile);
    out << Message;
    mFile.close();

    //Reboot the PI for settings to take Effect
    m_dashBoard->setSerialStat("Rebooting ");
    QProcess *process = new QProcess(this);
    process->start("sudo reboot");
    process->waitForFinished(100); // 10 minutes time before timeout
}

void Connect::daemonstartup(const int &daemon)
{
    QString daemonstart;
    switch (daemon)
    {
    case 0:
        daemonstart = "";
        break;
    case 1:
        daemonstart = "./Haltechd";
        break;
    case 2:
        daemonstart = "./Linkd";
        break;
    case 3:
        daemonstart = "./Microtechd";
        break;
    case 4:
        daemonstart = "./Consult /dev/ttyUSB0";
        break;
    case 5:
        daemonstart = "./Apexid /dev/ttyUSB0";
        break;
    case 6:
        daemonstart = "./OBD /dev/ttyUSB0";
        break;

    }
    QString fileName = "/home/pi/startdaemon.sh";//This will be the correct path on pi
    //QString fileName = "startdaemon.sh";//for testing on windows
    QFile mFile(fileName);
    mFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream out(&mFile);
    out << "#!/bin/sh"
        << endl
        << "cd /home/pi/daemons"
        << endl
        << daemonstart
        << endl;
    mFile.close();

    //Reboot the PI for settings to take Effect
    m_dashBoard->setSerialStat("Rebooting ");
    QProcess *process = new QProcess(this);
    process->start("sudo reboot");
    process->waitForFinished(100); // 10 minutes time before timeout
}

void Connect::LiveReqMsg(const int &val1, const int &val2, const int &val3, const int &val4, const int &val5, const int &val6, const int &val7, const int &val8, const int &val9, const int &val10, const int &val11, const int &val12, const int &val13, const int &val14, const int &val15, const int &val16, const int &val17, const int &val18, const int &val19, const int &val20, const int &val21, const int &val22, const int &val23, const int &val24, const int &val25, const int &val26, const int &val27, const int &val28, const int &val29, const int &val30, const int &val31, const int &val32, const int &val33, const int &val34, const int &val35, const int &val36, const int &val37, const int &val38, const int &val39, const int &val40, const int &val41, const int &val42, const int &val43, const int &val44 , const int &val45)
{
    QString Message;

    if (val1 == 2)
    {Message.append("0x00,0x01,");}//RPM}
    if (val2 == 2)
    {Message.append("0x02,0x03,");}//RPMREF}
    if (val3 == 2)
    {Message.append("0x04,0x05,");}//MAFVoltage}
    if (val4 == 2)
    {Message.append("0x06,0x07,");}//RHMAFVoltage}
    if (val5 == 2)
    {Message.append("0x08,");}//Coolant Temp}
    if (val6 == 2)
    {Message.append("0x09,");}//LH 02 volt}
    if (val7 == 2)
    {Message.append("0x0a,");}//RH 02 volt}
    if (val8 == 2)
    {Message.append("0x0b,");}//Speed}
    if (val9 == 2)
    {Message.append("0x0c,");}//Battery Voltage}
    if (val10 == 2)
    {Message.append("0x0d,");}//TPS Voltage}
    if (val11 == 2)
    {Message.append("0x0f,");}//FuelTemp}
    if (val12 == 2)
    {Message.append("0x11,");}//Intake Temp}
    if (val13 == 2)
    {Message.append("0x12,");}//EGT}
    if (val14 == 2)
    {Message.append("0x13,");}//Digital Bit Register}
    if (val15 == 2)
    {Message.append("0x14,0x15,");}//Injection Time (LH)}
    if (val16 == 2)
    {Message.append("0x16,");}//Ignition Timing}
    if (val17 == 2)
    {Message.append("0x17,");}//AAC Valve (Idle Air Valve %)}
    if (val18 == 2)
    {Message.append("0x1a,");}//A/F ALPHA-LH}
    if (val19 == 2)
    {Message.append("0x1b,");}//A/F ALPHA-RH}
    if (val20 == 2)
    {Message.append("0x1c,");}//A/F ALPHA-LH (SELFLEARN)}
    if (val21 == 2)
    {Message.append("0x1d,");}//A/F ALPHA-RH (SELFLEARN)}
    if (val22 == 2)
    {Message.append("0x1e,");}//Digital Control Register 1}
    if (val23 == 2)
    {Message.append("0x1f,");}//Digital Control Register 2}
    if (val24 == 2)
    {Message.append("0x21,");}//M/R F/C MNT}
    if (val25 == 2)
    {Message.append("0x22,0x23,");}//Injector time (RH)}
    if (val26 == 2)
    {Message.append("0x28,");}//Waste Gate Solenoid %}
    if (val27 == 2)
    {Message.append("0x29,");}//Turbo Boost Sensor, Voltage}
    if (val28 == 2)
    {Message.append("0x2a,");}//Engine Mount On/Off}
    if (val29 == 2)
    {Message.append("0x2e,");}//Position Counter}
    if (val30 == 2)
    {Message.append("0x25,");}//Purg. Vol. Control Valve, Step}
    if (val31 == 2)
    {Message.append("0x26,");}//Tank Fuel Temperature, C}
    if (val32 == 2)
    {Message.append("0x27,");}//FPCM DR, Voltage}
    if (val33 == 2)
    {Message.append("0x2f,");}//Fuel Gauge, Voltage}
    if (val34 == 2)
    {Message.append("0x30,");}//FR O2 Heater-B1}
    if (val35 == 2)
    {Message.append("0x31,");}//FR O2 Heater-B2}
    if (val36 == 2)
    {Message.append("0x32,");}//Ignition Switch}
    if (val37 == 2)
    {Message.append("0x33,");}//CAL/LD Value, %}
    if (val38 == 2)
    {Message.append("0x34,");}//B/Fuel Schedule, mS}
    if (val39 == 2)
    {Message.append("0x35,");}//RR O2 Sensor Voltage}
    if (val40 == 2)
    {Message.append("0x36,");}//RR O2 Sensor-B2 Voltage}
    if (val41 == 2)
    {Message.append("0x37,");}//Absolute Throttle Position, Voltage }
    if (val42 == 2)
    {Message.append("0x38,");}//MAF gm/S}
    if (val43 == 2)
    {Message.append("0x39,");}//Evap System Pressure, Voltage}
    if (val44 == 2)
    {Message.append("0x3a,0x4a,");}//Absolute Pressure Sensor,Voltage}
    if (val45 == 2)
    {Message.append("0x52,0x53,");}//FPCM F/P Voltage}
    Message.remove(Message.length()-1,1); // remove the last comma from string
    //qDebug()<< "write" <<Message;


    QString fileName = "/home/pi/daemons/Consult.cfg";//This will be the correct path on pi
    //QString fileName = "Consult.cfg";//for testing on windows
    QFile mFile(fileName);
    mFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

    QTextStream out(&mFile);
    out << Message;
    mFile.close();

    //Reboot the PI for settings to take Effect
    m_dashBoard->setSerialStat("Rebooting ");
    QProcess *process = new QProcess(this);
    process->start("sudo reboot");
    process->waitForFinished(100); // 10 minutes time before timeout

}
void Connect::openConnection(const QString &portName, const int &ecuSelect)
{
    ecu = ecuSelect;
    selectedPort = portName;

    //Apexi
    if (ecuSelect == 0)
    {

        m_apexi->openConnection(portName);

    }

    //UDP receiver
    if (ecu == 1)
    {
        m_udpreceiver->startreceiver();
    }
    //Adaptronic
    if (ecuSelect == 2)
    {
        m_adaptronicselect->openConnection(portName);

    }

    //Adaptronic ModularCAN protocol
    if (ecuSelect == 3)
    {
        QProcess *process = new QProcess(this);
        process->start("/home/pi/Adaptronic/AdaptronicCAN");
        m_udpreceiver->startreceiver();
    }
    if (ecuSelect == 4)
    {
        //NissanConsult
        //QProcess *process = new QProcess(this);
        //process->start("/home/pi/Consult/Consult /dev/"+(portName));
        //qDebug() << "/dev/"+(portName);
        m_udpreceiver->startreceiver();
    }
    if (ecuSelect == 5)
    {
        //HaltechV1
        QProcess *process = new QProcess(this);
        process->start("/home/pi/Haltech/HaltechV1");
        m_udpreceiver->startreceiver();
    }
    if (ecuSelect == 6)
    {
        //HaltechV2
        m_dashBoard->setFlagString1("Clutch");
        m_dashBoard->setFlagString2("Brake");
        m_dashBoard->setFlagString3("TransThrottle");
        m_dashBoard->setFlagString4("Decel Cut");
        m_dashBoard->setFlagString5("Gear Switch");
        m_dashBoard->setFlagString6("Torque Red.");
        m_dashBoard->setFlagString7("Flat Shift");
        m_dashBoard->setFlagString8("Aux RPM Limit");
        m_dashBoard->setFlagString9("Antilag");
        m_dashBoard->setFlagString10("MIL");
        m_dashBoard->setFlagString11("Batt. Light");
        m_dashBoard->setFlagString12("Eng. Limiter");
        m_dashBoard->setFlagString13("Ignition");
        m_dashBoard->setFlagString14("NOS Stage 1");
        m_dashBoard->setFlagString15("NOS Stage 2");
        m_dashBoard->setFlagString16("NOS Stage 3");
        //m_dashBoard->setFlagString17("NOS Stage 4");
        //m_dashBoard->setFlagString18("NOS Stage 5");
        //m_dashBoard->setFlagString19("NOS Stage 6");

        QProcess *process = new QProcess(this);
        process->start("/home/pi/Haltech/HaltechV2");
        m_udpreceiver->startreceiver();
    }

    if (ecuSelect == 7)
    {
        m_udpreceiver->startreceiver();
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
    //UDP receiver
    if (ecu == 1)
    {
        m_udpreceiver->closeConnection();
    }

    //Adaptronic Select
    if (ecu == 2)
    {
        m_adaptronicselect->closeConnection();

    }
    //Adaptronic ModularCAN protocol
    if (ecu == 3)
    {

        m_udpreceiver->closeConnection();

    }
    if (ecu == 4)
    {

        // QProcess *process = new QProcess(this);
        // process->start("sudo pkill Consult");
        // qDebug()<<"Kill";
        m_udpreceiver->closeConnection();
    }
    if (ecu == 5)
    {

        QProcess *process = new QProcess(this);
        process->start("sudo pkill HaltechV1");
        qDebug()<<"Kill";

    }
    if (ecu == 6)
    {

        QProcess *process = new QProcess(this);
        process->start("sudo pkill HaltechV2");
        qDebug()<<"Kill";

    }

}

void Connect::update()
{

    QProcess *p = new QProcess( this );

    if (p)
    {
        p->setEnvironment( QProcess::systemEnvironment() );
        p->setProcessChannelMode( QProcess::MergedChannels );
        p->start("/home/pi/src/updatePowerTune.sh", QStringList() << "echo" << "hye" );
        p->waitForStarted();

        connect( p, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()) );
        //connect( p, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
    }
}

void Connect::shutdown()
{
    m_dashBoard->setSerialStat("Shutting Down");
    QProcess *process = new QProcess(this);
    process->start("sudo shutdown -h now");
    process->waitForFinished(100); // 10 minutes time before timeout
}
void Connect::reboot()
{
    m_dashBoard->setSerialStat("Rebooting");
    QProcess *process = new QProcess(this);
    process->start("sudo reboot");
    process->waitForFinished(100); // 10 minutes time before timeout
}
void Connect::candump()
{
    QProcess *p = new QProcess( this );

    if (p)
    {
        p->setEnvironment( QProcess::systemEnvironment() );
        p->setProcessChannelMode( QProcess::MergedChannels );
        p->start( "/home/pi/daemons/OBD /dev/ttyUSB0", QStringList() << "echo" << "hye" );
        p->waitForStarted();

        connect( p, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()) );
        //connect( p, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
    }
}
void Connect::minicom()
{
    QProcess *p = new QProcess( this );

    if (p)
    {
        p->setEnvironment( QProcess::systemEnvironment() );
        p->setProcessChannelMode( QProcess::MergedChannels );
        p->start( "minicom", QStringList() << "echo" << "hye" );
        p->waitForStarted();

        connect( p, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()) );
        //connect( p, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
    }
}


// this gets called whenever the process has something to say...
void Connect::processOutput()
{
   // qDebug() << "processing";
    QProcess *p = dynamic_cast<QProcess *>( sender() );

  //  if (p)
        QString output = p->readAllStandardOutput();
 //       qDebug() << "redirecting" << output;
        m_dashBoard->setSerialStat(output);
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

void Connect::RequestLicence()
{
    QProcess *process = new QProcess(this);
    process->start("/home/pi/licencerequest");
    process->waitForFinished(100); // 10 minutes time before timeout

    QString path = "/home/pi/Licrequest.lic";
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            m_dashBoard->setSerialStat(line);
        }
        inputFile.close();
    }
}
