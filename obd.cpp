/*
* file obd.cpp
* Copyright (C) 2018 Markus Ippy
*
* Communications class for OBD2 Live readouts
*
* No warranty is made or implied. You use this program at your own risk.
*/
#include "obd.h"
#include "serialport.h"
#include "dashboard.h"
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>
#include <QTextStream>
#include <QByteArrayMatcher>
#include <QProcess>



int reqquestInd = 0; //ID for requested data type Power FC
bool ok;
quint16 RPM;
quint8 SPEED;
//

OBD::OBD(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)

{

}
OBD::OBD(DashBoard *dashboard, QObject *parent)
    : QObject(parent),
    m_dashboard(dashboard),
    m_serial(Q_NULLPTR),
    m_bytesWritten(0)
{
}


void OBD::initSerialPort()
{


    if (m_serial)
        delete m_serial;
    m_serial = new SerialPort(this);
    connect(this->m_serial,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    connect(m_serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &OBD::handleError);
    connect(m_serial, &QSerialPort::bytesWritten, this, &OBD::handleBytesWritten);
    connect(&m_timer, &QTimer::timeout, this, &OBD::handleTimeout);
    m_readData.clear();
    qDebug() <<("Initialized");


}

//function for flushing all serial buffers
void OBD::clear() const
{
    m_serial->clear();
}


//function to open serial port
void OBD::openConnection(const QString &portName)
{



    qDebug() <<("Opening Port")<<portName;

    initSerialPort();

    m_serial->setPortName(portName);
    m_serial->setBaudRate(QSerialPort::Baud38400); //initial standard baud for ELM327 is either 9600 or 384000
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);;

    if(m_serial->open(QIODevice::ReadWrite) == false)
    {
       m_dashboard->setSerialStat(m_serial->errorString());
       OBD::closeConnection();

    }
    else
    {
        reqquestInd = 0;
        OBD::sendRequest(reqquestInd);
    }


}

void OBD::closeConnection()

{
        disconnect(this->m_serial,SIGNAL(readyRead()),this,SLOT(readyToRead()));
        disconnect(m_serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                this, &OBD::handleError);
        disconnect(m_serial, &QSerialPort::bytesWritten, this, &OBD::handleBytesWritten);
        disconnect(&m_timer, &QTimer::timeout, this, &OBD::handleTimeout);
        m_serial->close();
}

void OBD::handleTimeout()
{
    m_timer.stop();
    qDebug() <<("timeout message") << m_buffer;
    m_readData.clear();
    m_buffer.clear();
    OBD::sendRequest(reqquestInd);
}

void OBD::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        QString fileName = "Errors.txt";
        QFile mFile(fileName);
        if(!mFile.open(QFile::Append | QFile::Text)){
        }
        QTextStream out(&mFile);
        out << "Serial Error " << (m_serial->errorString()) <<endl;
        mFile.close();
        m_dashboard->setSerialStat(m_serial->errorString());

    }
}


void OBD::readyToRead()
{

    m_readData = m_serial->readAll();
    OBD::messageconstructor(m_readData);

}

void OBD::messageconstructor(const QByteArray &buffer)
{
    m_timer.start(5000);
    m_buffer.append(buffer);
    QByteArray msgEnd = (QByteArray::fromStdString(">"));
    if (m_buffer.contains(msgEnd))
    {
        m_timer.stop();
        m_message = m_buffer;
        int end = m_message.indexOf(msgEnd);
        m_message.remove(end+1,m_message.length()-end);
        qDebug() <<("sending reply for decoding")<<m_message;
        m_buffer.remove(0,end+1);
        if (m_message.contains(QByteArray::fromStdString("7E8")))
        {
            m_message.replace("7E8","");
            m_message.replace(" ",""); //remove whitespace
            m_message.replace("\r\r>",""); //remove end string
            //int value = QString("AA110011").toInt(NULL, 16);

        }
        else
        {
        m_message.replace("\r\r>",""); //remove end string
        m_dashboard->setSerialStat(m_message);//update serialstatus
        }

        readData(m_message);

        //This is just a temporary solution....
        if(reqquestInd <= 8){reqquestInd++;}
        else reqquestInd =8;

        OBD::sendRequest(reqquestInd);
    }

}




