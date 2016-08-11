/*
 * Copyright (C) 2016 Bastian Gschrey & Markus Ippy
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

#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QQmlContext>
#include <QQmlApplicationEngine>

Serial::Serial(QObject *parent) :
    QObject(parent),
    m_serialport(Q_NULLPTR),
    m_decoder(Q_NULLPTR),
    m_dashBoard(Q_NULLPTR)
{
    getPorts();
    m_decoder = new Decoder(this);
    m_dashBoard = new DashBoard(this);

    QQmlApplicationEngine *engine = dynamic_cast<QQmlApplicationEngine*>( parent );
    if (engine == Q_NULLPTR)
        return;
    engine->rootContext()->setContextProperty("Dashboard", m_dashBoard);
}

void Serial::initSerialPort()
{
    if (m_serialport)
        delete m_serialport;
    m_serialport = new SerialPort(this);
    connect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
}

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
                            const int &dataBits, const int &stopBits, const int &flowControl )
{
    initSerialPort();

    m_serialport->setPortName(portName);
    m_serialport->setBaudRate(baudRate);
    m_serialport->setParity(parity);
    m_serialport->setDataBits(static_cast<QSerialPort::DataBits>(dataBits + 5));
    m_serialport->setStopBits(static_cast<QSerialPort::StopBits>(stopBits + 1));
    m_serialport->setFlowControl(static_cast<QSerialPort::FlowControl>(flowControl));

    qDebug() << "Try to open SerialPort:";
    if(m_serialport->open(QIODevice::ReadWrite) == false)
    {
        qDebug() << "Open Serial port failed: " << m_serialport->errorString();
    }
}

void Serial::closeConnection()
{
    m_serialport->close();
    qDebug() << "Connection closed.";
}

void Serial::readyToRead()
{
    // TODO: parse received data and set values
    if (0 /* speed */)
    {
        m_dashBoard->setSpeed(123);
        m_dashBoard->setRevs(221);
    }
    readData(m_serialport->readAll());
    // emit SIG_dataAvailable();
}

void Serial::readData(QByteArray serialdata)
{
    if( serialdata.length() )
    {
        quint8 requesttype = serialdata[0];
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


            serialdata.clear();
        }
    }
}

// Serial requests are send via Serial
void Serial::getAdvData()
{
    m_serialport->write(QByteArray::fromHex("F0020D"));
}

void Serial::getSensorData()
{
    m_serialport->write(QByteArray::fromHex("DE021F"));
}

void Serial::getAux()
{
    m_serialport->write(QByteArray::fromHex("0002FD"));
}

void Serial::getMapIndices()
{
    m_serialport->write(QByteArray::fromHex("DB0222"));

}
void Serial::getBasic()
{
    m_serialport->write(QByteArray::fromHex("DA0223"));
}

