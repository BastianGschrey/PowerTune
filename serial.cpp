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
#include <QFile>
#include <QTextStream>


int requestIndex = 0; //ID for requested data type Power FC
int ecu; //0=apex, 1=adaptronic;
int interface; // 0=fcHako, 1=fc-datalogIt
int logging; // 0 Logging off , 1 Logging to file
int Bytesexpected = 500;
//reply = new QModbusReply;


Serial::~Serial()
{

    if (modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;

}

Serial::Serial(QObject *parent) :
    QObject(parent),
    m_serialport(Q_NULLPTR),
    m_decoder(Q_NULLPTR),
    m_dashBoard(Q_NULLPTR),
    lastRequest(nullptr),
    modbusDevice(nullptr)


{
    modbusDevice = new QModbusRtuSerialMaster(this);
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
void Serial::openConnection(const QString &portName, const int &ecuSelect, const int &interfaceSelect, const int &loggingSelect)
{

    ecu = ecuSelect;
    interface = interfaceSelect;
    logging = loggingSelect;


    //Apexi
    if (ecuSelect == 0)
    {

     initSerialPort();
qDebug() << "logging" <<logging;
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

        if (!modbusDevice)
               return;

        if (modbusDevice->state() != QModbusDevice::ConnectedState)
        {
            qDebug() << "modbus is not connected";
                //modbusDevice = new QModbusRtuSerialMaster(this);
                modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,portName);
                modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,57600);
                modbusDevice->setTimeout(200);
                modbusDevice->setNumberOfRetries(10);
                modbusDevice->connectDevice();

                Serial::AdaptronicStartStream();

        }

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
        qDebug() << "device disconnected";
    }
}
// Error handling still to be tested
void Serial::readyToRead()
{
    if(ecu == 0)
    {

    int timeOut = 200; // timeout in milisec.
    int Bytes = 0;
    QByteArray recvData;
    QTime startTime = QTime::currentTime();

    while (Bytesexpected > Bytes)
        {
              if ( startTime.msecsTo(QTime::currentTime()) > timeOut ) break;
              qDebug() << "Bytes expected"<<Bytesexpected;
              qDebug() << "Bytes Available to read"<<m_serialport->bytesAvailable();
              Bytes = m_serialport->bytesAvailable();

         }

    if  (Bytesexpected == m_serialport->bytesAvailable())
        {
         recvData = m_serialport->read(Bytesexpected);
        }
            // Process to calculate checksum not evaluated at the moment , for later use
/*
                int checksum = 255; //calculated checksum from serial message 0xFF - each byte in message (except the last byte)
                QByteArray checksumhex;
                QByteArray recvchecksumhex = QByteArray::number(recvData[recvData[1]], 16).right(2); // reading the checksum byte , convert to Hex , and cut to 2 positions
                recvchecksumhex = recvchecksumhex.rightJustified(2, '0'); // If the checksumbyte is less than 2 positions , prepend a 0 for example if value is 0x9 turn it into 0x09
                //test1 = test.rightJustified(2, '0');

                for (int i = 0; i <= recvData[1]-1; i++)
                {
                checksum = checksum - recvData[i];
                checksumhex = QByteArray::number(checksum, 16).right(2);
                checksumhex = checksumhex.rightJustified(2, '0');
                }
*/
    if(Bytesexpected == recvData.size())                 //if the received data lenght equals the message lenght from lenght byte + identifier byte (correct message lenght received )
            {
        //qDebug() << "Message"<<recvData.toHex()<< "Checksum calculated" <<checksumhex << "Checksum receveived"<< recvchecksumhex;
            if(requestIndex <= 62){requestIndex++;}
            else{requestIndex = 59;}
            readData(recvData);
            recvData.clear();
            m_serialport->flush();
            }
     else
    {
        //Read Data and create error file
        if (logging ==1 ){
        recvData += m_serialport->readAll();
        QString fileName = "Errors.txt";
        QFile mFile(fileName);
        if(!mFile.open(QFile::Append | QFile::Text)){
            qDebug() << "Could not open file for writing";
        }
        QTextStream out(&mFile);
        out << "Request Index " << int(requestIndex)<< " lenght received "<< int(recvData.length())<< " Bytes "<< " Expected Bytes "<< int(Bytesexpected)<< " bytes " <<" Message "<< QByteArray(recvData.toHex()) <<endl;
        mFile.close();
        }
        qDebug() << "Received data  NOK request"<<requestIndex;
        //qDebug() << "Receved data "<<recvData.toHex()<< "Checksum calculated" <<checksumhex << "Checksum receveived"<< recvchecksumhex;
        recvData.clear();
        Serial::sendRequest(requestIndex);
    }
   }



/*
    if(ecu == 0)

        {
        QTime startTime = QTime::currentTime();
        int timeOut = 500; // timeout in milisec.
        QByteArray recvData;
        int Bytesexpected = 100;

        while (Bytesexpected > recvData.size()) //check the sc
            {
                  if ( startTime.msecsTo(QTime::currentTime()) > timeOut ) break;
                 // if (recvData == )
                  //      qDebug() << "Bytes expected"<<Bytesexpected;
                  //      qDebug() << "Bytes Available to read"<<m_serialport->bytesAvailable();
                  recvData += m_serialport->readAll();
                  if ( startTime.msecsTo(QTime::currentTime()) > timeOut ) break;
                  Bytesexpected = recvData[1]+1;
             }
*/


/*
// Pass OK Message on for proccessing
        if(Bytesexpected == recvData.size()) //if the received data lenght equals the message lenght from lenght byte + // Identifier byte (correct message lenght received )
                {
             //   qDebug() << "Received data OK"<<Bytesexpected;
             //   qDebug() << "time taken (ms) "<<(QTime::currentTime());
                if(requestIndex <= 62){requestIndex++;}
                else{requestIndex = 59;}
              //  m_dashboard->setInjDuty(recvData.toHex());
                readData(recvData);
                recvData.clear();
                m_serialport->flush();
                }
         else
        {
        qDebug() << "Received data  NOK message"<<requestIndex;
        qDebug() << "Incorrect message received:"<< recvData.toHex();
        Serial::sendRequest(requestIndex);
        }
       }
*/
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

//Write all OK Serial Messages to a file
        if(serialdata[1] + 1 == serialdata.length())
           {
            if (logging ==1 ){
            QString fileName = "OK Messages.txt";
            QFile mFile(fileName);
            if(!mFile.open(QFile::Append | QFile::Text)){
                qDebug() << "Could not open file for writing";
            }
            QTextStream out(&mFile);
            out << QByteArray(serialdata.toHex())<< endl;
            mFile.close();
            }



            if(serialdata.length() == 33 && requesttype == 0xF0){m_decoder->decodeAdv(serialdata);}
            if(requesttype == 0xDD){m_decoder->decodeSensorStrings(serialdata);}
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
    m_serialport->waitForBytesWritten(1000); // timeout 1 sec (1000 msec)
}

//Power FC requests

void Serial::sendRequest(int requestIndex)
{
    switch (requestIndex){

    case 0:
        //First request from (this is what FC Edit does)
        Serial::writeRequestPFC(QByteArray::fromHex("0102FC"));
        Bytesexpected = 4;
        break;
    case 1:
        //Init Platform for the first time ( usully returns a malformed packet)
        Serial::writeRequestPFC(QByteArray::fromHex("F3020A"));
        Bytesexpected = 11;
        break;
    case 2:
        //Serial::getWarConStrFlags();
        Serial::writeRequestPFC(QByteArray::fromHex("D60227"));
        Bytesexpected = 88;
        break;
    case 3:
        //Serial::getVersion();
        Serial::writeRequestPFC(QByteArray::fromHex("F50208"));
        Bytesexpected = 8;
        break;
    case 4:
        //Serial::getMapRef();
        Serial::writeRequestPFC(QByteArray::fromHex("8A0273"));
        Bytesexpected = 83;
        break;
    case 5:
        //Serial::getRevIdle();
        Serial::writeRequestPFC(QByteArray::fromHex("B80245"));
        Bytesexpected = 17;
        break;
    case 6:
        //Serial::getLeadign1();
        Serial::writeRequestPFC(QByteArray::fromHex("760287"));
        Bytesexpected = 103;
        break;
    case 7:
        //Serial::getLeadign2();
        Serial::writeRequestPFC(QByteArray::fromHex("770286"));
        Bytesexpected = 103;
        break;
    case 8:
        //Serial::getLeadign3();
        Serial::writeRequestPFC(QByteArray::fromHex("780285"));
        Bytesexpected = 103;
        break;
    case 9:
        //Serial::getLeadign4();
        Serial::writeRequestPFC(QByteArray::fromHex("790284"));
        Bytesexpected = 103;
        break;
    case 10:
        //Serial::getTrailIgn1();
        Serial::writeRequestPFC(QByteArray::fromHex("81027C"));
        Bytesexpected = 103;
        break;
    case 11:
        //Serial::getTrailIgn2();
        Serial::writeRequestPFC(QByteArray::fromHex("82027B"));
        Bytesexpected = 103;
        break;
    case 12:
        //Serial::getTrailIgn3();
        Serial::writeRequestPFC(QByteArray::fromHex("83027A"));
        Bytesexpected = 103;
        break;
    case 13:
        //Serial::getTrailIgn4();
        Serial::writeRequestPFC(QByteArray::fromHex("840279"));
        Bytesexpected = 103;
        break;
    case 14:
        //Serial::getPimStrInjA();
        Serial::writeRequestPFC(QByteArray::fromHex("CB0232"));
        Bytesexpected = 110;
        break;
    case 15:
        //Serial::getInjOverlap();
        Serial::writeRequestPFC(QByteArray::fromHex("7B0282"));
        Bytesexpected = 9;
        break;
    case 16:
        //Serial::getInjvsFuelT();
        Serial::writeRequestPFC(QByteArray::fromHex("7C0281"));
        Bytesexpected = 12;
        break;
    case 17:
        //Serial::getTurboTrans();
        Serial::writeRequestPFC(QByteArray::fromHex("7D0280"));
        Bytesexpected = 12;
        break;
    case 18:
        //Serial::getOilervsWaterT();
        Serial::writeRequestPFC(QByteArray::fromHex("7E027F")); //one of these is wrong
        Bytesexpected = 9;
        break;
    case 19:
        //Serial::getFanvsWater();
        Serial::writeRequestPFC(QByteArray::fromHex("7F027E")); //one of these is wrong
        Bytesexpected = 6;
        break;
    case 20:
        //Serial::getInjcorr1();
        Serial::writeRequestPFC(QByteArray::fromHex("860277"));
        Bytesexpected = 103;
        break;
    case 21:
        //Serial::getInjcorr2();
        Serial::writeRequestPFC(QByteArray::fromHex("870276"));
        Bytesexpected = 103;
        break;
    case 22:
        //Serial::getInjcorr3();
        Serial::writeRequestPFC(QByteArray::fromHex("880275"));
        Bytesexpected = 103;
        break;
    case 23:
        //Serial::getInjcorr4();
        Serial::writeRequestPFC(QByteArray::fromHex("890274"));
        Bytesexpected = 103;
        break;
    case 24:
        //Serial::getFuelInj();
        Serial::writeRequestPFC(QByteArray::fromHex("8D0270"));
        Bytesexpected = 27;
        break;
    case 25:
        //Serial::getCranking();
        Serial::writeRequestPFC(QByteArray::fromHex("8E026F"));
        Bytesexpected = 15;
        break;
    case 26:
        //Serial::getWaterTcorr();
        Serial::writeRequestPFC(QByteArray::fromHex("8F026E"));
        Bytesexpected = 17;
        break;
    case 27:
        //Serial::getInjvsWaterBoost();
        Serial::writeRequestPFC(QByteArray::fromHex("90026D"));
        Bytesexpected = 9;
        break;
    case 28:
        //Serial::getInjvsAirTBoost();
        Serial::writeRequestPFC(QByteArray::fromHex("91026C"));
        Bytesexpected = 11;
        break;
    case 29:
        //Serial::getInjPrimaryLag();
        Serial::writeRequestPFC(QByteArray::fromHex("92026B"));
        Bytesexpected = 15;
        break;
    case 30:
        //Serial::getAccInj();
        Serial::writeRequestPFC(QByteArray::fromHex("93026A"));
        Bytesexpected = 28;
        break;
    case 31:
        //Serial::getInjvsAccel();
        Serial::writeRequestPFC(QByteArray::fromHex("940269"));
        Bytesexpected = 12;
        break;
    case 32:
        //Serial::getIgnvsAircold();
        Serial::writeRequestPFC(QByteArray::fromHex("960267"));
        Bytesexpected = 7;
        break;
    case 33:
        //Serial::getIgnvsWater();
        Serial::writeRequestPFC(QByteArray::fromHex("980265"));
        Bytesexpected = 7;
        break;
    case 34:
        //Serial::getIgnvsAirwarm();
        Serial::writeRequestPFC(QByteArray::fromHex("9A0263"));
        Bytesexpected = 9;
        break;
    case 35:
        //Serial::getLIgnvsRPM();
        Serial::writeRequestPFC(QByteArray::fromHex("9B0262"));
        Bytesexpected = 9;
        break;
    case 36:
        //Serial::getIgnvsBatt();
        Serial::writeRequestPFC(QByteArray::fromHex("9C0261"));
        Bytesexpected = 9;
        break;
    case 37:
        //Serial::getBoostvsIgn();
        Serial::writeRequestPFC(QByteArray::fromHex("9D0260"));
        Bytesexpected = 7;
        break;
    case 38:
        //Serial::getTrailIgnvsRPM();
        Serial::writeRequestPFC(QByteArray::fromHex("9E025F"));
        Bytesexpected = 9;
        break;
    case 39:
        //Serial::getInjSecLagvsBattV();
        Serial::writeRequestPFC(QByteArray::fromHex("9F025E"));
        Bytesexpected = 15;
        break;
    case 40:
        //Serial::getKnockWarn();
        Serial::writeRequestPFC(QByteArray::fromHex("A90254"));
        Bytesexpected = 7;
        break;
    case 41:
        //Injejtor warning
        Serial::writeRequestPFC(QByteArray::fromHex("A80255"));
        Bytesexpected = 7;
        break;
    case 42:
        //Serial::getO2Feedback();
        Serial::writeRequestPFC(QByteArray::fromHex("AA0253"));
        Bytesexpected = 6;
        break;
    case 43:
        //Serial::getBoostcontrol();
        Serial::writeRequestPFC(QByteArray::fromHex("AB0252"));
        Bytesexpected = 14;
        break;
    case 44:
        //Serial::getSettingProtections();
        Serial::writeRequestPFC(QByteArray::fromHex("AC0251"));
        Bytesexpected = 13;
        break;
    case 45:
        //Serial::getTunerString();
        Serial::writeRequestPFC(QByteArray::fromHex("AD0250"));
        Bytesexpected = 11;
        break;
    case 46:
        //Serial::getFuelBase0();
        Serial::writeRequestPFC(QByteArray::fromHex("B0024D"));
        Bytesexpected = 103;
        break;
    case 47:
        //Serial::getFuelBase1();
        Serial::writeRequestPFC(QByteArray::fromHex("B1024C"));
        Bytesexpected = 103;
        break;
    case 48:
        //Serial::getFuelBase2();
        Serial::writeRequestPFC(QByteArray::fromHex("B2024B"));
        Bytesexpected = 103;
        break;
    case 49:
        //Serial::getFuelBase3();
        Serial::writeRequestPFC(QByteArray::fromHex("B3024A"));
        Bytesexpected = 103;
        break;
    case 50:
        //Serial::getFuelBase4();
        Serial::writeRequestPFC(QByteArray::fromHex("B40249"));
        Bytesexpected = 103;
        break;
    case 51:
        //Serial::getFuelBase5();
        Serial::writeRequestPFC(QByteArray::fromHex("B50248"));
        Bytesexpected = 103;
        break;
    case 52:
        //Serial::getFuelBase6();
        Serial::writeRequestPFC(QByteArray::fromHex("B60247"));
        Bytesexpected = 103;
        break;
    case 53:
        //Serial::getFuelBase7();
        Serial::writeRequestPFC(QByteArray::fromHex("B70246"));
        Bytesexpected = 103;
        break;
    case 54:
        //Serial::getInjvsAirTemp();
        Serial::writeRequestPFC(QByteArray::fromHex("B90244"));
        Bytesexpected = 15;
        break;
    case 55:
        //Serial::getInjvsTPS();
        Serial::writeRequestPFC(QByteArray::fromHex("BB0242"));
        Bytesexpected = 11;
        break;
    case 56:
        //Serial::getPIMScaleOffset();
        Serial::writeRequestPFC(QByteArray::fromHex("BC0241"));
        Bytesexpected = 23;
        break;
    case 57:
        //Init Platform
        Serial::writeRequestPFC(QByteArray::fromHex("F3020A"));
        Bytesexpected = 11;
        break;
    case 58:
        //Serial::getSensorStrings();
        Serial::writeRequestPFC(QByteArray::fromHex("DD0220"));
        Bytesexpected = 83;
        break;



// Live Data
    case 59:
        //Serial::getAdvData();
        Serial::writeRequestPFC(QByteArray::fromHex("F0020D"));
        Bytesexpected = 33;
        break;
    case 60:
        //Serial::getAux();
        Serial::writeRequestPFC(QByteArray::fromHex("0002FD"));
        if (interface ==0)
        {Bytesexpected = 7;}
        if (interface ==1)
            {Bytesexpected = 11;}
        break;
    case 61:
        //Serial::getMapIndices();
        Serial::writeRequestPFC(QByteArray::fromHex("DB0222"));
        Bytesexpected = 5;
        break;
    case 62:
        //Serial::getSensorData();
        Serial::writeRequestPFC(QByteArray::fromHex("DE021F"));
        Bytesexpected = 21;
        break;
    case 63:
        //Serial::getBasic();
        Serial::writeRequestPFC(QByteArray::fromHex("DA0223"));
       Bytesexpected = 23;
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
