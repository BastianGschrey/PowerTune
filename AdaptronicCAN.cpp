/*
 * Copyright (C) 2018 Markus Ippy, Bastian Gschrey,
 * use this program at your own risk.
  \file AdaptronicCAN.cpp
  \brief Receive Messages from Adaptronic Modular via CAN
  \author Markus Ippy, Bastian Gschrey
  \based on the information from http://www.adaptronic.com.au/files/Adap_config/Adaptronic_Full_Configuration.htm
 */

#include "AdaptronicCAN.h"
#include "dashboard.h"
#include <QDebug>
#include <QtEndian>

AdaptronicCAN::AdaptronicCAN(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)

{

}
AdaptronicCAN::AdaptronicCAN(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{


}

AdaptronicCAN::~AdaptronicCAN()
{
}

void AdaptronicCAN::openCAN()
{


    if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan")))
    {
        QString errorString;
        m_canDevice = QCanBus::instance()->createDevice(QStringLiteral("socketcan"),
                                                                       QStringLiteral("can0"),&errorString);

        if (!m_canDevice) {
            qDebug() << ("Error creating device");
            return;
        }



        if(m_canDevice->connectDevice()){
            qDebug() << m_canDevice->state();
            qDebug() << m_canDevice;
            qDebug() << "device connected!";
            //connect(m_canDevice,SIGNAL(framesReceived()),this,SLOT(readyToRead()));
            connect(m_canDevice, &QCanBusDevice::framesReceived, this, &AdaptronicCAN::readyToRead);
        }

    }


}






void AdaptronicCAN::closeConnection()
{
    disconnect(m_canDevice,SIGNAL(framesReceived()),this,SLOT(readyToRead()));
    if (m_canDevice->ConnectedState)
    m_canDevice->disconnectDevice();


}
void AdaptronicCAN::readyToRead()
{
    if (!m_canDevice){
        return;
    }

    while (m_canDevice->framesAvailable()) {
        const QCanBusFrame frame = m_canDevice->readFrame();
        /*// Just for testing  start
        QString view;
        if (frame.frameType() == QCanBusFrame::ErrorFrame)
            view = m_canDevice->interpretErrorFrame(frame);
        else
            view = frame.toString();*/

        const QString time = QString::fromLatin1("%1.%2  ")
                .arg(frame.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
                .arg(frame.timeStamp().microSeconds() / 100, 4, 10, QLatin1Char('0'));
        // Just for testing  end

        //qDebug() << time << view;

        // This section will be used to decode the received Frames currently shows only the the raw payload of a Adress
        QByteArray splitpayload = frame.payload();
        payload* info=reinterpret_cast<payload*>(splitpayload.data());
        pkgpayload[0] = qFromBigEndian(info->CH1);
        pkgpayload[1] = qFromBigEndian(info->CH2);
        pkgpayload[2] = qFromBigEndian(info->CH3);
        pkgpayload[3] = qFromBigEndian(info->CH4);


        switch(frame.frameId()) {

        case 0x300:
            //"Voltage_IMAP_int"(pkgpayload[0]/1000)
            //"Voltage_EMAP_int"(pkgpayload[1]/1000)
            //"Voltage_IMAP_ext"(pkgpayload[2]/1000)
            //"Voltage_EMAP_ext"(pkgpayload[3]/1000)
            break;
        case 0x301:
            m_dashboard->setThrottleV(pkgpayload[0]/1000);
            //"Voltage_TPS2"(pkgpayload[1]/1000)
            m_dashboard->setO2volt(pkgpayload[2]/1000);
            m_dashboard->setO2volt_2(pkgpayload[3]/1000);
            break;
        case 0x302:
            //"Voltage_ECT"(pkgpayload[0]/1000)
            //"Voltage_MAT"(pkgpayload[1]/1000)
            //"Voltage_OilT"(pkgpayload[2]/1000)
            //"Voltage_FuelT"(pkgpayload[3]/1000)
            break;
        case 0x303://"Voltage_OilP"(pkgpayload[0]/1000)
            //"Voltage_FuelP"(pkgpayload[1]/1000)
            //"Voltage_Servo"(pkgpayload[2]/1000)
            //"Voltage_Ext1"(pkgpayload[3]/1000)
            break;
        case 0x304:
            //"Voltage_Ext2"(pkgpayload[0]/1000)
            //"Voltage_12V"(pkgpayload[1]/1000)
            m_dashboard->setBatteryV(pkgpayload[1]/1000);
            //"Voltage_5V"(pkgpayload[2]/1000)
            //"Voltage_SGND current"(pkgpayload[3]/1000)
            break;
        case 0x305:
            //"Mini Ana In #1 V1"(pkgpayload[0]/1000)
            //"Mini Ana In #1 V2"(pkgpayload[1]/1000)
            //"Mini Ana In #1 V3"(pkgpayload[2]/1000)
            //"Mini Ana In #1 V4"(pkgpayload[3]/1000)
            break;
        case 0x306:
            //"Mini Ana In #1 5V out"(pkgpayload[0]/1000)
            //"Mini Ana In #2 V1"(pkgpayload[1]/1000)
            //"Mini Ana In #2 V2"(pkgpayload[2]/1000)
            //"Mini Ana In #2 V3"(pkgpayload[3]/1000)
            break;
        case 0x307:
            //"Mini Ana In #2 V4"(pkgpayload[0]/1000)
            //"Mini Ana In #2 5V out"(pkgpayload[1]/1000)
            //"Mini Ana In #3 V1"(pkgpayload[2]/1000)
            //"Mini Ana In #3 V2"(pkgpayload[3]/1000)
            break;
        case 0x308:
            //"Mini Ana In #3 V3"(pkgpayload[0]/1000)
            //"Mini Ana In #3 V4"(pkgpayload[1]/1000)
            //"Mini Ana In #3 5V out"(pkgpayload[2]/1000)
            //"Mini Ana In #4 V1"(pkgpayload[3]/1000)
            break;
        case 0x309:
            //"Mini Ana In #4 V2"(pkgpayload[0]/1000)
            //"Mini Ana In #4 V3"(pkgpayload[1]/1000)
            //"Mini Ana In #4 V4"(pkgpayload[2]/1000)
            //"Mini Ana In #4 5V out"(pkgpayload[3]/1000)
            break;
        case 0x30A:
            //"Analogue Voltage 40"(pkgpayload[0]/1000)
            //"Analogue Voltage 41"(pkgpayload[1]/1000)
            //"Analogue Voltage 42"(pkgpayload[2]/1000)
            //"Analogue Voltage 43"(pkgpayload[3]/1000)
            break;
        case 0x30B:
            //"Analogue Voltage 44"(pkgpayload[0]/1000)
            //"Analogue Voltage 45"(pkgpayload[1]/1000)
            //"Analogue Voltage 46"(pkgpayload[2]/1000)
            //"Analogue Voltage 47"(pkgpayload[3]/1000)
            break;
        case 0x30C:
            //"Analogue Voltage 48"(pkgpayload[0]/1000)
            //"Analogue Voltage 49"(pkgpayload[1]/1000)
            //"Analogue Voltage 50"(pkgpayload[2]/1000)
            //"Analogue Voltage 51"(pkgpayload[3]/1000)
            break;
        case 0x30D:
            //"Analogue Voltage 52"(pkgpayload[0]/1000)
            //"Analogue Voltage 53"(pkgpayload[1]/1000)
            //"Analogue Voltage 54"(pkgpayload[2]/1000)
            //"Analogue Voltage 55"(pkgpayload[3]/1000)
            break;
        case 0x30E:
            //"Analogue Voltage 56"(pkgpayload[0]/1000)
            //"Analogue Voltage 57"(pkgpayload[1]/1000)
            //"Analogue Voltage 58"(pkgpayload[2]/1000)
            //"Analogue Voltage 59"(pkgpayload[3]/1000)
            break;
        case 0x30F:
            //"Analogue Voltage 60"(pkgpayload[0]/1000)
            //"Analogue Voltage 61"(pkgpayload[1]/1000)
            //"Analogue Voltage 62"(pkgpayload[2]/1000)
            //"Analogue Voltage 63"(pkgpayload[3]/1000)
            break;
        case 0x310:
            m_dashboard->setRevs(pkgpayload[0]);
            //"Period for cyl 1"(pkgpayload[1]/1000)
            //"Period for cyl 2"(pkgpayload[2]/1000)
            //"Period for cyl 3"(pkgpayload[3]/1000)
            break;
        case 0x311:
            //"Period for cyl 4"(pkgpayload[0]/1000)
            //"Period for cyl 5"(pkgpayload[1]/1000)
            //"Period for cyl 6"(pkgpayload[2]/1000)
            //"Period for cyl 7"(pkgpayload[3]/1000)
            break;
        case 0x312:
            //"Period for cyl 8"(pkgpayload[0]/1000)
            //"Period for cyl 9"(pkgpayload[1]/1000)
            //"Period for cyl 10"(pkgpayload[2]/1000)
            //"Period for cyl 11"(pkgpayload[3]/1000)
            break;
        case 0x313:
            //"Period for cyl 12"(pkgpayload[0]/1000)
            //"Period for cyl 13"(pkgpayload[1]/1000)
            //"Period for cyl 14"(pkgpayload[2]/1000)
            //"Period for cyl 15"(pkgpayload[3]/1000)
            break;
        case 0x314:
            //"Period for cyl 16"(pkgpayload[0]/1000)
            //"CAS3 period"(pkgpayload[1]/100)
            //"CAS3 low time"(pkgpayload[2]/100)
            //"CAS3 frequency"(pkgpayload[3]/10)
            break;

        case 0x315:
            //"VSS1 period"(pkgpayload[0]/0.1)
            //"VSS1 frequency"(pkgpayload[1]/10)
            //"VSS2 period"(pkgpayload[2]/0.1)
            //"VSS2 frequency"(pkgpayload[3]/10)
            break;
        case 0x316:
            //"VSS3 period"(pkgpayload[0]/0.1)
            //"VSS3 frequency"(pkgpayload[1]/10)
            //"VSS4 period"(pkgpayload[2]/0.1)
            //"VSS4 frequency"(pkgpayload[3]/10)
            break;
        case 0x317:
            //"VVT1 raw angle"(pkgpayload[0]/10)
            //"VVT2 raw angle"(pkgpayload[1]/10)
            //"VVT3 raw angle"(pkgpayload[2]/10)
            //"VVT4 raw angle"(pkgpayload[3]/10)
            break;
        case 0x318:
            m_dashboard->setaccelx(pkgpayload[0]/1000);
            //qDebug() << (pkgpayload[0]/1000);
            m_dashboard->setaccely(pkgpayload[1]/1000);
            m_dashboard->setaccelz(pkgpayload[2]/1000);
            //m_dashboard->setgyrox(pkgpayload[3]/10); //Yaw
            break;
        case 0x319:
            //m_dashboard->setgyroy(pkgpayload[0]/10); //Pitch
            //qDebug() << (pkgpayload[0]/10);
            //m_dashboard->setgyroz(pkgpayload[1]/10); //Roll
            //qDebug() << (pkgpayload[1]/10);
            break;
        case 0x31A:
            //"GPS Long low"(pkgpayload[0])
            //"GPS Long high"(pkgpayload[1])
            //"GPS Altitude"(pkgpayload[2])
            //"GPS # satellites"(pkgpayload[3])
            break;
        case 0x31B:
            //"GPS error"(pkgpayload[0])
            //"GPS Lat speed"(pkgpayload[1])
            //"GPS Long speed"(pkgpayload[2])
            //"Digital Inputs Raw"(pkgpayload[3])
            break;
        case 0x31C:
            //"Internal Lambda 1"(pkgpayload[0]/1000)
            //"Internal Lambda 2"(pkgpayload[1]/1000)
            //"Internal Lambda 3"(pkgpayload[2]/1000)
            //"Internal Lambda 4"(pkgpayload[3]/1000)
            break;
        case 0x31D:
            //"Internal EGT 1"(pkgpayload[0]/10)
            //"Internal EGT 2"(pkgpayload[1]/10)
            //"Internal EGT 3"(pkgpayload[2]/10)
            //"Internal EGT 4"(pkgpayload[3]/10)
            break;
        case 0x31E:
            //"Internal EGT 5"(pkgpayload[0]/10)
            //"Internal EGT 6"(pkgpayload[1]/10)
            //"Internal EGT 7"(pkgpayload[2]/10)
            //"Internal EGT 8"(pkgpayload[3]/10)
            break;
        case 0x31F:
            //"Internal EGT 9"(pkgpayload[0]/10)
            //"Internal EGT 10"(pkgpayload[1]/10)
            //"Internal EGT 11"(pkgpayload[2]/10)
            //"Internal EGT 12"(pkgpayload[3]/10)
            break;
        case 0x320:
            //"Internal EGT 13"(pkgpayload[0]/10)
            //"Internal EGT 14"(pkgpayload[1]/10)
            //"Internal EGT 15"(pkgpayload[2]/10)
            //"Internal EGT 16"(pkgpayload[3]/10)
            break;
        case 0x321:
            //"Knock cyl 1"(pkgpayload[0]/1000)
            //"Knock cyl 2"(pkgpayload[1]/1000)
            //"Knock cyl 3"(pkgpayload[2]/1000)
            //"Knock cyl 4"(pkgpayload[3]/1000)
            break;
        case 0x322:
            //"Knock cyl 5"(pkgpayload[0]/1000)
            //"Knock cyl 6"(pkgpayload[1]/1000)
            //"Knock cyl 7"(pkgpayload[2]/1000)
            //"Knock cyl 8"(pkgpayload[3]/1000)
            break;
        case 0x323:
            //"Knock cyl 9"(pkgpayload[0]/1000)
            //"Knock cyl 10"(pkgpayload[1]/1000)
            //"Knock cyl 11"(pkgpayload[2]/1000)
            //"Knock cyl 12"(pkgpayload[3]/1000)
            break;
        case 0x324:
            //"Knock cyl 13"(pkgpayload[0]/1000)
            //"Knock cyl 14"(pkgpayload[1]/1000)
            //"Knock cyl 15"(pkgpayload[2]/1000)
            //"Knock cyl 16"(pkgpayload[3]/1000)
            break;
        case 0x325:
            //"RPM rate"(pkgpayload[0])
            //"DBW1 TPS 1"(pkgpayload[1]/1000)
            //"DBW1 TPS 2"(pkgpayload[2]/1000)
            //"DBW2 TPS 1"(pkgpayload[3]/1000)
            break;
        case 0x326:
            //"DBW2 TPS 2"(pkgpayload[0]/1000)
            //"DBW3 TPS 1"(pkgpayload[1]/1000)
            //"DBW3 TPS 2"(pkgpayload[2]/1000)
            //"DBW4 TPS 1"(pkgpayload[3]/1000)
            break;
        case 0x327:
            //"DBW4 TPS 2"(pkgpayload[0]/1000)
            //"CAS1 Voltage"(pkgpayload[1]/1000)
            //"CAS2 Voltage"(pkgpayload[2]/1000)
            //"CAS3 Voltage"(pkgpayload[3]/1000)
            break;
        case 0x328:
            //"CAS4 Voltage"(pkgpayload[0]/1000)
            //"CAS5 Voltage"(pkgpayload[1]/1000)
            //"CAS1 peak V"(pkgpayload[2]/1000)
            //"CAS2 peak V"(pkgpayload[3]/1000)
            break;
        case 0x329:
            //"CAS3 peak V"(pkgpayload[0]/1000)
            //"CAS4 peak V"(pkgpayload[1]/1000)
            //"CAS5 peak V"(pkgpayload[2]/1000)
            //"Current engine angle"(pkgpayload[3]/10)
            break;
        case 0x32A:
            //"Flags3"(pkgpayload[0])
            //"Knock pos index"(pkgpayload[1])
            //"Knock V (raw)"(pkgpayload[2]/1000)
            //"Knock V (filt)"(pkgpayload[3]/1000)
            break;
        case 0x32B:
            //"Mic V"(pkgpayload[0]/1000)
            //"Int IMAP V (inst)"(pkgpayload[1]/1000)
            //"Int EMAPV (inst)"(pkgpayload[2]/1000)
            //"Ext IMAP V (inst)"(pkgpayload[3]/1000)
            break;
        case 0x32C:
            //"Ext EMAP V (inst)"(pkgpayload[0]/1000)
            //"CPU temp"(pkgpayload[1]/10)
            //"Int 1.24V ref V"(pkgpayload[2]/1000)
            //"# samples (int IMAP)"(pkgpayload[3])
            break;
        case 0x32D:
            //"# samples (int EMAP)"(pkgpayload[0])
            //"# samples (ext IMAP)"(pkgpayload[1])
            //"# samples (ext EMAP)"(pkgpayload[2])
            //"Resistance (ECT)"(pkgpayload[3]/1000)
            break;
        case 0x32E:
            //"Resistance (MAT)"(pkgpayload[0]/1000)
            //"Resistance (OilT)"(pkgpayload[1]/1000)
            //"Resistance (FuelT)"(pkgpayload[2]/1000)
            //"Init status"(pkgpayload[3])
            break;
        case 0x32F:
            //"Low level inps"(pkgpayload[0])
            //"Knock ampl (raw)"(pkgpayload[1]/1000)
            //"Knock ampl (filt)"(pkgpayload[2]/1000)
            //"Interpol engine angle"(pkgpayload[3]/10)
            break;
        case 0x330:
            //"Comms FB Mod 0"(pkgpayload[0])
            //"CAS4 period"(pkgpayload[1]/0.1)
            //"CAS4 frequency"(pkgpayload[2]/10)
            //"CAS5 period"(pkgpayload[3]/0.1)
            break;
        case 0x331:
            //"CAS5 frequency"(pkgpayload[0]/10)
            //"Low lev RT Mini inps"(pkgpayload[1])
            //"RT Flex input period"(pkgpayload[2]/0.1)
            //"RT Flex low time"(pkgpayload[3]/0.1)
            break;
        case 0x332:
            //"RT Flex frequency"(pkgpayload[0]/10)
            //"DBW current (A) 1"(pkgpayload[1]/1000)
            //"DBW current (A) 2"(pkgpayload[2]/1000)
            //"DBW current (A) 3"(pkgpayload[3]/1000)
            break;
        case 0x333:
            //"DBW current (A) 4"(pkgpayload[0]/1000)
            //"Comms FB Mini ana 1&2"(pkgpayload[1])
            //"Comms FB Mini ana 3&4"(pkgpayload[2])
            //"Crank period (low)"(pkgpayload[3])
            break;
        case 0x334:
            //"Crank period (high)"(pkgpayload[0])
            //"Trigger error angle"(pkgpayload[1]/10)
            //"Trigger error count"(pkgpayload[2])
            //"CAS2 period"(pkgpayload[3]/0.1)
            break;
        case 0x335:
            //"CAS2 frequency"(pkgpayload[0]/10)
            //"Low level out (M1200)"(pkgpayload[1])
            //"Async vol calc (µL)"(pkgpayload[2]/10)
            //"Async dur calc (ms)"(pkgpayload[3]/1000)
            break;
        case 0x336:
            //"Output 1 error ctr"(pkgpayload[0])
            //"var217"(pkgpayload[1])
            //"var218"(pkgpayload[2])
            //"var219"(pkgpayload[3])
            break;
        case 0x337:
            //"var220"(pkgpayload[0])
            //"var221"(pkgpayload[1])
            //"var222"(pkgpayload[2])
            //"var223"(pkgpayload[3])
            break;
        case 0x338:
            //"var224"(pkgpayload[0])
            //"var225"(pkgpayload[1])
            //"var226"(pkgpayload[2])
            //"var227"(pkgpayload[3])
            break;
        case 0x339:
            //"var228"(pkgpayload[0])
            //"var229"(pkgpayload[1])
            //"var230"(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x33A:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x33B:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x33C:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x33D:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x33E:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x33F:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x340:
            //"Serial Lambda 1"(pkgpayload[0]/1000)
            //"Serial Lambda 2"(pkgpayload[1]/1000)
            //"Serial Lambda 3"(pkgpayload[2]/1000)
            //"Serial Lambda 4"(pkgpayload[3]/1000)
            break;
        case 0x341:
            //"Serial Lambda 5"(pkgpayload[0]/1000)
            //"Serial Lambda 6"(pkgpayload[1]/1000)
            //"Serial Lambda 7"(pkgpayload[2]/1000)
            //"Serial Lambda 8"(pkgpayload[3]/1000)
            break;
        case 0x342:
            //"Serial Lambda 9"(pkgpayload[0]/1000)
            //"Serial Lambda 10"(pkgpayload[1]/1000)
            //"Serial Lambda 11"(pkgpayload[2]/1000)
            //"Serial Lambda 12"(pkgpayload[3]/1000)
            break;
        case 0x343:
            //"Serial Lambda 13"(pkgpayload[0]/1000)
            //"Serial Lambda 14"(pkgpayload[1]/1000)
            //"Serial Lambda 15"(pkgpayload[2]/1000)
            //"Serial Lambda 16"(pkgpayload[3]/1000)
            break;
        case 0x344:
            //"Serial EGT 1"(pkgpayload[0])
            //"Serial EGT 2"(pkgpayload[1])
            //"Serial EGT 3"(pkgpayload[2])
            //"Serial EGT 4"(pkgpayload[3])
            break;
        case 0x345:
            //"Serial EGT 5"(pkgpayload[0])
            //"Serial EGT 6"(pkgpayload[1])
            //"Serial EGT 7"(pkgpayload[2])
            //"Serial EGT 8"(pkgpayload[3])
            break;
        case 0x346:
            //"Serial EGT 9"(pkgpayload[0])
            //"Serial EGT 10"(pkgpayload[1])
            //"Serial EGT 11"(pkgpayload[2])
            //"Serial EGT 12"(pkgpayload[3])
            break;
        case 0x347:
            //"Serial EGT 13"(pkgpayload[0])
            //"Serial EGT 14"(pkgpayload[1])
            //"Serial EGT 15"(pkgpayload[2])
            //"Serial EGT 16"(pkgpayload[3])
            break;
        case 0x348:
            //"Serial Analogue V 1"(pkgpayload[0])
            //"Serial Analogue V 2"(pkgpayload[1])
            //"Serial Analogue V 3"(pkgpayload[2])
            //"Serial Analogue V 4"(pkgpayload[3])
            break;
        case 0x349:
            //"Serial Analogue V 5"(pkgpayload[0])
            //"Serial Analogue V 6"(pkgpayload[1])
            //"Serial Analogue V 7"(pkgpayload[2])
            //"Serial Analogue V 8"(pkgpayload[3])
            break;
        case 0x34A:
            //"Serial Analogue V 9"(pkgpayload[0])
            //"Serial Analogue V 10"(pkgpayload[1])
            //"Serial Analogue V 11"(pkgpayload[2])
            //"Serial Analogue V 12"(pkgpayload[3])
            break;
        case 0x34B:
            //"Serial Analogue V 13"(pkgpayload[0])
            //"Serial Analogue V 14"(pkgpayload[1])
            //"Serial Analogue V 15"(pkgpayload[2])
            //"Serial Analogue V 16"(pkgpayload[3])
            break;
        case 0x34C:
            //"Module 0 ID"(pkgpayload[0])
            //"Module 1 ID"(pkgpayload[1])
            //"Module 2 ID"(pkgpayload[2])
            //"Module 3 ID"(pkgpayload[3])
            break;
        case 0x34D:
            //"Module 4 ID"(pkgpayload[0])
            //"Module 5 ID"(pkgpayload[1])
            //"Module 6 ID"(pkgpayload[2])
            //"Module 7 ID"(pkgpayload[3])
            break;
        case 0x34E:
            //"Vehicle board ID"(pkgpayload[0])
            //"Ethanol % (ECF gauge)"(pkgpayload[1]/10)
            //"Fuel temp (ECF gauge)"(pkgpayload[2]/10)
            //"Fuel press(ECF gauge)"(pkgpayload[3]/10)
            break;
        case 0x34F:
            //"Analogue lambda O2 1"(pkgpayload[0]/1000)
            //"Analogue lambda O2 2"(pkgpayload[1]/1000)
            //"Turbine speed 1 kRPM"(pkgpayload[2]/100)
            //"Turbine speed 2 kRPM"(pkgpayload[3]/100)
            break;
        case 0x350:
            //"CAN Lambda 1"(pkgpayload[0]/1000)
            //"CAN Lambda 2"(pkgpayload[1]/1000)
            //"CAN Lambda 3"(pkgpayload[2]/1000)
            //"CAN Lambda 4"(pkgpayload[3]/1000)
            break;
        case 0x351:
            //"CAN Lambda 5"(pkgpayload[0]/1000)
            //"CAN Lambda 6"(pkgpayload[1]/1000)
            //"CAN Lambda 7"(pkgpayload[2]/1000)
            //"CAN Lambda 8"(pkgpayload[3]/1000)
            break;
        case 0x352:
            //"CAN Lambda 9"(pkgpayload[0]/1000)
            //"CAN Lambda 10"(pkgpayload[1]/1000)
            //"CAN Lambda 11"(pkgpayload[2]/1000)
            //"CAN Lambda 12"(pkgpayload[3]/1000)
            break;
        case 0x353:
            //"CAN Lambda 13"(pkgpayload[0]/1000)
            //"CAN Lambda 14"(pkgpayload[1]/1000)
            //"CAN Lambda 15"(pkgpayload[2]/1000)
            //"CAN Lambda 16"(pkgpayload[3]/1000)
            break;
        case 0x354:
            //"CAN EGT 1"(pkgpayload[0])
            //"CAN EGT 2"(pkgpayload[1])
            //"CAN EGT 3"(pkgpayload[2])
            //"CAN EGT 4"(pkgpayload[3])
            break;
        case 0x355:
            //"CAN EGT 5"(pkgpayload[0])
            //"CAN EGT 6"(pkgpayload[1])
            //"CAN EGT 7"(pkgpayload[2])
            //"CAN EGT 8"(pkgpayload[3])
            break;
        case 0x356:
            //"CAN EGT 9"(pkgpayload[0])
            //"CAN EGT 10"(pkgpayload[1])
            //"CAN EGT 11"(pkgpayload[2])
            //"CAN EGT 12"(pkgpayload[3])
            break;
        case 0x357:
            //"CAN EGT 13"(pkgpayload[0])
            //"CAN EGT 14"(pkgpayload[1])
            //"CAN EGT 15"(pkgpayload[2])
            //"CAN EGT 16"(pkgpayload[3])
            break;
        case 0x358:
            //"CAN Analogue V 1"(pkgpayload[0])
            //"CAN Analogue V 2"(pkgpayload[1])
            //"CAN Analogue V 3"(pkgpayload[2])
            //"CAN Analogue V 4"(pkgpayload[3])
            break;
        case 0x359:
            //"CAN Analogue V 5"(pkgpayload[0])
            //"CAN Analogue V 6"(pkgpayload[1])
            //"CAN Analogue V 7"(pkgpayload[2])
            //"CAN Analogue V 8"(pkgpayload[3])
            break;
        case 0x35A:
            //"CAN Analogue V 9"(pkgpayload[0])
            //"CAN Analogue V 10"(pkgpayload[1])
            //"CAN Analogue V 11"(pkgpayload[2])
            //"CAN Analogue V 12"(pkgpayload[3])
            break;
        case 0x35B:
            //"CAN Analogue V 13"(pkgpayload[0])
            //"CAN Analogue V 14"(pkgpayload[1])
            //"CAN Analogue V 15"(pkgpayload[2])
            //"CAN Analogue V 16"(pkgpayload[3])
            break;
        case 0x35C:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x35D:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x35E:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x35F:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x360:
            //"IMAP int"(pkgpayload[0]/10)
            //"EMAP int"(pkgpayload[1]/10)
            //"IMAP ext"(pkgpayload[2]/10)
            //"EMAP ext"(pkgpayload[3]/10)
            break;
        case 0x361:
            //qDebug() << "IMAP :" << pkgpayload[0]/10;
            m_dashboard->setMAP(pkgpayload[0]/10);
            m_dashboard->setpim((pkgpayload[0]/10));
            //qDebug() << (pkgpayload[0]/10);
            //qDebug() << "IMAP2 :" << pkgpayload[1]/10;
            //qDebug() << "EMAP :" << pkgpayload[2]/10;
            //qDebug() << "EMAP2  :" << pkgpayload[3]/10;
            break;
        case 0x362:
            //"Pressure ratio"(pkgpayload[0]/10)
            //"Pressure ratio 2"(pkgpayload[1]/10)
            //"Pedal 1 / TPS1"(pkgpayload[2]/100)
            //"Pedal 2 / TPS2"(pkgpayload[3]/100)
            break;
        case 0x363:
            //"TPS overall"(pkgpayload[0]/100)
            //"TPS 1 (DBW)"(pkgpayload[1]/100)
            //"TPS 2 (DBW)"(pkgpayload[2]/100)
            //"TPS 3 (DBW)"(pkgpayload[3]/100)
            break;

        case 0x364:
            //"TPS 4 (DBW)"(pkgpayload[0]/100)
            m_dashboard->setLAMBDA(pkgpayload[1]/1000.00);
            //"Lambda 1"(pkgpayload[1]/100)
            //"Lambda 1)"(pkgpayload[2]/100)
            //"ECT"(pkgpayload[3]/100)
            break;


        case 0x365:
            //qDebug() << "MAT :" << pkgpayload[0]/10;
            m_dashboard->setIntaketemp(pkgpayload[0]/10);
            //qDebug() << "Oil T :" << pkgpayload[1]/10;
            m_dashboard->setFueltemp(pkgpayload[2]/10);
            //qDebug() << "Oil P  :" << pkgpayload[3]/10;
            break;


        case 0x366:
            //qDebug() << "Diff Fuel P" << pkgpayload[0]/10;
            //qDebug() << "Servo pos:" << pkgpayload[1]/10;
            //qDebug() << "Fuel T :" << pkgpayload[2]/10;
            //qDebug() << "0-5V Ext 1 :" << pkgpayload[3]/10;
            break;

        case 0x367:
            //qDebug() << "0-5V Ext 2 :" << pkgpayload[0]/10;
            //qDebug() << "Sens GND V (GND off):" << pkgpayload[1]/1000;
            //qDebug() << "Ethanol Content :" << pkgpayload[2]/10;
            m_dashboard->setSpeed(pkgpayload[3]/10);
            break;

        case 0x368:
            //qDebug() << "Gear number :" << pkgpayload[0];
            //qDebug() << "Driven speed:" << pkgpayload[1]/10;
            //qDebug() << "Ground speed :" << pkgpayload[2]/10;
            //qDebug() << "Spd diff (drive-gnd)  :" << pkgpayload[3]/10;
            break;
        case 0x369:
            //"Spd diff drive (L-R)"(pkgpayload[0]/10)
            //"Spd diff gnd L-R)"(pkgpayload[1]/10)
            //"Inlet VVT1 pos"(pkgpayload[2]/10)
            //"Inlet VVT2 pos"(pkgpayload[3]/10)
            break;
        case 0x36A:
            //"Exhaust VVT1 pos"(pkgpayload[0]/10)
            //"Exhaust VVT2 pos"(pkgpayload[1]/10)
            //"Position X"(pkgpayload[2]/10)
            //"Position Y"(pkgpayload[3]/10)
            break;
        case 0x36B:
            //"Position X (abs low)"(pkgpayload[0]/10)
            //"Position X (abs high)"(pkgpayload[1]/10)
            //"Position Y (abs low)"(pkgpayload[2]/10)
            //"Position Y (abs high)"(pkgpayload[3]/10)
            break;
        case 0x36C:
            //"Dig inp processed low"(pkgpayload[0])
            //"Dig inp processed hi"(pkgpayload[1])
            //"Flags low"(pkgpayload[2])
            //"Flags high"(pkgpayload[3])
            break;
        case 0x36D:
            //"Knock bkg level"(pkgpayload[0]/1000)
            //"KnockMax(bkg removed)"(pkgpayload[1]/1000)
            //"Baro pressure"(pkgpayload[2]/10)
            //"Temperature bias"(pkgpayload[3])
            break;
        case 0x36E:
            //"TPS target (DBW)"(pkgpayload[0]/100)
            //"Throttle duty 1 (DBW)"(pkgpayload[1]/100)
            //"Throttle duty 2 (DBW)"(pkgpayload[2]/100)
            //"Throttle duty 3 (DBW)"(pkgpayload[3]/100)
            break;
        case 0x36F:
            //"Throttle duty 4 (DBW)"(pkgpayload[0]/100)
            //"CAS 1 V threshold"(pkgpayload[1]/1000)
            //"CAS 2 V threshold"(pkgpayload[2]/1000)
            //"CAS 3 V threshold"(pkgpayload[3]/1000)
            break;
        case 0x370:
            //"CAS 4 V threshold"(pkgpayload[0]/1000)
            //"CAS 5 V threshold"(pkgpayload[1]/1000)
            //"VSS V threshold"(pkgpayload[2]/1000)
            //"CAS 1 filter (ms)"(pkgpayload[3]/1000)
            break;
        case 0x371:
            //"CAS 2 filter (ms)"(pkgpayload[0]/1000)
            //"CAS 3 filter (ms)"(pkgpayload[1]/1000)
            //"CAS 4 filter (ms)"(pkgpayload[2]/1000)
            //"CAS 5 filter (ms)"(pkgpayload[3]/1000)
            break;
        case 0x372:
            //"VSS filter (ms)"(pkgpayload[0]/1000)
            //"Digital In (filt)"(pkgpayload[1])
            //"Ethanol % (for calc)"(pkgpayload[2]/10)
            //"Lambda Error 1"(pkgpayload[3]/1000)
            break;
        case 0x373:
            //"Lambda Error 2"(pkgpayload[0]/1000)
            //"Lambda 1 min"(pkgpayload[1]/1000)
            //"Lambda 1 max"(pkgpayload[2]/1000)
            //"Lambda 2 min"(pkgpayload[3]/1000)
            break;
        case 0x374:
            //"Lambda 2 max"(pkgpayload[0]/1000)
            //"TPS effort due to TC"(pkgpayload[1]/100)
            //"Slip"(pkgpayload[2]/100)
            //"Slip LR Driven"(pkgpayload[3]/100)
            break;
        case 0x375:
            //"Slip LR Ground"(pkgpayload[0]/100)
            //"MGP1"(pkgpayload[1]/10)
            //"MGP2"(pkgpayload[2]/10)
            //"Knock max (inc bkg)"(pkgpayload[3]/1000)
            break;
        case 0x376:
            //"Peak knock retard"(pkgpayload[0]/10)
            //"Pedal pos (DBW)"(pkgpayload[1]/100)
            //"Current Launch Control RPM"(pkgpayload[2])
            //"Displayed RPM"(pkgpayload[3])
            break;
        case 0x377:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x378:
            //"Injector 1 duty"(pkgpayload[0]/100)
            //"Injector 2 duty"(pkgpayload[1]/100)
            //"Injector 3 duty"(pkgpayload[2]/100)
            //"Injector 4 duty"(pkgpayload[3]/100)
            break;
        case 0x379:
            //"Injector 5 duty"(pkgpayload[0]/100)
            //"Injector 6 duty"(pkgpayload[1]/100)
            //"Injector 7 duty"(pkgpayload[2]/100)
            //"Injector 8 duty"(pkgpayload[3]/100)
            break;
        case 0x37A:
            //"Injector 9 duty"(pkgpayload[0]/100)
            //"Injector 10 duty"(pkgpayload[1]/100)
            //"Injector 11 duty"(pkgpayload[2]/100)
            //"Injector 12 duty"(pkgpayload[3]/100)
            break;
        case 0x37B:
            //"Injector 13 duty"(pkgpayload[0]/100)
            //"Injector 14 duty"(pkgpayload[1]/100)
            //"Injector 15 duty"(pkgpayload[2]/100)
            //"Injector 16 duty"(pkgpayload[3]/100)
            break;
        case 0x37C:
            //"Injector 17 duty"(pkgpayload[0]/100)
            //"Injector 18 duty"(pkgpayload[1]/100)
            //"Injector 19 duty"(pkgpayload[2]/100)
            //"Injector 20 duty"(pkgpayload[3]/100)
            break;
        case 0x37D:
            //"Injector 21 duty"(pkgpayload[0]/100)
            //"Injector 22 duty"(pkgpayload[1]/100)
            //"Injector 23 duty"(pkgpayload[2]/100)
            //"Injector 24 duty"(pkgpayload[3]/100)
            break;
        case 0x37E:
            //"Injector 25 duty"(pkgpayload[0]/100)
            //"Injector 26 duty"(pkgpayload[1]/100)
            //"Injector 27 duty"(pkgpayload[2]/100)
            //"Injector 28 duty"(pkgpayload[3]/100)
            break;
        case 0x37F:
            //"Injector 29 duty"(pkgpayload[0]/100)
            //"Injector 30 duty"(pkgpayload[1]/100)
            //"Injector 31 duty"(pkgpayload[2]/100)
            //"Injector 32 duty"(pkgpayload[3]/100)
            break;
        case 0x380:
            //"Load Value 1"(pkgpayload[0]/10)
            //"Load Value 2"(pkgpayload[1]/10)
            //"Calculated VE 1"(pkgpayload[2]/100)
            //"Calculated VE 2"(pkgpayload[3]/100)
            break;
        case 0x381:
            //"Calc Charge temp 1"(pkgpayload[0]/10)
            //"Calc Charge temp 2"(pkgpayload[1]/10)
            //"Stoichiometric ratio"(pkgpayload[2]/1000)
            //"Target Lambda"(pkgpayload[3]/10000)
            m_dashboard->setLAMBDATarget(pkgpayload[3]/1000.00);
            break;
        case 0x382:
            //"Calc fuel mass/cyl 1"(pkgpayload[0]/10)
            //"Calc fuel mass/cyl 2"(pkgpayload[1]/10)
            //"Est fuel film mass 1"(pkgpayload[2]/10)
            //"Est fuel film mass 2"(pkgpayload[3]/10)
            break;
        case 0x383:
            //"Req fuel film mass 1"(pkgpayload[0]/10)
            //"Req fuel film mass 2"(pkgpayload[1]/10)
            //"Fuel to deliver 1"(pkgpayload[2]/10)
            //"Fuel to deliver 2"(pkgpayload[3]/10)
            break;
        case 0x384:
            //"Fuel P used (calc)"(pkgpayload[0]/10)
            //"Fuel Dens used (calc)"(pkgpayload[1]/1000)
            //"Inj flow rate stage 1"(pkgpayload[2])
            //"Inj flow rate stage 2"(pkgpayload[3])
            break;
        case 0x385:
            //"Inj flow rate stage 3"(pkgpayload[0])
            //"Inj flow rate stage 4"(pkgpayload[1])
            //"Inj offset stage 1"(pkgpayload[2]/1000)
            //"Inj offset stage 2"(pkgpayload[3]/1000)
            break;
        case 0x386:
            //"Inj offset stage 3"(pkgpayload[0]/1000)
            //"Inj offset stage 4"(pkgpayload[1]/1000)
            //"Fuel mass cyl 1"(pkgpayload[2]/10)
            //"Fuel mass cyl 2"(pkgpayload[3]/10)
            break;
        case 0x387:
            //"Fuel mass cyl 3"(pkgpayload[0]/10)
            //"Fuel mass cyl 4"(pkgpayload[1]/10)
            //"Fuel mass cyl 5"(pkgpayload[2]/10)
            //"Fuel mass cyl 6"(pkgpayload[3]/10)
            break;
        case 0x388:
            //"Fuel mass cyl 7"(pkgpayload[0]/10)
            //"Fuel mass cyl 8"(pkgpayload[1]/10)
            //"Fuel mass cyl 9"(pkgpayload[2]/10)
            //"Fuel mass cyl 10"(pkgpayload[3]/10)
            break;
        case 0x389:
            //"Fuel mass cyl 11"(pkgpayload[0]/10)
            //"Fuel mass cyl 12"(pkgpayload[1]/10)
            //"Fuel mass cyl 13"(pkgpayload[2]/10)
            //"Fuel mass cyl 14"(pkgpayload[3]/10)
            break;
        case 0x38A:
            //"Fuel mass cyl 15"(pkgpayload[0]/10)
            //"Fuel mass cyl 16"(pkgpayload[1]/10)
            //"Fuel inj dur out 1"(pkgpayload[2]/1000)
            //"Fuel inj dur out 2"(pkgpayload[3]/1000)
            break;
        case 0x38B:
            //"Fuel inj dur out 3"(pkgpayload[0]/1000)
            //"Fuel inj dur out 4"(pkgpayload[1]/1000)
            //"Fuel inj dur out 5"(pkgpayload[2]/1000)
            //"Fuel inj dur out 6"(pkgpayload[3]/1000)
            break;
        case 0x38C:
            //"Fuel inj dur out 7"(pkgpayload[0]/1000)
            //"Fuel inj dur out 8"(pkgpayload[1]/1000)
            //"Fuel inj dur out 9"(pkgpayload[2]/1000)
            //"Fuel inj dur out 10"(pkgpayload[3]/1000)
            break;
        case 0x38D:
            //"Fuel inj dur out 11"(pkgpayload[0]/1000)
            //"Fuel inj dur out 12"(pkgpayload[1]/1000)
            //"Fuel inj dur out 13"(pkgpayload[2]/1000)
            //"Fuel inj dur out 14"(pkgpayload[3]/1000)
            break;
        case 0x38E:
            //"Fuel inj dur out 15"(pkgpayload[0]/1000)
            //"Fuel inj dur out 16"(pkgpayload[1]/1000)
            //"Fuel inj dur out 17"(pkgpayload[2]/1000)
            //"Fuel inj dur out 18"(pkgpayload[3]/1000)
            break;
        case 0x38F:
            //"Fuel inj dur out 19"(pkgpayload[0]/1000)
            //"Fuel inj dur out 20"(pkgpayload[1]/1000)
            //"Fuel inj dur out 21"(pkgpayload[2]/1000)
            //"Fuel inj dur out 22"(pkgpayload[3]/1000)
            break;
        case 0x390:
            //"Fuel inj dur out 23"(pkgpayload[0]/1000)
            //"Fuel inj dur out 24"(pkgpayload[1]/1000)
            //"Fuel inj dur out 25"(pkgpayload[2]/1000)
            //"Fuel inj dur out 26"(pkgpayload[3]/1000)
            break;
        case 0x391:
            //"Fuel inj dur out 27"(pkgpayload[0]/1000)
            //"Fuel inj dur out 28"(pkgpayload[1]/1000)
            //"Fuel inj dur out 29"(pkgpayload[2]/1000)
            //"Fuel inj dur out 30"(pkgpayload[3]/1000)
            break;
        case 0x392:
            //"Fuel inj dur out 31"(pkgpayload[0]/1000)
            //"Fuel inj dur out 32"(pkgpayload[1]/1000)
            //"FuelTrim air/chg temp"(pkgpayload[2]/100)
            //"FuelTrim ECT"(pkgpayload[3]/100)
            break;
        case 0x393:
            //"FuelTrim post crank"(pkgpayload[0]/100)
            //"FuelTrim closed lp 1"(pkgpayload[1]/100)
            //"FuelTrim closed lp 2"(pkgpayload[2]/100)
            //"FuelTrim master"(pkgpayload[3]/100)
            break;
        case 0x394:
            //"FuelTrim user enrich"(pkgpayload[0]/100)
            //"FuelTrim ethanol"(pkgpayload[1]/100)
            //"TPS rate for bank 1"(pkgpayload[2]/10)
            //"TPS rate for bank 2"(pkgpayload[3]/10)
            break;
        case 0x395:
            //"Predicted MAP (TPS1)"(pkgpayload[0]/10)
            //"Predicted MAP (TPS2)"(pkgpayload[1]/10)
            //"Predicted MAP active"(pkgpayload[2])
            //"Calc fuel film %"(pkgpayload[3]/10)
            break;
        case 0x396:
            //"Calc evap time"(pkgpayload[0]/1000)
            //"Calc enric fuel film"(pkgpayload[1]/10)
            //"Target AFR (real AFR)"(pkgpayload[2]/1000)
            //"Calc air mass bank 1"(pkgpayload[3])
            break;
        case 0x397:
            //"Calc air mass bank 2"(pkgpayload[0])
            //"Total fuel trim 1"(pkgpayload[1]/100)
            //"Total fuel trim 2"(pkgpayload[2]/100)
            //"Heat soak percentage"(pkgpayload[3]/100)
            break;
        case 0x398:
            //"Fuel inj angle 1"(pkgpayload[0]/10)
            //"Fuel inj angle 2"(pkgpayload[1]/10)
            //"Fuel inj angle 3"(pkgpayload[2]/10)
            //"Fuel inj angle 4"(pkgpayload[3]/10)
            break;
        case 0x399:
            //"Fuel inj angle 5"(pkgpayload[0]/10)
            //"Fuel inj angle 6"(pkgpayload[1]/10)
            //"Fuel inj angle 7"(pkgpayload[2]/10)
            //"Fuel inj angle 8"(pkgpayload[3]/10)
            break;
        case 0x39A:
            //"Fuel inj angle 9"(pkgpayload[0]/10)
            //"Fuel inj angle 10"(pkgpayload[1]/10)
            //"Fuel inj angle 11"(pkgpayload[2]/10)
            //"Fuel inj angle 12"(pkgpayload[3]/10)
            break;
        case 0x39B:
            //"Fuel inj angle 13"(pkgpayload[0]/10)
            //"Fuel inj angle 14"(pkgpayload[1]/10)
            //"Fuel inj angle 15"(pkgpayload[2]/10)
            //"Fuel inj angle 16"(pkgpayload[3]/10)
            break;
        case 0x39C:
            //"Fuel inj angle 17"(pkgpayload[0]/10)
            //"Fuel inj angle 18"(pkgpayload[1]/10)
            //"Fuel inj angle 19"(pkgpayload[2]/10)
            //"Fuel inj angle 20"(pkgpayload[3]/10)
            break;
        case 0x39D://"Fuel inj angle 21"(pkgpayload[0]/10)
            //"Fuel inj angle 22"(pkgpayload[1]/10)
            //"Fuel inj angle 23"(pkgpayload[2]/10)
            //"Fuel inj angle 24"(pkgpayload[3]/10)
            break;
        case 0x39E://"Fuel inj angle 25"(pkgpayload[0]/10)
            //"Fuel inj angle 26"(pkgpayload[1]/10)
            //"Fuel inj angle 27"(pkgpayload[2]/10)
            //"Fuel inj angle 28"(pkgpayload[3]/10)
            break;
        case 0x39F:
            //"Fuel inj angle 29"(pkgpayload[0]/10)
            //"Fuel inj angle 30"(pkgpayload[1]/10)
            //"Fuel inj angle 31"(pkgpayload[2]/10)
            //"Fuel inj angle 32"(pkgpayload[3]/10)
            break;
        case 0x3A0:
            //"Ign map raw value"(pkgpayload[0]/10)
            //"Ign map ethanol trim"(pkgpayload[1]/10)
            //"FuelTrim antilag"(pkgpayload[2]/100)
            //"IgnTrim ECT"(pkgpayload[3]/10)
            break;
        case 0x3A1:
            //"IgnTrim MAT"(pkgpayload[0]/10)
            //"IgnTrim Knock"(pkgpayload[1]/10)
            //"IgnTrim Idle"(pkgpayload[2]/10)
            //"IgnTrim Traction"(pkgpayload[3]/10)
            break;
        case 0x3A2:
            //"IgnTrim Antilag"(pkgpayload[0]/10)
            //"IgnTrim Master"(pkgpayload[1]/10)
            //"IgnTrim User"(pkgpayload[2]/10)
            //"Spark split"(pkgpayload[3]/10)
            break;
        case 0x3A3:
            m_dashboard->setLeadingign(pkgpayload[0]/10);
            m_dashboard->setTrailingign(pkgpayload[1]/10);
            //"Advance metric (raw)"(pkgpayload[2])
            //"Advance metric (filt)"(pkgpayload[3])
            break;
        case 0x3A4:
            //"Nominal dwell time"(pkgpayload[0]/1000)
            //"Actual dwell time"(pkgpayload[1]/1000)
            //"Time since start"(pkgpayload[2]/100)
            //"Time in enrichment"(pkgpayload[3])
            break;
        case 0x3A5:
            //"Async inj duration"(pkgpayload[0]/1000)
            //"Async inj strobe 1-16"(pkgpayload[1])
            //"Async inj duration 2"(pkgpayload[2]/1000)
            //"Async inj str 1-16 2"(pkgpayload[3])
            break;
        case 0x3A6:
            //"Async inj dur 17-32"(pkgpayload[0]/1000)
            //"Async inj str 17-32"(pkgpayload[1])
            //"Async inj dur 17-32 2"(pkgpayload[2]/1000)
            //"Async inj str 17-32 2"(pkgpayload[3])
            break;
        case 0x3A7:
            //"Fuel temp (for calc)"(pkgpayload[0]/10)
            //"# injector outs used"(pkgpayload[1])
            //"# ignition outs used"(pkgpayload[2])
            //"Main loop speed"(pkgpayload[3])
            break;
        case 0x3A8:
            //"Raw target idle value"(pkgpayload[0])
            //"Target idle (elec)"(pkgpayload[1])
            //"Raw base duty cycle"(pkgpayload[2]/100)
            //"Idle effort (elec)"(pkgpayload[3]/100)
            break;
        case 0x3A9:
            //"Idle effort (altern)"(pkgpayload[0]/100)
            //"Idle effort (psteer)"(pkgpayload[1]/100)
            //"Idle effort (antilag)"(pkgpayload[2]/100)
            //"Idle effort postcrank"(pkgpayload[3]/100)
            break;
        case 0x3AA:
            //"Idle effort closed lp"(pkgpayload[0]/100)
            //"Idle closed lp status"(pkgpayload[1])
            //"Unclipped idle effort"(pkgpayload[2]/100)
            //"Idle effort / duty"(pkgpayload[3]/100)
            break;
        case 0x3AB:
            //"Idle stepper position"(pkgpayload[0])
            //"Target idle RPM"(pkgpayload[1])
            //"Idle effort (open lp)"(pkgpayload[2]/100)
            //"Idle effort (thermo)"(pkgpayload[3]/100)
            break;
        case 0x3AC:
            //"Idle effort (aircon)"(pkgpayload[0]/100)
            //"Target idle (aircon)"(pkgpayload[1])
            //"Idle stepper target"(pkgpayload[2])
            //"Idle Stepper A duty"(pkgpayload[3]/100)
            break;
        case 0x3AD:
            //"Idle Stepper B duty"(pkgpayload[0]/100)
            //"Current gear bit 0"(pkgpayload[1]/100)
            //"Current gear bit 1"(pkgpayload[2]/100)
            //"Current gear bit 2"(pkgpayload[3]/100)
            break;
        case 0x3AE:
            //"Idle effort (cracker)"(pkgpayload[0]/100)
            //"Current N2O Stage"(pkgpayload[1])
            //"Fuel trim for nitrous"(pkgpayload[2]/100)
            //"IgnTrim (nitrous)"(pkgpayload[3]/10)
            break;
        case 0x3AF:
            //"Fuel usage rate"(pkgpayload[0])
            //"Prev gear before shft"(pkgpayload[1])
            //"Measured ign cut dur"(pkgpayload[2])
            //"Idle RPM error"(pkgpayload[3])
            break;
        case 0x3B0:
            //"Cutting conditions"(pkgpayload[0])
            //"Current RPM limit"(pkgpayload[1])
            //"Pitlane RPM limit"(pkgpayload[2])
            //"Pitlane status"(pkgpayload[3])
            break;
        case 0x3B1:
            //"Pwr cut (antilag)"(pkgpayload[0])
            //"Pwr cut (traction)"(pkgpayload[1])
            //"Fuel cut"(pkgpayload[2])
            //"Ignition cut"(pkgpayload[3])
            break;
        case 0x3B2:
            //"Pwr cut (flat shift)"(pkgpayload[0])
            //"Antilag Rolling RPM"(pkgpayload[1])
            //"Pwr cut (launch)"(pkgpayload[2])
            //"Throt limit (antilag)"(pkgpayload[3]/100)
            break;
        case 0x3B3:
            //"Throt limit (trac)"(pkgpayload[0]/100)
            //"Throt limit (fuelcut)"(pkgpayload[1]/100)
            //"Throt limit (igncut)"(pkgpayload[2]/100)
            //"Throt limit (flatshf)"(pkgpayload[3]/100)
            break;
        case 0x3B4:
            //"Throt limit (launch)"(pkgpayload[0]/100)
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x3B5:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x3B6:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x3B7:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x3B8:
            //"Target MAP (from map)"(pkgpayload[0]/10)
            //"Boost limit (ethanol)"(pkgpayload[1]/10)
            //"Boost limit (traction)"(pkgpayload[2]/10)
            //"Boost limit (input)"(pkgpayload[3]/10)
            break;
        case 0x3B9:
            //"Boost limit (gear)"(pkgpayload[0]/10)
            //"Target MAP (final)"(pkgpayload[1]/10)
            //"Open lp WG (limited)"(pkgpayload[2]/100)
            //"Closed lp WG 1 corr"(pkgpayload[3]/100)
            break;
        case 0x3BA:
            //"Unclipped WG value1"(pkgpayload[0]/100)
            //"Wastegate 1 duty"(pkgpayload[1]/100)
            m_dashboard->setBoostDuty(pkgpayload[1]/100);
            //"Boost ctrl status"(pkgpayload[2])
            //"Closed lp WG 2 corr"(pkgpayload[3]/100)
            break;
        case 0x3BB:
            //"Unclipped WG value2"(pkgpayload[0]/100)
            //"Wastegate 2 duty"(pkgpayload[1]/100)
            //"Twin Turbo Pre duty"(pkgpayload[2]/100)
            //"Twin Turbo Ctrl duty"(pkgpayload[3]/100)
            break;
        case 0x3BC:
            //"Purge valve duty"(pkgpayload[0]/100)
            //"Turbo Timer duty"(pkgpayload[1]/100)
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x3BD:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x3BE:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //""(pkgpayload[2])
            //""(pkgpayload[3])
            break;
        case 0x3BF:
            //""(pkgpayload[0])
            //""(pkgpayload[1])
            //"MOP target step (OL)"(pkgpayload[2])
            //"MOP Step number (OL)"(pkgpayload[3])
            break;
        case 0x3C0:
            //"Target intake VVT"(pkgpayload[0]/10)
            //"Target exhaust VVT"(pkgpayload[1]/10)
            //"Intake VVT P gain"(pkgpayload[2]/100)
            //"Intake VVT I gain"(pkgpayload[3]/100)
            break;
        case 0x3C1:
            //"Intake VVT D gain"(pkgpayload[0]/100)
            //"Exhaust VVT P gain"(pkgpayload[1]/100)
            //"Exhaust VVT I gain"(pkgpayload[2]/100)
            //"Exhaust VVT D gain"(pkgpayload[3]/100)
            break;
        case 0x3C2:
            //"Unclipped VVTint1duty"(pkgpayload[0]/100)
            //"Unclipped VVTint2duty"(pkgpayload[1]/100)
            //"Unclipped VVTexh1duty"(pkgpayload[2]/100)
            //"Unclipped VVTexh2duty"(pkgpayload[3]/100)
            break;
        case 0x3C3:
            //"VVT int 1 duty"(pkgpayload[0]/100)
            //"VVT int 2 duty"(pkgpayload[1]/100)
            //"VVT exh 1 duty"(pkgpayload[2]/100)
            //"VVT exh 2 duty"(pkgpayload[3]/100)
            break;
        case 0x3C4:
            //"Status Intake 1"(pkgpayload[0])
            //"Status Intake 2"(pkgpayload[1])
            //"Status Exhaust 1"(pkgpayload[2])
            //"Status Exhaust 2"(pkgpayload[3])
            break;
        case 0x3C5:
            //"MOP pos"(pkgpayload[0]/100)
            //"MOP target"(pkgpayload[1]/100)
            //"MOP Step A duty"(pkgpayload[2]/100)
            //"MOP Step B duty"(pkgpayload[3]/100)
            break;
        case 0x3C6:
            //"TPS output duty cycle"(pkgpayload[0]/100)
            //"Checklight duty cycle"(pkgpayload[1]/100)
            //"Thermofan speed >= 1"(pkgpayload[2]/100)
            //"Thermofan speed >= 2"(pkgpayload[3]/100)
            break;
        case 0x3C7:
            //"Thermofan speed >= 3"(pkgpayload[0]/100)
            //"Air conditioner duty"(pkgpayload[1]/100)
            //"Fuel pump duty cycle"(pkgpayload[2]/100)
            //"Thermofan stage 0-3"(pkgpayload[3])
            break;
        case 0x3C8:
            //"Aux output 1 duty"(pkgpayload[0]/10)
            //"Aux output 2 duty"(pkgpayload[1])
            //"Aux output 3 duty"(pkgpayload[2])
            //"Aux output 4 duty"(pkgpayload[3])
            break;
        case 0x3C9:
            //"Aux output 5 duty"(pkgpayload[0])
            //"Aux output 6 duty"(pkgpayload[1])
            //"Aux output 7 duty"(pkgpayload[2])
            //"Aux output 8 duty"(pkgpayload[3])
            break;
        case 0x3CA:
            //"Aux output 9 duty"(pkgpayload[0])
            //"Aux output 10 duty"(pkgpayload[1])
            //"Aux output 11 duty"(pkgpayload[2])
            //"Aux output 12 duty"(pkgpayload[3])
            break;
        case 0x3CB:
            //"Aux output 13 duty"(pkgpayload[0])
            //"Aux output 14 duty"(pkgpayload[1])
            //"Aux output 15 duty"(pkgpayload[2])
            //"Aux output 16 duty"(pkgpayload[3])
            break;
        case 0x3CC:
            //"Aux output 17 duty"(pkgpayload[0])
            //"Aux output 18 duty"(pkgpayload[1])
            //"Aux output 19 duty"(pkgpayload[2])
            //"Aux output 20 duty"(pkgpayload[3])
            break;
        case 0x3CD:
            //"Aux output 21 duty"(pkgpayload[0])
            //"Aux output 22 duty"(pkgpayload[1])
            //"Aux output 23 duty"(pkgpayload[2])
            //"Aux output 24 duty"(pkgpayload[3])
            break;
        case 0x3CE:
            //"Aux output 25 duty"(pkgpayload[0])
            //"Aux output 26 duty"(pkgpayload[1])
            //"Aux output 27 duty"(pkgpayload[2])
            //"Aux output 28 duty"(pkgpayload[3])
            break;
        case 0x3CF:
            //"Aux output 29 duty"(pkgpayload[0])
            //"Aux output 30 duty"(pkgpayload[1])
            //"Aux output 31 duty"(pkgpayload[2])
            //"Aux output 32 duty"(pkgpayload[3])
            break;
        case 0x3D0:
            //"Aux output 33 duty"(pkgpayload[0])
            //"Aux output 34 duty"(pkgpayload[1])
            //"Aux output 35 duty"(pkgpayload[2])
            //"Aux output 36 duty"(pkgpayload[3])
            break;
        case 0x3D1:
            //"Aux output 37 duty"(pkgpayload[0])
            //"Aux output 38 duty"(pkgpayload[1])
            //"Aux output 39 duty"(pkgpayload[2])
            //"Aux output 40 duty"(pkgpayload[3])
            break;
        case 0x3D2:
            //"Aux output 41 duty"(pkgpayload[0])
            //"Aux output 42 duty"(pkgpayload[1])
            //"Aux output 43 duty"(pkgpayload[2])
            //"Aux output 44 duty"(pkgpayload[3])
            break;
        case 0x3D3:
            //"Aux output 45 duty"(pkgpayload[0])
            //"Aux output 46 duty"(pkgpayload[1])
            //"Aux output 47 duty"(pkgpayload[2])
            //"Aux output 48 duty"(pkgpayload[3])
            break;
        case 0x3D4:
            //"Aux output 49 duty"(pkgpayload[0])
            //"Aux output 50 duty"(pkgpayload[1])
            //"Aux output 51 duty"(pkgpayload[2])
            //"Aux output 52 duty"(pkgpayload[3])
            break;
        case 0x3D5:
            //"Aux output 53 duty"(pkgpayload[0])
            //"Aux output 54 duty"(pkgpayload[1])
            //"Aux output 55 duty"(pkgpayload[2])
            //"Aux output 56 duty"(pkgpayload[3])
            break;
        case 0x3D6:
            //"Aux output 57 duty"(pkgpayload[0])
            //"Aux output 58 duty"(pkgpayload[1])
            //"Aux output 59 duty"(pkgpayload[2])
            //"Aux output 60 duty"(pkgpayload[3])
            break;
        case 0x3D7:
            //"Aux output 61 duty"(pkgpayload[0])
            //"Aux output 62 duty"(pkgpayload[1])
            //"Aux output 63 duty"(pkgpayload[2])
            //"Aux output 64 duty"(pkgpayload[3])
            break;
        case 0x3D8:
            //"Aux output 65 duty"(pkgpayload[0])
            //"Aux output 66 duty"(pkgpayload[1])
            //"Aux output 67 duty"(pkgpayload[2])
            //"Aux output 68 duty"(pkgpayload[3])
            break;
        case 0x3D9:
            //"Aux output 69 duty"(pkgpayload[0])
            //"Aux output 70 duty"(pkgpayload[1])
            //"Aux output 71 duty"(pkgpayload[2])
            //"Aux output 72 duty"(pkgpayload[3])
            break;
        case 0x3DA:
            //"Aux output 73 duty"(pkgpayload[0])
            //"Aux output 74 duty"(pkgpayload[1])
            //"Aux output 75 duty"(pkgpayload[2])
            //"Aux output 76 duty"(pkgpayload[3])
            break;
        case 0x3DB:
            //"Aux output 77 duty"(pkgpayload[0])
            //"Aux output 78 duty"(pkgpayload[1])
            //"Aux output 79 duty"(pkgpayload[2])
            //"Aux output 80 duty"(pkgpayload[3])
            break;
        case 0x3DC:
            //"Aux output 81 duty"(pkgpayload[0])
            //"Aux output 82 duty"(pkgpayload[1])
            //"Aux output 83 duty"(pkgpayload[2])
            //"Aux output 84 duty"(pkgpayload[3])
            break;
        case 0x3DD:
            //"Aux output 85 duty"(pkgpayload[0])
            //"Aux output 86 duty"(pkgpayload[1])
            //"Aux output 87 duty"(pkgpayload[2])
            //"Aux output 88 duty"(pkgpayload[3])
            break;
        case 0x3DE:
            //"Aux output 89 duty"(pkgpayload[0])
            //"Aux output 90 duty"(pkgpayload[1])
            //"Aux output 91 duty"(pkgpayload[2])
            //"Aux output 92 duty"(pkgpayload[3])
            break;
        case 0x3DF:
            //"Aux output 93 duty"(pkgpayload[0])
            //"Aux output 94 duty"(pkgpayload[1])
            //"Aux output 95 duty"(pkgpayload[2])
            //"895"(pkgpayload[3])
            break;
        case 0x3E0:
            //"896"(pkgpayload[0])
            //"897"(pkgpayload[1])
            //"898"(pkgpayload[2])
            //"899"(pkgpayload[3])
            break;
        case 0x3E1:
            //"900"(pkgpayload[0])
            //"901"(pkgpayload[1])
            //"902"(pkgpayload[2])
            //"903"(pkgpayload[3])
            break;
        case 0x3E2:
            //"904"(pkgpayload[0])
            //"905"(pkgpayload[1])
            //"906"(pkgpayload[2])
            //"907"(pkgpayload[3])
            break;
        case 0x3E3:
            //"908"(pkgpayload[0])
            //"909"(pkgpayload[1])
            //"910"(pkgpayload[2])
            //"911"(pkgpayload[3])
            break;
        case 0x3E4:
            //"912"(pkgpayload[0])
            //"913"(pkgpayload[1])
            //"914"(pkgpayload[2])
            //"915"(pkgpayload[3])
            break;
        case 0x3E5:
            //"916"(pkgpayload[0])
            //"917"(pkgpayload[1])
            //"918"(pkgpayload[2])
            //"919"(pkgpayload[3])
            break;
        case 0x3E6:
            //"920"(pkgpayload[0])
            //"921"(pkgpayload[1])
            //"922"(pkgpayload[2])
            //"923"(pkgpayload[3])
            break;
        case 0x3E7:
            //"924"(pkgpayload[0])
            //"925"(pkgpayload[1])
            //"926"(pkgpayload[2])
            //"927"(pkgpayload[3])
            break;
        case 0x3E8:
            //"928"(pkgpayload[0])
            //"929"(pkgpayload[1])
            //"930"(pkgpayload[2])
            //"931"(pkgpayload[3])
            break;
        case 0x3E9:
            //"932"(pkgpayload[0])
            //"933"(pkgpayload[1])
            //"934"(pkgpayload[2])
            //"935"(pkgpayload[3])
            break;
        case 0x3EA:
            //"936"(pkgpayload[0])
            //"937"(pkgpayload[1])
            //"938"(pkgpayload[2])
            //"939"(pkgpayload[3])
            break;
        case 0x3EB:
            //"940"(pkgpayload[0])
            //"941"(pkgpayload[1])
            //"942"(pkgpayload[2])
            //"943"(pkgpayload[3])
            break;
        case 0x3EC:
            //"944"(pkgpayload[0])
            //"945"(pkgpayload[1])
            //"946"(pkgpayload[2])
            //"947"(pkgpayload[3])
            break;
        case 0x3ED:
            //"948"(pkgpayload[0])
            //"949"(pkgpayload[1])
            //"950"(pkgpayload[2])
            //"951"(pkgpayload[3])
            break;
        case 0x3EE:
            //"952"(pkgpayload[0])
            //"953"(pkgpayload[1])
            //"954"(pkgpayload[2])
            //"955"(pkgpayload[3])
            break;
        case 0x3EF:
            //"956"(pkgpayload[0])
            //"957"(pkgpayload[1])
            //"958"(pkgpayload[2])
            //"959"(pkgpayload[3])
            break;
        case 0x3F0:
            //"960"(pkgpayload[0])
            //"961"(pkgpayload[1])
            //"962"(pkgpayload[2])
            //"963"(pkgpayload[3])
            break;
        case 0x3F1:
            //"964"(pkgpayload[0])
            //"965"(pkgpayload[1])
            //"966"(pkgpayload[2])
            //"967"(pkgpayload[3])
            break;
        case 0x3F2:
            //"968"(pkgpayload[0])
            //"969"(pkgpayload[1])
            //"970"(pkgpayload[2])
            //"971"(pkgpayload[3])
            break;
        case 0x3F3:
            //"972"(pkgpayload[0])
            //"973"(pkgpayload[1])
            //"974"(pkgpayload[2])
            //"975"(pkgpayload[3])
            break;
        case 0x3F4:
            //"976"(pkgpayload[0])
            //"977"(pkgpayload[1])
            //"978"(pkgpayload[2])
            //"979"(pkgpayload[3])
            break;
        case 0x3F5:
            //"980"(pkgpayload[0])
            //"981"(pkgpayload[1])
            //"982"(pkgpayload[2])
            //"983"(pkgpayload[3])
            break;
        case 0x3F6:
            //"984"(pkgpayload[0])
            //"985"(pkgpayload[1])
            //"986"(pkgpayload[2])
            //"987"(pkgpayload[3])
            break;
        case 0x3F7:
            //"988"(pkgpayload[0])
            //"989"(pkgpayload[1])
            //"990"(pkgpayload[2])
            //"991"(pkgpayload[3])
            break;
        case 0x3F8:
            //"992"(pkgpayload[0])
            //"993"(pkgpayload[1])
            //"994"(pkgpayload[2])
            //"995"(pkgpayload[3])
            break;
        case 0x3F9:
            //"996"(pkgpayload[0])
            //"997"(pkgpayload[1])
            //"998"(pkgpayload[2])
            //"999"(pkgpayload[3])
            break;
        case 0x3FA:
            //"1000"(pkgpayload[0])
            //"1001"(pkgpayload[1])
            //"1002"(pkgpayload[2])
            //"1003"(pkgpayload[3])
            break;
        case 0x3FB:
            //"1004"(pkgpayload[0])
            //"1005"(pkgpayload[1])
            //"1006"(pkgpayload[2])
            //"1007"(pkgpayload[3])
            break;
        case 0x3FC:
            //"1008"(pkgpayload[0])
            //"1009"(pkgpayload[1])
            //"1010"(pkgpayload[2])
            //"1011"(pkgpayload[3])
            break;
        case 0x3FD:
            //"1012"(pkgpayload[0])
            //"1013"(pkgpayload[1])
            //"1014"(pkgpayload[2])
            //"1015"(pkgpayload[3])
            break;
        case 0x3FE:
            //"1016"(pkgpayload[0])
            //"1017"(pkgpayload[1])
            //"1018"(pkgpayload[2])
            //"1019"(pkgpayload[3])
            break;
        case 0x3FF:
            //"1020"(pkgpayload[0])
            //"1021"(pkgpayload[1])
            //"1022"(pkgpayload[2])
            //"1023"(pkgpayload[3])
            break;
        }
    }
}

