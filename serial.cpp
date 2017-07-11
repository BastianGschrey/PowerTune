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
  \author Bastian Gschrey & Markus Ippy
*/


#include "serial.h"
#include "decoder.h"
#include "dashboard.h"
#include "serialport.h"
#include "appsettings.h"
#include "gopro.h"
#include "gps.h"
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
#include <QByteArrayMatcher>



int requestIndex = 0; //ID for requested data type Power FC
int ecu =3; //0=apex, 1=adaptronic; 2= Dicktator ECU
int interface; // 0=fcHako, 1=fc-datalogIt
int logging; // 0 Logging off , 1 Logging to file
int loggingstatus;
int Bytesexpected;
int Bytes;
QString Logfilename;
QByteArray checksumhex;
QByteArray recvchecksumhex;

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
    m_gopro(Q_NULLPTR),
    m_gps(Q_NULLPTR),
    m_bytesWritten(0),
    lastRequest(nullptr),
    modbusDevice(nullptr)


{
    modbusDevice = new QModbusRtuSerialMaster(this);
    getPorts();
    m_dashBoard = new DashBoard(this);
    m_decoder = new Decoder(m_dashBoard, this);
    m_appSettings = new AppSettings(this);
    m_gopro = new GoPro(this);
    m_gps = new GPS(m_dashBoard, this);
    connect(m_decoder,SIGNAL(sig_adaptronicReadFinished()),this,SLOT(AdaptronicStartStream()));
    QQmlApplicationEngine *engine = dynamic_cast<QQmlApplicationEngine*>( parent );
    if (engine == Q_NULLPTR)
        return;
    engine->rootContext()->setContextProperty("Dashboard", m_dashBoard);
    engine->rootContext()->setContextProperty("AppSettings", m_appSettings);
    engine->rootContext()->setContextProperty("GoPro", m_gopro);
    engine->rootContext()->setContextProperty("GPS", m_gps);
}

void Serial::initSerialPort()
{
    if (m_serialport)
        delete m_serialport;
    m_serialport = new SerialPort(this);
    connect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    connect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &Serial::handleError);
    connect(m_serialport, &QSerialPort::bytesWritten, this, &Serial::handleBytesWritten);
    connect(&m_timer, &QTimer::timeout, this, &Serial::handleTimeout);
    m_readData.clear();
    //m_timer.start(5000);


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
    qDebug() << "Selected ECU" << ecu;
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
        //m_serialport->setReadBufferSize(103);

        qDebug() << "Try to open SerialPort:";
        if(m_serialport->open(QIODevice::ReadWrite) == false)
        {
            m_dashBoard->setSerialStat(m_serialport->errorString());
            qDebug() << "Open Serial port failed: " << m_serialport->errorString();
        }
        else
        {
            m_dashBoard->setSerialStat(QString("Connected to Serialport"));
        }

        //requestIndex = 0;

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
    //Dicktator
    if (ecuSelect == 2)
    {

        initSerialPort();
        qDebug() << "logging" <<logging;
        m_serialport->setPortName(portName);
        m_serialport->setBaudRate(QSerialPort::Baud19200);
        m_serialport->setParity(QSerialPort::NoParity);
        m_serialport->setDataBits(QSerialPort::Data8);
        m_serialport->setStopBits(QSerialPort::OneStop);
        m_serialport->setFlowControl(QSerialPort::NoFlowControl);
        //m_serialport->setReadBufferSize(103);

        qDebug() << "Try to open SerialPort:";
        if(m_serialport->open(QIODevice::ReadWrite) == false)
        {
            m_dashBoard->setSerialStat(m_serialport->errorString());
            qDebug() << "Open Serial port failed: " << m_serialport->errorString();
        }
        else
        {
            m_dashBoard->setSerialStat(QString("Connected to Serialport"));
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

//test


void Serial::handleTimeout()
{
    qDebug() << "Timeout";
    //request Data Again
    QString fileName = "Errors.txt";
    QFile mFile(fileName);
    if(!mFile.open(QFile::Append | QFile::Text)){
        qDebug() << "Could not open file for writing";
    }
    QTextStream out(&mFile);
    out << "Timeout Request Index " << int(requestIndex)<< "Request identifier " << m_writeData[0] << " lenght received "<< int(m_readData.length())<< " Bytes "<< " Expected Bytes "<< int(Bytesexpected)<< " bytes " <<" Message "<< QByteArray(m_readData.toHex()) <<endl;
    mFile.close();
    Serial::clear();
    qDebug() << "check whats still left on serialport"<< m_serialport->readAll();
    m_serialport->flush();
    m_readData.clear();
    qDebug() << "m_readData"<<m_readData;
    Serial::sendRequest(requestIndex);
}

void Serial::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        QString fileName = "Errors.txt";
        QFile mFile(fileName);
        if(!mFile.open(QFile::Append | QFile::Text)){
            qDebug() << "Could not open file for writing";
        }
        QTextStream out(&mFile);
        out << "Serial Error " << (m_serialport->errorString()) <<endl;
        mFile.close();
        m_dashBoard->setSerialStat(m_serialport->errorString());
        qDebug() <<"Serialport Error" <<(m_serialport->errorString());
    }
}






