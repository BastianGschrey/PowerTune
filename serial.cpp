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
  \file serial.cpp
  \brief Raspexi Viewer Power FC related functions
  \author Bastian Gschrey
*/

#include "serial.h"
#include "decoder.h"
#include "dashboard.h"
#include "serialport.h"
#include "appsettings.h"

#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QModbusRtuSerialMaster>

int requestIndex = 0; //ID for requested data type
int ecu; //0=apex, 1=adaptronic;
int Bytesexpected = 500;
//reply = new QModbusReply;


Serial::Serial(QObject *parent) :
    QObject(parent),
    m_serialport(Q_NULLPTR),
    m_decoder(Q_NULLPTR),
    m_dashBoard(Q_NULLPTR),
    lastRequest(nullptr),
    modbusDevice(nullptr)

{


    getPorts();
    m_dashBoard = new DashBoard(this);
    m_decoder = new Decoder(m_dashBoard, this);
    m_appSettings = new AppSettings(this);
    connect(m_decoder,SIGNAL(sig_adaptronicReadFinished()),this,SLOT(AdaptronicStartStream()));
    QQmlApplicationEngine *engine = dynamic_cast<QQmlApplicationEngine*>( parent );
    if (engine == Q_NULLPTR)
        return;
    engine->rootContext()->setContextProperty("Dashboard", m_dashBoard);
    engine->rootContext()->setContextProperty("AppSettings", m_appSettings);
}

void Serial::initSerialPort()
{
    if (m_serialport)
        delete m_serialport;
    m_serialport = new SerialPort(this);
    connect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));

}
void Serial::getEcus()
{
    QStringList EcuList;
    EcuList.append("PowerFC");
    EcuList.append("Adaptronic");
    //setEcus(EcuList);
}

/*void Serial::setEcus(QStringList ECUList)
{

}*/

void Serial::getPorts()
{
    QStringList PortList;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       PortList.append(info.portName());
    }
    setPortsNames(PortList);
    // Check available ports evry 1000 ms
    QTimer::singleShot(1000, this, SLOT(getPorts()));
}
//function for flushing all serial buffers
void Serial::clear() const
{
    m_serialport->clear();
}
//function to open serial port
void Serial::openConnection(const QString &portName, const int &baudRate, const int &parity,
                            const int &dataBits, const int &stopBits, const int &flowControl, const int &ecuSelect)
{

    ecu = ecuSelect;

    //Apexi
    if (ecuSelect == 0)
    {

     initSerialPort();

     m_serialport->setPortName(portName);
     //m_serialport->setBaudRate(baudRate);
     m_serialport->setBaudRate(QSerialPort::Baud57600);
     //m_serialport->setParity(parity);
     m_serialport->setParity(QSerialPort::NoParity);
     m_serialport->setDataBits(static_cast<QSerialPort::DataBits>(dataBits + 5));
     m_serialport->setStopBits(static_cast<QSerialPort::StopBits>(stopBits + 1));
     //m_serialport->setFlowControl(static_cast<QSerialPort::FlowControl>(flowControl));
     m_serialport->setFlowControl(QSerialPort::NoFlowControl);

     qDebug() << "Try to open SerialPort:";
     if(m_serialport->open(QIODevice::ReadWrite) == false)
     {
         qDebug() << "Open Serial port failed: " << m_serialport->errorString();
     }

     requestIndex = 0;
     qDebug() << "Initial request to PowerFc"<< requestIndex;
     Serial::sendRequest(requestIndex);

     }


    //Adaptronic    
    if (ecuSelect == 1)
    {
    modbusDevice = new QModbusRtuSerialMaster(this);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,portName);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,57600);
    modbusDevice->setTimeout(200);
    modbusDevice->setNumberOfRetries(10);
    modbusDevice->connectDevice();
    //modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 4097, 6),1);
    Serial::AdaptronicStartStream();
    }
}