//Map Readout
void Serial::getRevIdle()
{
    m_serialport->write(QByteArray::fromHex("B80245"));
}
void Serial::getSensorStrings()
{
    m_serialport->write(QByteArray::fromHex("DD0220"));
}
void Serial::getPimStrInjA()
{
    m_serialport->write(QByteArray::fromHex("CB0232"));
}
void Serial::getVersion()
{
    m_serialport->write(QByteArray::fromHex("F50208"));
}
void Serial::getMapRef()
{
    m_serialport->write(QByteArray::fromHex("8A0273"));
}
void Serial::getLeadign1()
{
    m_serialport->write(QByteArray::fromHex("760287"));
}
void Serial::getLeadign2()
{
    m_serialport->write(QByteArray::fromHex("770286"));
}
void Serial::getLeadign3()
{
    m_serialport->write(QByteArray::fromHex("780285"));
}
void Serial::getLeadign4()
{
    m_serialport->write(QByteArray::fromHex("790284"));
}
void Serial::getTrailIgn1()
{
    m_serialport->write(QByteArray::fromHex("81027C"));
}
void Serial::getTrailIgn2()
{
    m_serialport->write(QByteArray::fromHex("82027B"));
}
void Serial::getTrailIgn3()
{
    m_serialport->write(QByteArray::fromHex("83027A"));
}
void Serial::getTrailIgn4()
{
    m_serialport->write(QByteArray::fromHex("840279"));
}
void Serial::getInitPlatform()
{
    m_serialport->write(QByteArray::fromHex("F3020A"));
}
void Serial::getInjOverlap()
{
    m_serialport->write(QByteArray::fromHex("7B0282"));
}
void Serial::getInjvsFuelT()
{
    m_serialport->write(QByteArray::fromHex("7C0281"));
}
void Serial::getTurboTrans()
{
    m_serialport->write(QByteArray::fromHex("7D0280"));
}
void Serial::getOilervsWaterT()
{
    m_serialport->write(QByteArray::fromHex("7E027F"));
}
void Serial::getFanvsWater()
{
    m_serialport->write(QByteArray::fromHex("7F027E"));
}
void Serial::getInjcorr1()
{
    m_serialport->write(QByteArray::fromHex("860277"));
}
void Serial::getInjcorr2()
{
    m_serialport->write(QByteArray::fromHex("870276"));
}
void Serial::getInjcorr3()
{
    m_serialport->write(QByteArray::fromHex("880275"));
}
void Serial::getInjcorr4()
{
    m_serialport->write(QByteArray::fromHex("890274"));
}
void Serial::getFuelInj()
{
    m_serialport->write(QByteArray::fromHex("8D0270"));
}
void Serial::getCranking()
{
    m_serialport->write(QByteArray::fromHex("8E026F"));
}
void Serial::getWaterTcorr()
{
    m_serialport->write(QByteArray::fromHex("8F026E"));
}
void Serial::getInjvsWaterBoost()
{
    m_serialport->write(QByteArray::fromHex("90026D"));
}
void Serial::getInjvsAirTBoost()
{
    m_serialport->write(QByteArray::fromHex("91026C"));
}
void Serial::getInjPrimaryLag()
{
    m_serialport->write(QByteArray::fromHex("92026B"));
}
void Serial::getAccInj()
{
    m_serialport->write(QByteArray::fromHex("93026A"));
}
void Serial::getInjvsAccel()
{
    m_serialport->write(QByteArray::fromHex("940269"));
}
void Serial::getIgnvsAircold()
{
    m_serialport->write(QByteArray::fromHex("960267"));
}
void Serial::getIgnvsWater()
{
    m_serialport->write(QByteArray::fromHex("980265"));
}
void Serial::getIgnvsAirwarm()
{
    m_serialport->write(QByteArray::fromHex("9A0263"));
}
void Serial::getLIgnvsRPM()
{
    m_serialport->write(QByteArray::fromHex("9B0262"));
}
void Serial::getIgnvsBatt()
{
    m_serialport->write(QByteArray::fromHex("9C0261"));
}
void Serial::getBoostvsIgn()
{
    m_serialport->write(QByteArray::fromHex("9D0260"));
}
void Serial::getTrailIgnvsRPM()
{
    m_serialport->write(QByteArray::fromHex("9E025F"));
}
void Serial::getInjSecLagvsBattV()
{
    m_serialport->write(QByteArray::fromHex("9F025E"));
}
void Serial::getInjWarn()
{
    m_serialport->write(QByteArray::fromHex("A80255"));
}
void Serial::getKnockWarn()
{
    m_serialport->write(QByteArray::fromHex("A90254"));
}
void Serial::getO2Feedback()
{
    m_serialport->write(QByteArray::fromHex("AA0253"));
}
void Serial::getBoostcontrol()
{
    m_serialport->write(QByteArray::fromHex("AB0252"));
}
void Serial::getSettingProtections()
{
    m_serialport->write(QByteArray::fromHex("AC0251"));
}
void Serial::getTunerString()
{
    m_serialport->write(QByteArray::fromHex("AD0250"));
}
void Serial::getInjvsAirTemp()
{
    m_serialport->write(QByteArray::fromHex("B90244"));
}
void Serial::getInjvsTPS()
{
    m_serialport->write(QByteArray::fromHex("BA0243"));
}
void Serial::getIgnvsTPS()
{
    m_serialport->write(QByteArray::fromHex("BB0242"));
}
void Serial::getPIMScaleOffset()
{
    m_serialport->write(QByteArray::fromHex("BC0241"));
}
void Serial::getWarConStrFlags()
{
    m_serialport->write(QByteArray::fromHex("D60227"));
}
void Serial::getNotdocumented()
{
    m_serialport->write(QByteArray::fromHex("F40209"));
}

void Serial::getFuelBase0()
{
    m_serialport->write(QByteArray::fromHex("B0024D"));
}
void Serial::getFuelBase1()
{
    m_serialport->write(QByteArray::fromHex("B1024C"));
}
void Serial::getFuelBase2()
{
    m_serialport->write(QByteArray::fromHex("B2024B"));
}
void Serial::getFuelBase3()
{
    m_serialport->write(QByteArray::fromHex("B3024A"));
}
void Serial::getFuelBase4()
{
    m_serialport->write(QByteArray::fromHex("B40249"));
}
void Serial::getFuelBase5()
{
    m_serialport->write(QByteArray::fromHex("B50248"));
}
void Serial::getFuelBase6()
{
    m_serialport->write(QByteArray::fromHex("B60247"));
}
void Serial::getFuelBase7()
{
    m_serialport->write(QByteArray::fromHex("B70246"));
}
//End of serial requests