// Error handling still to be tested
void Serial::readyToRead()
{

    if(ecu == 0)
    {
        m_readData = m_serialport->readAll();
        qDebug() << "ready read slot entered"<<m_readData.toHex();
        Serial::apexiECU(m_readData);
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
    if(ecu == 2) //Dicktator ECU
    {
        m_readData = m_serialport->readAll();
        qDebug() << "ready read slot entered"<<m_readData.toHex();
        Serial::dicktatorECU(m_readData);
    }

}

void Serial::dicktatorECU(const QByteArray &buffer)
{

    //Appending the message until the patterns Start and End Are found , then removing all bytes before and after the message
    m_buffer.append(buffer);
 //   qDebug() << "Dicktator ecu"<< m_buffer.toHex();
    QByteArray startpattern("START");
    QByteArrayMatcher startmatcher(startpattern);
    QByteArray endpattern("END");
    QByteArrayMatcher endmatcher(endpattern);
//    qDebug() << "Dicktator ecu" <<m_buffer;
    int pos = 0;
    while((pos = startmatcher.indexIn(m_buffer, pos)) != -1)
    {
     //   qDebug() << "Dicktator pattern found at pos" << pos;
        if (pos !=0)
        {
            m_buffer.remove(0, pos); //remove all bytes before "Start:
       //     qDebug() << "removed all bytes before the string START " << m_buffer;
        }
        if (pos == 0 ) break;
    }
    int pos2 = 0;
    if((pos2 = endmatcher.indexIn(m_buffer, pos2)) != -1)
    {
  //      qDebug() << "found end of message at " << pos2;
        m_dicktatorMsg.append(m_buffer); // Appending all bytes from "START" to "END" into a new array
        m_dicktatorMsg.remove(pos2+3, m_dicktatorMsg.length()+1 );// Remove all bytes after "END"
        m_buffer.remove(0, pos2+3); //clear all bytes  from buffer that have been written into m_dicktatorMsg
    //    qDebug() << "Finsished processing  Dicktator messag" << m_dicktatorMsg;
    //    qDebug() << "removed processed part from Buffer" << m_buffer;
        m_decoder->decodeDicktator(m_dicktatorMsg);
        m_dicktatorMsg.clear();
    }


}

void Serial::apexiECU(const QByteArray &buffer)
{
    qDebug() << "APEXI ecu";

    if (Bytesexpected != m_buffer.length())
    {
        qDebug() << "starting timer";
        m_timer.start(5000);
    }
    m_buffer.append(buffer);
    if (Bytesexpected > m_buffer.length())
    {
        qDebug() << "clearing"<< Bytesexpected <<m_buffer.length();
        m_buffer.clear();
    }
    qDebug() << "current buffer"<<m_buffer.toHex();
    qDebug() << "buffer length"<<m_buffer.length()<< "Expected"<< Bytesexpected;
/*
    const char start[] =  {m_writeData[0]};

    QByteArray startpattern(start);
    QByteArrayMatcher startmatcher(startpattern);
    qDebug() << "Message"<<start<<"Start"<< startpattern;

    int pos = 0;
    while((pos = startmatcher.indexIn(m_buffer, pos)) != -1)
    {
        qDebug() << "pattern found at pos" << pos;
        if (pos !=0)
        {
            m_buffer.remove(0, pos); //remove all bytes before Identifier
            qDebug() << "removed all bytes before the expected response start" << m_buffer;
        }
        if (pos == 0 ) break;


    }
*/
    if (m_buffer.length() == Bytesexpected)
    {
        m_apexiMsg =  m_buffer;
        //m_apexiMsg.remove(Bytesexpected,m_apexiMsg.length()+1);
        qDebug() << "Extracted Apexi Message" << m_buffer;
        //m_buffer.remove(0,Bytesexpected); // remove extracted message from the buffer
        qDebug() << "left on buffer" << m_buffer;
        m_buffer.clear();
        // Process to calculate checksum not evaluated at the moment , for later use

        int checksum = 255; //calculated checksum from serial message 0xFF - each byte in message (except the last byte)
        recvchecksumhex = QByteArray::number(m_apexiMsg[m_apexiMsg[1]], 16).right(2); // reading the checksum byte , convert to Hex , and cut to 2 positions
        recvchecksumhex = recvchecksumhex.rightJustified(2, '0'); // If the checksumbyte is less than 2 positions , prepend a 0 for example if value is 0x9 turn it into 0x09
        //test1 = test.rightJustified(2, '0');

        for (int i = 0; i <= m_apexiMsg[1]-1; i++)
        {
            checksum = checksum - m_apexiMsg[i];
            checksumhex = QByteArray::number(checksum, 16).right(2);
            checksumhex = checksumhex.rightJustified(2, '0');
        }

        if (checksumhex == recvchecksumhex)
        {
            qDebug() << "Checksum matches expected Checksum " << checksumhex << " " << recvchecksumhex;
            m_timer.stop();
            if(requestIndex <= 62){requestIndex++;}
            else{requestIndex = 59;}
            readData(m_apexiMsg);
            m_apexiMsg.clear();
            Serial::sendRequest(requestIndex);
        }

    }
}




void Serial::readData(QByteArray serialdata)
{

    if( serialdata.length() )
    {
        //Power FC Decode
        quint8 requesttype = serialdata[0];
        qDebug() << "Processing Message"<< serialdata.toHex();

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



            if(requesttype == 0xF0){m_decoder->decodeAdv(serialdata);}
            if(requesttype == 0xDD){m_decoder->decodeSensorStrings(serialdata);}
            if(requesttype == 0xDE){m_decoder->decodeSensor(serialdata);}
            if(requesttype == 0x00){m_decoder->decodeAux(serialdata);}
            if(requesttype == 0x00){m_decoder->decodeAux2(serialdata);}
            if(requesttype == 0xDB){m_decoder->decodeMap(serialdata);}
            if(requesttype == 0xDA){m_decoder->decodeBasic(serialdata);}
            if(requesttype == 0xB8){m_decoder->decodeRevIdle(serialdata);}
            if(requesttype == 0x7D){m_decoder->decodeTurboTrans(serialdata);}
            if(requesttype == 0x76){m_decoder->decodeLeadIgn(serialdata, 0);}
            if(requesttype == 0x77){m_decoder->decodeLeadIgn(serialdata, 5);}
            if(requesttype == 0x78){m_decoder->decodeLeadIgn(serialdata, 10);}
            if(requesttype == 0x79){m_decoder->decodeLeadIgn(serialdata, 15);}
            if(requesttype == 0x81){m_decoder->decodeTrailIgn(serialdata, 0);}
            if(requesttype == 0x82){m_decoder->decodeTrailIgn(serialdata, 5);}
            if(requesttype == 0x83){m_decoder->decodeTrailIgn(serialdata, 10);}
            if(requesttype == 0x84){m_decoder->decodeTrailIgn(serialdata, 15);}
            if(requesttype == 0x86){m_decoder->decodeInjcorr(serialdata, 0);}
            if(requesttype == 0x87){m_decoder->decodeInjcorr(serialdata, 5);}
            if(requesttype == 0x88){m_decoder->decodeInjcorr(serialdata, 10);}
            if(requesttype == 0x89){m_decoder->decodeInjcorr(serialdata, 15);}

            if(requesttype == 0xB0){m_decoder->decodeFuelBase(serialdata, 0);}
            if(requesttype == 0xB1){m_decoder->decodeFuelBase(serialdata, 1);}
            if(requesttype == 0xB2){m_decoder->decodeFuelBase(serialdata, 2);}
            if(requesttype == 0xB3){m_decoder->decodeFuelBase(serialdata, 3);}
            if(requesttype == 0xB4){m_decoder->decodeFuelBase(serialdata, 4);}
            if(requesttype == 0xB5){m_decoder->decodeFuelBase(serialdata, 5);}
            if(requesttype == 0xB6){m_decoder->decodeFuelBase(serialdata, 6);}
            if(requesttype == 0xB7){m_decoder->decodeFuelBase(serialdata, 7);}

            if(requesttype == 0xF5){m_decoder->decodeVersion(serialdata);}
            if(requesttype == 0xF3){m_decoder->decodeInit(serialdata);}
            if(requesttype == 0xAB){m_decoder->decodeBoostCont(serialdata);}
            if(requesttype == 0x7B){m_decoder->decodeInjOverlap(serialdata);}
            if(requesttype == 0x92){m_decoder->decodeInjPriLagvsBattV(serialdata);}
            if(requesttype == 0x9F){m_decoder->decodeInjScLagvsBattV(serialdata);}
            if(requesttype == 0x8D){m_decoder->decodeFuelInjectors(serialdata);}
        }
        serialdata.clear();
        \

    }


}
void Serial::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
    if (m_bytesWritten == m_writeData.size()) {
        m_bytesWritten = 0;
        qDebug() <<("Data successfully sent to port") << (m_serialport->portName());

    }
}
// Serial requests are send via Serial
void Serial::writeRequestPFC(QByteArray p_request)
{
    qDebug() << "write request" << p_request.toHex();
    m_writeData = p_request;
    qint64 bytesWritten = m_serialport->write(p_request);

    //Action to be implemented
    if (bytesWritten == -1) {
        m_dashBoard->setSerialStat(m_serialport->errorString());
        qDebug() << "Write request to port failed" << (m_serialport->errorString());
    } else if (bytesWritten != m_writeData.size()) {
        m_dashBoard->setSerialStat(m_serialport->errorString());
        qDebug() << "could not write complete request to port" << (m_serialport->errorString());
    }

    //m_timer.start(5000);
}