void Serial::closeConnection()
{
    if(ecu == 0){
    m_serialport->close();
    qDebug() << "Connection closed.";
    }
    if(ecu == 1){
        modbusDevice->disconnectDevice();
    }
}
// Error handling still to be tested
void Serial::readyToRead()
{
    if(ecu == 0)
    {
    QTime startTime = QTime::currentTime();
    int timeOut = 100; // timeout in milisec.
    int Bytes = 1000;
    QByteArray recvData;// = m_serialport->read(Bytesexpected);  // reading first two bytes of received message to determine lenght of ecpected message
    //int msgLen = Bytesexpected; //Total message Lenght excluding the first byte

    while (Bytesexpected < Bytes)
        {
              if ( startTime.msecsTo(QTime::currentTime()) > timeOut ) break;

              //      qDebug() << "Bytes expected"<<Bytesexpected;
              //      qDebug() << "Bytes Available to read"<<m_serialport->bytesAvailable();
              Bytes = m_serialport->bytesAvailable();
         }

    if  (Bytesexpected == m_serialport->bytesAvailable())
        {
         recvData += m_serialport->read(Bytesexpected);
        }

    if(Bytesexpected == recvData.size())                  //if the received data lenght equals the message lenght from lenght byte + identifier byte (correct message lenght received )
            {
            qDebug() << "Received data OK"<<Bytesexpected;
            qDebug() << "time taken (ms) "<<(QTime::currentTime());
            if(requestIndex <= 61){requestIndex++;}
            else{requestIndex = 58;}
            readData(recvData);
            recvData.clear();
            m_serialport->flush();
            }
     else
    {
    qDebug() << "Received data  NOK message"<<requestIndex;
    }
   }

    if(ecu == 1)
    {

    auto reply = qobject_cast<QModbusReply *>(sender());
    if(!reply)
        return;
    if(reply->error() == QModbusDevice::NoError){
        const QModbusDataUnit unit = reply->result();
        m_decoder->decodeAdaptronic(unit);
    }



    }
}