void Serial::sendRequest(int requestIndex)
{
    switch (requestIndex){

    case 0:
         Serial::getInitPlatform();
         requestIndex++;
         break;
    case 1:
         Serial::getSensorStrings();
         requestIndex++;
         break;
    case 2:
         Serial::getPimStrInjA();
         requestIndex++;
         break;
    case 3:
         Serial::getVersion();
         requestIndex++;
         break;
    case 4:
         Serial::getMapRef();
         requestIndex++;
         break;
    case 5:
         Serial::getRevIdle();
         requestIndex++;
         break;
    case 6:
         Serial::getLeadign1();
         requestIndex++;
         break;
    case 7:
         Serial::getLeadign2();
         requestIndex++;
         break;
    case 8:
         Serial::getLeadign3();
         requestIndex++;
         break;
    case 9:
         Serial::getLeadign4();
         requestIndex++;
         break;
    case 10:
         Serial::getTrailIgn1();
         requestIndex++;
         break;
    case 11:
         Serial::getTrailIgn2();
         requestIndex++;
         break;
    case 12:
         Serial::getTrailIgn3();
         requestIndex++;
         break;
    case 13:
         Serial::getTrailIgn4();
         requestIndex++;
         break;
    case 14:
         Serial::getInitPlatform();
         requestIndex++;
         break;
    case 15:
         Serial::getInjOverlap();
         requestIndex++;
         break;
    case 16:
         Serial::getInjvsFuelT();
         requestIndex++;
         break;
    case 17:
         Serial::getTurboTrans();
         requestIndex++;
         break;
    case 18:
         Serial::getOilervsWaterT();
         requestIndex++;
         break;
    case 19:
         Serial::getFanvsWater();
         requestIndex++;
         break;
    case 20:
         Serial::getInjcorr1();
         requestIndex++;
         break;
    case 21:
         Serial::getInjcorr2();
         requestIndex++;
         break;
    case 22:
         Serial::getInjcorr3();
         requestIndex++;
         break;
    case 23:
         Serial::getInjcorr4();
         requestIndex++;
         break;
    case 24:
         Serial::getFuelInj();
         requestIndex++;
         break;
    case 25:
         Serial::getCranking();
         requestIndex++;
         break;
    case 26:
         Serial::getWaterTcorr();
         requestIndex++;
         break;
    case 27:
         Serial::getInjvsWaterBoost();
         requestIndex++;
         break;
    case 28:
         Serial::getInjvsAirTBoost();
         requestIndex++;
         break;
    case 29:
         Serial::getInjPrimaryLag();
         requestIndex++;
         break;
    case 30:
         Serial::getAccInj();
         requestIndex++;
         break;
    case 31:
         Serial::getInjvsAccel();
         requestIndex++;
         break;
    case 32:
         Serial::getIgnvsAircold();
         requestIndex++;
         break;
    case 33:
         Serial::getIgnvsWater();
         requestIndex++;
         break;
    case 34:
         Serial::getIgnvsAirwarm();
         requestIndex++;
         break;
    case 35:
         Serial::getLIgnvsRPM();
         requestIndex++;
         break;
    case 36:
         Serial::getIgnvsBatt();
         requestIndex++;
         break;
    case 37:
         Serial::getBoostvsIgn();
         requestIndex++;
         break;
    case 38:
         Serial::getTrailIgnvsRPM();
         requestIndex++;
         break;
    case 39:
         Serial::getInjSecLagvsBattV();
         requestIndex++;
         break;
    case 40:
         Serial::getKnockWarn();
         requestIndex++;
         break;
    case 41:
         Serial::getNotdocumented();
         requestIndex++;
        break;
    case 42:
         Serial::getO2Feedback();
         requestIndex++;
         break;
    case 43:
         Serial::getBoostcontrol();
         requestIndex++;
         break;
    case 44:
         Serial::getSettingProtections();
         requestIndex++;
         break;
    case 45:
         Serial::getTunerString();
         requestIndex++;
         break;
    case 46:
         Serial::getFuelBase0();
         requestIndex++;
         break;
    case 47:
         Serial::getFuelBase1();
         requestIndex++;
         break;
    case 48:
         Serial::getFuelBase2();
         requestIndex++;
         break;
    case 49:
         Serial::getFuelBase3();
         requestIndex++;
         break;
    case 50:
         Serial::getFuelBase4();
         requestIndex++;
         break;
    case 51:
         Serial::getFuelBase5();
         requestIndex++;
         break;
    case 52:
         Serial::getFuelBase6();
         requestIndex++;
         break;
    case 53:
         Serial::getFuelBase7();
         requestIndex++;
         break;
    case 54:
         Serial::getInjvsAirTemp();
         requestIndex++;
         break;
    case 55:
         Serial::getInjvsTPS();
         requestIndex++;
         break;
    case 56:
         Serial::getPIMScaleOffset();
         requestIndex++;
         break;
    case 57:
         Serial::getWarConStrFlags();
         requestIndex++;
         break;
// Live Data
    case 58:
        Serial::getAdvData();
        requestIndex++;
        break;
    case 59:
        Serial::getAux();
        requestIndex++;
        break;
    case 60:
        Serial::getMapIndices();
        requestIndex++;
        break;
    case 61:
        Serial::getSensorData();
        requestIndex++;
        break;
    case 62:
        Serial::getBasic();
        requestIndex = 58;
        break;
    }
}