//Power FC requests

void Serial::sendRequest(int requestIndex)
{
    switch (requestIndex){

    case 0:
        //First request from (this is what FC Edit does seems to get a 4 or 8 Byte response dependant on Aux inputs ??)
        Serial::writeRequestPFC(QByteArray::fromHex("0102FC"));
        if (interface ==0)
        {Bytesexpected = 4;}
        if (interface ==1)
        {Bytesexpected = 8;}
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
        Bytesexpected= 103;
        break;
    case 10:
        //Serial::getTrailIgn1();
        Serial::writeRequestPFC(QByteArray::fromHex("81027C"));
        Bytesexpected= 103;
        break;
    case 11:
        //Serial::getTrailIgn2();
        Serial::writeRequestPFC(QByteArray::fromHex("82027B"));
        Bytesexpected= 103;
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


//function for Start Logging
void Serial::startLogging(const QString &logfilenameSelect, const int &loggeron)
{
    loggingstatus = loggeron;
    Logfilename = logfilenameSelect;
    qDebug() << Logfilename;
    qDebug() << "on off"<< loggingstatus;
    if (ecu == 0)    //Apexi
    {
        {
            m_decoder->loggerApexi(Logfilename);
        }
    }
    if (ecu == 1)    //Adaptronic
    {
        QString filename = Logfilename + ".csv";
        QFile file( filename );
        qDebug() << "Adaptronic start Log";
        if ( file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &file );
            stream << "Time (s),RPM,MAP (kPa),MAT (°C),WT (°C),AuxT (°C),AFR,Knock,TPS %,Idle,MVSS (km/h),SVSS (km/h),Batt (V),Inj 1 (ms), Inj 2 (ms),Inj 3 (ms),Inj 4 (ms),Ign 1 (°),Ign 2 (°),Ign 3 (°),Ign 4 (°),Trim" << endl;
        }
        file.close();
        m_decoder->loggerAdaptronic(Logfilename);
        m_decoder->loggerActivationstatus(loggingstatus);
    }


    return;
}

//function for Stop Logging
void Serial::stopLogging(const QString &logfilenameSelect, const int &loggeron)
{
    loggingstatus = loggeron;
    m_decoder->loggerActivationstatus(loggingstatus);
    qDebug() << "Stop Logging ";
    return;
}


void Serial::Auxcalc (const QString &unitaux1,const int &an1V0,const int &an2V5,const QString &unitaux2,const int &an3V0,const int &an4V5,const QString &unitaux3,const int &an5V0,const int &an6V5,const QString &unitaux4,const int &an7V0,const int &an8V5)
{
    int aux1min = an1V0;
    int aux2max = an2V5;
    int aux3min = an3V0;
    int aux4max = an4V5;
    int aux5min = an5V0;
    int aux6max = an6V5;
    int aux7min = an7V0;
    int aux8max = an8V5;
    QString Auxunit1 = unitaux1;
    QString Auxunit2 = unitaux2;
    QString Auxunit3 = unitaux3;
    QString Auxunit4 = unitaux4;
    m_decoder->calculatorAux(aux1min,aux2max,aux3min,aux4max,aux5min,aux6max,aux7min,aux8max,Auxunit1,Auxunit2,Auxunit3,Auxunit4);
}