void Serial::readData(QByteArray serialdata)
{
    if( serialdata.length() )
    {
        //Power FC Decode
        quint8 requesttype = serialdata[0];
        qDebug() << "Received message :"<< serialdata.toHex();
        //quint8 requesttypeAdaptronic = serialdata[1];

        if(serialdata[1] + 1 == serialdata.length())

           {

            if(serialdata.length() == 33 && requesttype == 0xF0){m_decoder->decodeAdv(serialdata);}
            if(serialdata.length() == 21 && requesttype == 0xDE){m_decoder->decodeSensor(serialdata);}
            if(serialdata.length() == 7 && requesttype == 0x00){m_decoder->decodeAux(serialdata);}
            if(serialdata.length() == 5 && requesttype == 0xDB){m_decoder->decodeMap(serialdata);}
            if(serialdata.length() == 23 && requesttype == 0xDA){m_decoder->decodeBasic(serialdata);}
            if(serialdata.length() == 17 && requesttype == 0xB8){m_decoder->decodeRevIdle(serialdata);}
            if(serialdata.length() == 12 && requesttype == 0x7D){m_decoder->decodeTurboTrans(serialdata);}
            if(serialdata.length() == 103 && requesttype == 0x76){m_decoder->decodeLeadIgn(serialdata, 0);}
            if(serialdata.length() == 103 && requesttype == 0x77){m_decoder->decodeLeadIgn(serialdata, 5);}
            if(serialdata.length() == 103 && requesttype == 0x78){m_decoder->decodeLeadIgn(serialdata, 10);}
            if(serialdata.length() == 103 && requesttype == 0x79){m_decoder->decodeLeadIgn(serialdata, 15);}
            if(serialdata.length() == 103 && requesttype == 0x81){m_decoder->decodeTrailIgn(serialdata, 0);}
            if(serialdata.length() == 103 && requesttype == 0x82){m_decoder->decodeTrailIgn(serialdata, 5);}
            if(serialdata.length() == 103 && requesttype == 0x83){m_decoder->decodeTrailIgn(serialdata, 10);}
            if(serialdata.length() == 103 && requesttype == 0x84){m_decoder->decodeTrailIgn(serialdata, 15);}
            if(serialdata.length() == 103 && requesttype == 0x86){m_decoder->decodeInjcorr(serialdata, 0);}
            if(serialdata.length() == 103 && requesttype == 0x87){m_decoder->decodeInjcorr(serialdata, 5);}
            if(serialdata.length() == 103 && requesttype == 0x88){m_decoder->decodeInjcorr(serialdata, 10);}
            if(serialdata.length() == 103 && requesttype == 0x89){m_decoder->decodeInjcorr(serialdata, 15);}

            if(serialdata.length() == 103 && requesttype == 0xB0){m_decoder->decodeFuelBase(serialdata, 0);}
            if(serialdata.length() == 103 && requesttype == 0xB1){m_decoder->decodeFuelBase(serialdata, 1);}
            if(serialdata.length() == 103 && requesttype == 0xB2){m_decoder->decodeFuelBase(serialdata, 2);}
            if(serialdata.length() == 103 && requesttype == 0xB3){m_decoder->decodeFuelBase(serialdata, 3);}
            if(serialdata.length() == 103 && requesttype == 0xB4){m_decoder->decodeFuelBase(serialdata, 4);}
            if(serialdata.length() == 103 && requesttype == 0xB5){m_decoder->decodeFuelBase(serialdata, 5);}
            if(serialdata.length() == 103 && requesttype == 0xB6){m_decoder->decodeFuelBase(serialdata, 6);}
            if(serialdata.length() == 103 && requesttype == 0xB7){m_decoder->decodeFuelBase(serialdata, 7);}

            if(serialdata.length() == 8 && requesttype == 0xF5){m_decoder->decodeVersion(serialdata);}
            if(serialdata.length() == 11 && requesttype == 0xF3){m_decoder->decodeInit(serialdata);}
            if(serialdata.length() == 14 && requesttype == 0xAB){m_decoder->decodeBoostCont(serialdata);}
            if(serialdata.length() == 9 && requesttype == 0x7B){m_decoder->decodeInjOverlap(serialdata);}
            if(serialdata.length() == 15 && requesttype == 0x92){m_decoder->decodeInjPriLagvsBattV(serialdata);}
            if(serialdata.length() == 15 && requesttype == 0x9F){m_decoder->decodeInjScLagvsBattV(serialdata);}
            if(serialdata.length() == 27 && requesttype == 0x8D){m_decoder->decodeFuelInjectors(serialdata);}




      }

        serialdata.clear();

        Serial::sendRequest(requestIndex);


    }


}

// Serial requests are send via Serial

