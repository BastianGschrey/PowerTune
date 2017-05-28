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

int requestIndex = 0; //ID for requested data type Power FC
int ecu; //0=apex, 1=adaptronic;
int interface; // 0=fcHako, 1=fc-datalogIt
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
void Serial::openConnection(const QString &portName, const int &ecuSelect, const int &interfaceSelect)
{

    ecu = ecuSelect;
    interface = interfaceSelect;


    //Apexi
    if (ecuSelect == 0)
    {

     initSerialPort();

     m_serialport->setPortName(portName);
     m_serialport->setBaudRate(QSerialPort::Baud57600);
     m_serialport->setParity(QSerialPort::NoParity);
     m_serialport->setDataBits(QSerialPort::Data8);
     m_serialport->setStopBits(QSerialPort::OneStop);
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
        int timeOut = 5000; // timeout in milisec.
        QByteArray recvData;
        int Bytesexpected = 100;

        while (Bytesexpected > recvData.size()) //check the sc
            {
                  if ( startTime.msecsTo(QTime::currentTime()) > timeOut ) break;
                  //      qDebug() << "Bytes expected"<<Bytesexpected;
                  //      qDebug() << "Bytes Available to read"<<m_serialport->bytesAvailable();
                  recvData += m_serialport->readAll();
                  Bytesexpected = recvData[1]+1;
             }

/* For Later use
        // Process to calculate checksum
            int8_t checksum = 0xFFFFFFFFFFFFFFFF;                       //calculated checksum from serial message 0xFF - each byte in message (except the last byte)
            int8_t checksumposition = recvData[1];                  //determines in which position of the message the checksumbyte is located
            int8_t receivedchecksum = recvData[checksumposition];   //checksum from serial message
            //int8_t integrity = checksum - receivedchecksum;
            for (int i = 0; i <= recvData[1]-1; i++)
            {
            checksum = checksum - recvData[i];
            }
        if (receivedchecksum == checksum)
        {
        qDebug() << "Checksum OK"<<checksum;
        }
*/
// Pass OK Message on for proccessing
        if(Bytesexpected == recvData.size()) //if the received data lenght equals the message lenght from lenght byte + // Identifier byte (correct message lenght received )
                {
             //   qDebug() << "Received data OK"<<Bytesexpected;
             //   qDebug() << "time taken (ms) "<<(QTime::currentTime());
                if(requestIndex <= 61){requestIndex++;}
                else{requestIndex = 58;}
                readData(recvData);
                recvData.clear();
                m_serialport->flush();
                }
         else
        {
       // qDebug() << "Received data  NOK message"<<requestIndex;
       // qDebug() << "Incorrect message received:"<< recvData.toHex();
        Serial::sendRequest(requestIndex);
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
        //qDebug() << "Received message :"<< serialdata.toHex();
        //quint8 requesttypeAdaptronic = serialdata[1];

        if(serialdata[1] + 1 == serialdata.length())

           {
            if(serialdata.length() == 33 && requesttype == 0xF0){m_decoder->decodeAdv(serialdata);}
     //       if(serialdata.length() == 33 && Model == 2 && requesttype == 0xF0){m_decoder->decodeAdv2(serialdata);}
     //       if(serialdata.length() == 33 && Model == 3 && requesttype == 0xF0){m_decoder->decodeAdv3(serialdata);}
            if(serialdata.length() == 21 && requesttype == 0xDE){m_decoder->decodeSensor(serialdata);}
            if(serialdata.length() == 7 && requesttype == 0x00){m_decoder->decodeAux(serialdata);}
            if(serialdata.length() == 11 && requesttype == 0x00){m_decoder->decodeAux2(serialdata);}
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
        else
        {
        serialdata.clear();
        Serial::sendRequest(requestIndex);
        }
        serialdata.clear();
        Serial::sendRequest(requestIndex);

    }


}

// Serial requests are send via Serial
void Serial::writeRequestPFC(QByteArray p_request)
{
    m_serialport->write(p_request);
    m_serialport->flush();
}

//Power FC requests

void Serial::sendRequest(int requestIndex)
{
    switch (requestIndex){

    case 0:
        //not documented
        Serial::writeRequestPFC(QByteArray::fromHex("F40209"));
        break;
    case 1:
        //Init Platform for the first time ( usully returns a malformed packet)
        Serial::writeRequestPFC(QByteArray::fromHex("F3020A"));
        break;
    case 2:
        //Init Platform for a 2nd time
        Serial::writeRequestPFC(QByteArray::fromHex("F3020A"));
        break;
    case 3:
        //Serial::getVersion();
        Serial::writeRequestPFC(QByteArray::fromHex("F50208"));
        break;
    case 4:
        //Serial::getMapRef();
        Serial::writeRequestPFC(QByteArray::fromHex("8A0273"));
        break;
    case 5:
        //Serial::getRevIdle();
        Serial::writeRequestPFC(QByteArray::fromHex("B80245"));
        break;
    case 6:
        //Serial::getLeadign1();
        Serial::writeRequestPFC(QByteArray::fromHex("760287"));
        break;
    case 7:
        //Serial::getLeadign2();
        Serial::writeRequestPFC(QByteArray::fromHex("770286"));
        break;
    case 8:
        //Serial::getLeadign3();
        Serial::writeRequestPFC(QByteArray::fromHex("780285"));
        break;
    case 9:
        //Serial::getLeadign4();
        Serial::writeRequestPFC(QByteArray::fromHex("790284"));
        break;
    case 10:
        //Serial::getTrailIgn1();
        Serial::writeRequestPFC(QByteArray::fromHex("81027C"));
        break;
    case 11:
        //Serial::getTrailIgn2();
        Serial::writeRequestPFC(QByteArray::fromHex("82027B"));
        break;
    case 12:
        //Serial::getTrailIgn3();
        Serial::writeRequestPFC(QByteArray::fromHex("83027A"));
        break;
    case 13:
        //Serial::getTrailIgn4();
        Serial::writeRequestPFC(QByteArray::fromHex("840279"));
        break;
    case 14:
        //Serial::getPimStrInjA();
        Serial::writeRequestPFC(QByteArray::fromHex("CB0232"));
        break;
    case 15:
        //Serial::getInjOverlap();
        Serial::writeRequestPFC(QByteArray::fromHex("7B0282"));
        break;
    case 16:
        //Serial::getInjvsFuelT();
        Serial::writeRequestPFC(QByteArray::fromHex("7C0281"));
        break;
    case 17:
        //Serial::getTurboTrans();
        Serial::writeRequestPFC(QByteArray::fromHex("7D0280"));
        break;
    case 18:
        //Serial::getOilervsWaterT();
        Serial::writeRequestPFC(QByteArray::fromHex("7E027F")); //one of these is wrong
        break;
    case 19:
        //Serial::getFanvsWater();
        Serial::writeRequestPFC(QByteArray::fromHex("7F027E")); //one of these is wrong
        break;
    case 20:
        //Serial::getInjcorr1();
        Serial::writeRequestPFC(QByteArray::fromHex("860277"));
        break;
    case 21:
        //Serial::getInjcorr2();
        Serial::writeRequestPFC(QByteArray::fromHex("870276"));
        break;
    case 22:
        //Serial::getInjcorr3();
        Serial::writeRequestPFC(QByteArray::fromHex("880275"));
        break;
    case 23:
        //Serial::getInjcorr4();
        Serial::writeRequestPFC(QByteArray::fromHex("890274"));
        break;
    case 24:
        //Serial::getFuelInj();
        Serial::writeRequestPFC(QByteArray::fromHex("8D0270"));
        break;
    case 25:
        //Serial::getCranking();
        Serial::writeRequestPFC(QByteArray::fromHex("8E026F"));
        break;
    case 26:
        //Serial::getWaterTcorr();
        Serial::writeRequestPFC(QByteArray::fromHex("8F026E"));
        break;
    case 27:
        //Serial::getInjvsWaterBoost();
        Serial::writeRequestPFC(QByteArray::fromHex("90026D"));
        break;
    case 28:
        //Serial::getInjvsAirTBoost();
        Serial::writeRequestPFC(QByteArray::fromHex("91026C"));
        break;
    case 29:
        //Serial::getInjPrimaryLag();
        Serial::writeRequestPFC(QByteArray::fromHex("92026B"));
        break;
    case 30:
        //Serial::getAccInj();
        Serial::writeRequestPFC(QByteArray::fromHex("93026A"));
        break;
    case 31:
        //Serial::getInjvsAccel();
        Serial::writeRequestPFC(QByteArray::fromHex("940269"));
        break;
    case 32:
        //Serial::getIgnvsAircold();
        Serial::writeRequestPFC(QByteArray::fromHex("960267"));
        break;
    case 33:
        //Serial::getIgnvsWater();
        Serial::writeRequestPFC(QByteArray::fromHex("980265"));
        break;
    case 34:
        //Serial::getIgnvsAirwarm();
        Serial::writeRequestPFC(QByteArray::fromHex("9A0263"));
        break;
    case 35:
        //Serial::getLIgnvsRPM();
        Serial::writeRequestPFC(QByteArray::fromHex("9B0262"));
        break;
    case 36:
        //Serial::getIgnvsBatt();
        Serial::writeRequestPFC(QByteArray::fromHex("9C0261"));
        break;
    case 37:
        //Serial::getBoostvsIgn();
        Serial::writeRequestPFC(QByteArray::fromHex("9D0260"));
        break;
    case 38:
        //Serial::getTrailIgnvsRPM();
        Serial::writeRequestPFC(QByteArray::fromHex("9E025F"));
        break;
    case 39:
        //Serial::getInjSecLagvsBattV();
        Serial::writeRequestPFC(QByteArray::fromHex("9F025E"));
        break;
    case 40:
        //Serial::getKnockWarn();
        Serial::writeRequestPFC(QByteArray::fromHex("A90254"));
        break;
    case 41:
        //Injejtor warning
        Serial::writeRequestPFC(QByteArray::fromHex("A80255"));
        break;
    case 42:
        //Serial::getO2Feedback();
        Serial::writeRequestPFC(QByteArray::fromHex("AA0253"));
        break;
    case 43:
        //Serial::getBoostcontrol();
        Serial::writeRequestPFC(QByteArray::fromHex("AB0252"));
        break;
    case 44:
        //Serial::getSettingProtections();
        Serial::writeRequestPFC(QByteArray::fromHex("AC0251"));
        break;
    case 45:
        //Serial::getTunerString();
        Serial::writeRequestPFC(QByteArray::fromHex("AD0250"));
        break;
    case 46:
        //Serial::getFuelBase0();
        Serial::writeRequestPFC(QByteArray::fromHex("B0024D"));
        break;
    case 47:
        //Serial::getFuelBase1();
        Serial::writeRequestPFC(QByteArray::fromHex("B1024C"));
        break;
    case 48:
        //Serial::getFuelBase2();
        Serial::writeRequestPFC(QByteArray::fromHex("B2024B"));
        break;
    case 49:
        //Serial::getFuelBase3();
        Serial::writeRequestPFC(QByteArray::fromHex("B3024A"));
        break;
    case 50:
        //Serial::getFuelBase4();
        Serial::writeRequestPFC(QByteArray::fromHex("B40249"));
        break;
    case 51:
        //Serial::getFuelBase5();
        Serial::writeRequestPFC(QByteArray::fromHex("B50248"));
        break;
    case 52:
        //Serial::getFuelBase6();
        Serial::writeRequestPFC(QByteArray::fromHex("B60247"));
        break;
    case 53:
        //Serial::getFuelBase7();
        Serial::writeRequestPFC(QByteArray::fromHex("B70246"));
        break;
    case 54:
        //Serial::getInjvsAirTemp();
        Serial::writeRequestPFC(QByteArray::fromHex("B90244"));
        break;
    case 55:
        //Serial::getInjvsTPS();
        Serial::writeRequestPFC(QByteArray::fromHex("BB0242"));
        break;
    case 56:
        //Serial::getPIMScaleOffset();
        Serial::writeRequestPFC(QByteArray::fromHex("BC0241"));
        break;
    case 57:
        //Serial::getWarConStrFlags();
        Serial::writeRequestPFC(QByteArray::fromHex("D60227"));
        break;
// Live Data
    case 58:
        //Serial::getAdvData();
        Serial::writeRequestPFC(QByteArray::fromHex("F0020D"));
        break;
    case 59:
        //Serial::getAux();
        Serial::writeRequestPFC(QByteArray::fromHex("0002FD"));
        break;
    case 60:
        //Serial::getMapIndices();
        Serial::writeRequestPFC(QByteArray::fromHex("DB0222"));
        break;
    case 61:
        //Serial::getSensorData();
        Serial::writeRequestPFC(QByteArray::fromHex("DE021F"));
        break;
    case 62:
        //Serial::getBasic();
        Serial::writeRequestPFC(QByteArray::fromHex("DA0223"));
        break;
    }
}


// Adaptronic streaming comms

void Serial::AdaptronicStartStream()
{
    auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 4096, 21),1); // read first twenty-one realtime values
    if (!reply->isFinished())
        connect(reply, &QModbusReply::finished, this,&Serial::readyToRead);
    else
        delete reply;

}
void Serial::AdaptronicStopStream()
{

}