void OBD::readData(QByteArray serialdata)
{


    int requesttype = (serialdata.mid(4,2)).toInt(&ok,16);
    qDebug() <<("requesttype ")<< requesttype;
    if( serialdata.length() )
    {

            switch (requesttype) {
            case PIDS::SupportedPids0to20:
                //Still need to ad calculations
                break;
            case PIDS::Monitorstatus:
                //Still need to ad calculations
                break;

            case PIDS::FreezeDTC:
                //Still need to ad calculations
                break;

            case PIDS::FuelsystemStatus:
                //Still need to ad calculations
                break;

            case PIDS::CalcEngLoad:
                //LOAD = (serialdata.mid(6,2)).toInt(&ok,16);
                //m_dashboard->setEngLoad(LOAD/255);
                break;

            case PIDS::EngCoolantTemp:
                //COOLANT = (serialdata.mid(6,2)).toInt(&ok,16);
                //m_dashboard->setEngLoad(COOLANT-40);
                break;

            case PIDS::ShortTermFueltrimB1:
                //Still need to ad calculations
                break;

            case PIDS::LongTermFueltrimB1:
                //Still need to ad calculations
                break;

            case PIDS::ShortTermFueltrimB2:
                //Still need to ad calculations
                break;

            case PIDS::LongTermFueltrimB2:
                //Still need to ad calculations
                break;

            case PIDS::FuelPressure:
                //FUELPR = (serialdata.mid(6,2)).toInt(&ok,16);
                //m_dashboard->setEngLoad(FUELPR*3); // value in KPA
                break;

            case PIDS::IntakeManifoldPress:
                //MAP = (serialdata.mid(6,2)).toInt(&ok,16);
                //m_dashboard->setMAP(MAP); // value in KPA
                break;

            case PIDS::EngineRPM:
                RPM = (serialdata.mid(6,4)).toInt(&ok,16);
                m_dashboard->setrpm(RPM/4);

                break;

            case PIDS::VehicleSpeed:
                SPEED = (serialdata.mid(6,2)).toInt(&ok,16);
                m_dashboard->setSpeed(SPEED);
                break;

            case PIDS::TimingAdvance:
                //IGNT = (serialdata.mid(6,2)).toInt(&ok,16);
                //m_dashboard->setIgn((IGNT/2)-64);
                break;

            case PIDS::IntakeAirTemp:
                //IAT = (serialdata.mid(6,2)).toInt(&ok,16);
                //m_dashboard->setIntaketemp(IAT-40);
                break;

            case PIDS::MAFrate:
                //Still need to ad calculations
                break;
            case PIDS::ThrottlePosition:
                //Still need to ad calculations
                break;
            case PIDS::ComsecAirStatus:
                //Still need to ad calculations
                break;

            case PIDS::OxygenSenspresent:
                //Still need to ad calculations
                break;

            case PIDS::O2sensor1:
                //Still need to ad calculations
                break;


            default:
                break;
            }

        serialdata.clear();

    }


}
void OBD::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
    if (m_bytesWritten == m_writeData.size()) {
        m_bytesWritten = 0;
        //qDebug() <<("Data successfully sent to port") << (m_serial->portName());

    }
}
// Serial requests are send via Serial
void OBD::writeRequest(QByteArray p_request)
{
    qDebug() << "Sending Request" << p_request;
    m_writeData = p_request;
    qint64 bytesWritten = m_serial->write(p_request);
    m_dashboard->setSerialStat(QString("Sending Request " + p_request.toHex()));

    //Action to be implemented
    if (bytesWritten == -1) {
        m_dashboard->setSerialStat(m_serial->errorString());
        //qDebug() << "Write request to port failed" << (m_serial->errorString());
    } else if (bytesWritten != m_writeData.size()) {
       m_dashboard->setSerialStat(m_serial->errorString());
        //qDebug() << "could not write complete request to port" << (m_serial->errorString());
    }

}



void OBD::sendRequest(int reqquestInd)
{
    switch (reqquestInd){

    // Setup the OBD ELM Device
       case 0:
           // Reset Adapter ELM OBD Adapter
           OBD::writeRequest(QByteArray::fromStdString("ATZ\r"));
           qDebug() <<("ELM Device reset ");
           break;
       case 1:
           // Reset Adapter ELM OBD Adapter
           OBD::writeRequest(QByteArray::fromStdString("ATI\r"));
           qDebug() <<("Request name of ELM Device");
           break;

       case 2:
           // disable extended response
           OBD::writeRequest(QByteArray::fromStdString("ATE0\r"));
           qDebug() <<("Disable  extended response");
           break;

       case 3:
           // Disable extended response
           OBD::writeRequest(QByteArray::fromStdString("ATL0\r"));
           qDebug() <<("Disable  extended response");
           break;

       case 4:
           // Enable header for response
           OBD::writeRequest(QByteArray::fromStdString("ATH1\r"));
           qDebug() <<("Enable Response Header");
           break;

       case 5:
           // Autodetect protocol
           OBD::writeRequest(QByteArray::fromStdString("ATSP00\r"));
           qDebug() <<("Autodetect Protocol");
           break;

       case 6:
           // Test communication
           OBD::writeRequest(QByteArray::fromStdString("0001\r"));
           qDebug() <<("Check if ELM communication is OK ");
           break;
       case 7:
           // Request supported PIDS
           OBD::writeRequest(QByteArray::fromStdString("0100\r"));
           qDebug() <<("Request supported pids ");
           break;
       case 8:
           // Test RPM
           OBD::writeRequest(QByteArray::fromStdString("010C\r"));
           qDebug() <<("Request RPM ");
           break;
       case 9:
        // Test Speed
        OBD::writeRequest(QByteArray::fromStdString("010D\r"));
        qDebug() <<("Request Speed ");
        break;
// PID requests

        break;
    }
}