void Serial::getAdvData()
{
    m_serialport->write(QByteArray::fromHex("F0020D"));
    m_serialport->flush();
    Bytesexpected = 33;
}
void Serial::getSensorData()
{
    m_serialport->write(QByteArray::fromHex("DE021F"));
    m_serialport->flush();
    Bytesexpected = 21;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
//    emit readyRead();
}
void Serial::getAux()
{
    m_serialport->write(QByteArray::fromHex("0002FD"));
    m_serialport->flush();
    Bytesexpected = 7;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)

}
void Serial::getMapIndices()
{
    m_serialport->write(QByteArray::fromHex("DB0222"));
    m_serialport->flush();
    Bytesexpected = 5;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
//    emit readyRead();

}
void Serial::getBasic()
{
    m_serialport->write(QByteArray::fromHex("DA0223"));
    m_serialport->flush();
    Bytesexpected = 23;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
//    emit readyRead();
}
//Map Readout
void Serial::getRevIdle()
{
    m_serialport->write(QByteArray::fromHex("B80245"));
    m_serialport->flush();
    Bytesexpected = 17;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getSensorStrings()
{
    m_serialport->write(QByteArray::fromHex("DD0220"));
    m_serialport->flush();
    Bytesexpected = 83;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getPimStrInjA()
{
    m_serialport->write(QByteArray::fromHex("CB0232"));
    m_serialport->flush();
    Bytesexpected = 110;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getVersion()
{
    m_serialport->write(QByteArray::fromHex("F50208"));
    m_serialport->flush();
    Bytesexpected = 8;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getMapRef()
{
    m_serialport->write(QByteArray::fromHex("8A0273"));
    m_serialport->flush();
    Bytesexpected = 83;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getLeadign1()
{
    m_serialport->write(QByteArray::fromHex("760287"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getLeadign2()
{
    m_serialport->write(QByteArray::fromHex("770286"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getLeadign3()
{
    m_serialport->write(QByteArray::fromHex("780285"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getLeadign4()
{
    m_serialport->write(QByteArray::fromHex("790284"));
    m_serialport->flush();
     Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getTrailIgn1()
{
    m_serialport->write(QByteArray::fromHex("81027C"));
    m_serialport->flush();
     Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getTrailIgn2()
{
    m_serialport->write(QByteArray::fromHex("82027B"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getTrailIgn3()
{
    m_serialport->write(QByteArray::fromHex("83027A"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getTrailIgn4()
{
    m_serialport->write(QByteArray::fromHex("840279"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInitPlatform()
{
    m_serialport->write(QByteArray::fromHex("F3020A"));
    m_serialport->flush();
    Bytesexpected = 11;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec) }
}
void Serial::getInjOverlap()
{
    m_serialport->write(QByteArray::fromHex("7B0282"));
    m_serialport->flush();
    Bytesexpected = 9;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInjvsFuelT()
{
    m_serialport->write(QByteArray::fromHex("7C0281"));
    m_serialport->flush();
    Bytesexpected = 12;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getTurboTrans()
{
    m_serialport->write(QByteArray::fromHex("7D0280"));
    m_serialport->flush();
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getOilervsWaterT()
{
    m_serialport->write(QByteArray::fromHex("7E027F"));
    m_serialport->flush();
    Bytesexpected = 9;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getFanvsWater()
{
    m_serialport->write(QByteArray::fromHex("7F027E"));
    m_serialport->flush();
    Bytesexpected = 6;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInjcorr1()
{
    m_serialport->write(QByteArray::fromHex("860277"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInjcorr2()
{
    m_serialport->write(QByteArray::fromHex("870276"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInjcorr3()
{
    m_serialport->write(QByteArray::fromHex("880275"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInjcorr4()
{
    m_serialport->write(QByteArray::fromHex("890274"));
    m_serialport->flush();
    Bytesexpected = 103;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getFuelInj()
{
    m_serialport->write(QByteArray::fromHex("8D0270"));
    m_serialport->flush();
    Bytesexpected = 27;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getCranking()
{
    m_serialport->write(QByteArray::fromHex("8E026F"));
    m_serialport->flush();
    Bytesexpected = 15;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getWaterTcorr()
{
    m_serialport->write(QByteArray::fromHex("8F026E"));
    m_serialport->flush();
    Bytesexpected = 17;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInjvsWaterBoost()
{
    m_serialport->write(QByteArray::fromHex("90026D"));
    m_serialport->flush();
    Bytesexpected = 9;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInjvsAirTBoost()
{
    m_serialport->write(QByteArray::fromHex("91026C"));
    m_serialport->flush();
    Bytesexpected = 11;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInjPrimaryLag()
{
    m_serialport->write(QByteArray::fromHex("92026B"));
    m_serialport->flush();
    Bytesexpected = 15;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getAccInj()
{
    m_serialport->write(QByteArray::fromHex("93026A"));
    m_serialport->flush();
    Bytesexpected = 28;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getInjvsAccel()
{
    m_serialport->write(QByteArray::fromHex("940269"));
    m_serialport->flush();
    Bytesexpected = 12;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getIgnvsAircold()
{
    m_serialport->write(QByteArray::fromHex("960267"));
    m_serialport->flush();
    Bytesexpected = 7;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getIgnvsWater()
{
    m_serialport->write(QByteArray::fromHex("980265"));
    m_serialport->flush();
    Bytesexpected = 7;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getIgnvsAirwarm()
{
    m_serialport->write(QByteArray::fromHex("9A0263"));
    m_serialport->flush();
    Bytesexpected = 9;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getLIgnvsRPM()
{
    m_serialport->write(QByteArray::fromHex("9B0262"));
    m_serialport->flush();
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getIgnvsBatt()
{
    m_serialport->write(QByteArray::fromHex("9C0261"));
    m_serialport->flush();
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getBoostvsIgn()
{
    m_serialport->write(QByteArray::fromHex("9D0260"));
    m_serialport->flush();
    Bytesexpected = 7;
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getTrailIgnvsRPM()
{
    m_serialport->write(QByteArray::fromHex("9E025F"));
    m_serialport->flush();
    Bytesexpected = 9;
}
void Serial::getInjSecLagvsBattV()
{
    m_serialport->write(QByteArray::fromHex("9F025E"));
    m_serialport->flush();
    Bytesexpected = 15;
}
void Serial::getInjWarn()
{
    m_serialport->write(QByteArray::fromHex("A80255"));
    m_serialport->flush();
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getKnockWarn()
{
    m_serialport->write(QByteArray::fromHex("A90254"));
   m_serialport->flush();
   Bytesexpected = 7;
}
void Serial::getO2Feedback()
{
    m_serialport->write(QByteArray::fromHex("AA0253"));
    m_serialport->flush();
    Bytesexpected = 6;
}
void Serial::getBoostcontrol()
{
    m_serialport->write(QByteArray::fromHex("AB0252"));
    m_serialport->flush();
    Bytesexpected = 14;
}
void Serial::getSettingProtections()
{
    m_serialport->write(QByteArray::fromHex("AC0251"));
    m_serialport->flush();
    Bytesexpected = 13;
}
void Serial::getTunerString()
{
    m_serialport->write(QByteArray::fromHex("AD0250"));
    m_serialport->flush();
    Bytesexpected = 11;
}
void Serial::getInjvsAirTemp()
{
    m_serialport->write(QByteArray::fromHex("B90244"));
    m_serialport->flush();
    Bytesexpected = 15;
}
void Serial::getInjvsTPS()
{
    m_serialport->write(QByteArray::fromHex("BA0243"));
    m_serialport->flush();
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getIgnvsTPS()
{
    m_serialport->write(QByteArray::fromHex("BB0242"));
    m_serialport->flush();
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}
void Serial::getPIMScaleOffset()
{
   m_serialport->write(QByteArray::fromHex("BC0241"));
    m_serialport->flush();
    Bytesexpected = 23;
}
void Serial::getWarConStrFlags()
{
    m_serialport->write(QByteArray::fromHex("D60227"));
    m_serialport->flush();
    Bytesexpected = 88;
}
void Serial::getNotdocumented()
{
    m_serialport->write(QByteArray::fromHex("F40209"));
    m_serialport->flush();
    Bytesexpected = 4;
}
void Serial::getFuelBase0()
{
    m_serialport->write(QByteArray::fromHex("B0024D"));
    m_serialport->flush();
    Bytesexpected = 103;
}
void Serial::getFuelBase1()
{
    m_serialport->write(QByteArray::fromHex("B1024C"));
    m_serialport->flush();
    Bytesexpected = 103;
}
void Serial::getFuelBase2()
{
    m_serialport->write(QByteArray::fromHex("B2024B"));
    m_serialport->flush();
    Bytesexpected = 103;
}
void Serial::getFuelBase3()
{
    m_serialport->write(QByteArray::fromHex("B3024A"));
    m_serialport->flush();
    Bytesexpected = 103;
}
void Serial::getFuelBase4()
{
    m_serialport->write(QByteArray::fromHex("B40249"));
    m_serialport->flush();
    Bytesexpected = 103;
}
void Serial::getFuelBase5()
{
    m_serialport->write(QByteArray::fromHex("B50248"));
    m_serialport->flush();
    Bytesexpected = 103;
}
void Serial::getFuelBase6()
{
    m_serialport->write(QByteArray::fromHex("B60247"));
    m_serialport->flush();
    Bytesexpected = 103;
}
void Serial::getFuelBase7()
{
    m_serialport->write(QByteArray::fromHex("B70246"));
    m_serialport->flush();
    Bytesexpected = 103;
}
//End of serial requests

// Adaptronic streaming comms


void Serial::sendRequest(int requestIndex)
{
    switch (requestIndex){

    case 0:
         Serial::getInitPlatform();
         break;
    case 1:
         Serial::getSensorStrings();
         break;
    case 2:
         Serial::getPimStrInjA();
         break;
    case 3:
         Serial::getVersion();
         break;
    case 4:
         Serial::getMapRef();
         break;
    case 5:
         Serial::getRevIdle();
         break;
    case 6:
         Serial::getLeadign1();
         break;
    case 7:
         Serial::getLeadign2();
         break;
    case 8:
         Serial::getLeadign3();
         break;
    case 9:
         Serial::getLeadign4();
         break;
    case 10:
         Serial::getTrailIgn1();
         break;
    case 11:
         Serial::getTrailIgn2();
         break;
    case 12:
         Serial::getTrailIgn3();
         break;
    case 13:
         Serial::getTrailIgn4();
         break;
    case 14:
         Serial::getInitPlatform();
         break;
    case 15:
         Serial::getInjOverlap();
         break;
    case 16:
         Serial::getInjvsFuelT();
         break;
    case 17:
         Serial::getTurboTrans();
         break;
    case 18:
         Serial::getOilervsWaterT();
         break;
    case 19:
         Serial::getFanvsWater();
         break;
    case 20:
         Serial::getInjcorr1();
         break;
    case 21:
         Serial::getInjcorr2();
         break;
    case 22:
         Serial::getInjcorr3();
         break;
    case 23:
         Serial::getInjcorr4();
         requestIndex++;
         break;
    case 24:
         Serial::getFuelInj();
         break;
    case 25:
         Serial::getCranking();
         break;
   case 26:
         Serial::getWaterTcorr();
         break;
    case 27:
         Serial::getInjvsWaterBoost();
         break;
    case 28:
         Serial::getInjvsAirTBoost();
         break;
    case 29:
         Serial::getInjPrimaryLag();
         break;
    case 30:
         Serial::getAccInj();
         break;
    case 31:
         Serial::getInjvsAccel();
         break;
    case 32:
         Serial::getIgnvsAircold();
         break;
    case 33:
         Serial::getIgnvsWater();
         break;
    case 34:
         Serial::getIgnvsAirwarm();
         break;
    case 35:
         Serial::getLIgnvsRPM();
         break;
    case 36:
         Serial::getIgnvsBatt();
         break;
    case 37:
         Serial::getBoostvsIgn();
         break;
    case 38:
         Serial::getTrailIgnvsRPM();
         break;
    case 39:
         Serial::getInjSecLagvsBattV();
         break;
    case 40:
         Serial::getKnockWarn();
         break;
    case 41:
         Serial::getNotdocumented();
        break;
    case 42:
         Serial::getO2Feedback();
         break;
    case 43:
         Serial::getBoostcontrol();
         break;
    case 44:
         Serial::getSettingProtections();
         break;
    case 45:
         Serial::getTunerString();
         break;
    case 46:
         Serial::getFuelBase0();
         break;
    case 47:
         Serial::getFuelBase1();
         break;
    case 48:
         Serial::getFuelBase2();
         break;
    case 49:
         Serial::getFuelBase3();
         break;
    case 50:
         Serial::getFuelBase4();
         break;
    case 51:
         Serial::getFuelBase5();
         break;
    case 52:
         Serial::getFuelBase6();
         break;
    case 53:
         Serial::getFuelBase7();
         break;
   case 54:
         Serial::getInjvsAirTemp();
         break;
    case 55:
         Serial::getInjvsTPS();
         break;
    case 56:
         Serial::getPIMScaleOffset();
         break;
    case 57:
         Serial::getWarConStrFlags();
         break;
// Live Data
    case 58:
        Serial::getAdvData();
        break;
    case 59:
        Serial::getAux();
        break;
    case 60:
        Serial::getMapIndices();
        break;
    case 61:
        Serial::getSensorData();
        break;
    case 62:
        Serial::getBasic();
        break;
    }
}



void Serial::AdaptronicStartStream()
{
auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 4096, 21),1); // read first twenty realtime values
if (!reply->isFinished())
    connect(reply, &QModbusReply::finished, this,&Serial::readyToRead);
else
    delete reply;


}
void Serial::AdaptronicStopStream()
{

}
