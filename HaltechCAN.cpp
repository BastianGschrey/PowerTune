/*
 * Copyright (C) 2018 Markus Ippy, Bastian Gschrey,
 * use this program at your own risk.

  \file HaltechCAN.cpp
  \brief request and receive messages from Haltech via CAN Haltech CAN Protocol V2
  \author Markus Ippy
 */

#include "HaltechCAN.h"
#include "dashboard.h"
#include <QtEndian>
#include <QDebug>

HaltechCAN::HaltechCAN(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)

{

}
HaltechCAN::HaltechCAN(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}

HaltechCAN::~HaltechCAN()
{
}

void HaltechCAN::openCAN()
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
            connect(m_canDevice, &QCanBusDevice::framesReceived, this, &HaltechCAN::readyToRead);
        }

    }
}
void HaltechCAN::closeConnection()
{
    disconnect(m_canDevice,SIGNAL(framesReceived()),this,SLOT(readyToRead()));
    if (m_canDevice)
    m_canDevice->disconnectDevice();


}
void HaltechCAN::readyToRead()
{
    if (!m_canDevice)
        return;

    while (m_canDevice->framesAvailable()) {
        const QCanBusFrame frame = m_canDevice->readFrame();
// Just for testing  start
        QString view;
        if (frame.frameType() == QCanBusFrame::ErrorFrame)
            view = m_canDevice->interpretErrorFrame(frame);
        else
            view = frame.toString();
/*
        const QString time = QString::fromLatin1("%1.%2  ")
                .arg(frame.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
                .arg(frame.timeStamp().microSeconds() / 100, 4, 10, QLatin1Char('0'));
// Just for testing  end

//        qDebug() << time << view;
*/
// This section decodes the recevied Payload accordung to the frame ID

       QByteArray splitpayload = frame.payload();
        payload* info=reinterpret_cast<payload*>(splitpayload.data());
        pkgpayload[0] = qFromBigEndian(info->CH1);
        pkgpayload[1] = qFromBigEndian(info->CH2);
        pkgpayload[2] = qFromBigEndian(info->CH3);
        pkgpayload[3] = qFromBigEndian(info->CH4);

        switch(frame.frameId()) {

        case 0x360:
             m_dashboard->setrpm(pkgpayload[0]);
             m_dashboard->setMAP(pkgpayload[1]*0.1);
             m_dashboard->setTPS(pkgpayload[2]*0.1);
             m_dashboard->setcoolantpress(pkgpayload[3]*0.1);
            break;
        case 0x361:
             m_dashboard->setFuelPress(pkgpayload[0]*0.1);
             m_dashboard->setoilpres(pkgpayload[1]*0.1);
             m_dashboard->setaccelpedpos(pkgpayload[2]*0.1);
             m_dashboard->setwastegatepress(pkgpayload[3]*0.1);
            break;
        case 0x362:
            m_dashboard->setInj1(pkgpayload[0]*0.1);
            m_dashboard->setInj2(pkgpayload[1]*0.1);
            m_dashboard->setLeadingign(pkgpayload[2]*0.1);
            m_dashboard->setTrailingign(pkgpayload[3]*0.1);
            break;
        case 0x363:
            m_dashboard->setwheelslip(pkgpayload[0]*0.1);
            m_dashboard->setwheeldiff(pkgpayload[1]*0.1);
            //Engine Acceleration(pkgpayload[2]); // rate of RPM rise per second
            //Manifold Pressure2(pkgpayload[3]*0.1); //still need to implement this datasource
            break;
        case 0x368:
            m_dashboard->setLAMBDA(pkgpayload[0]*0.001);
            m_dashboard->setlambda2(pkgpayload[1]*0.001);
            m_dashboard->setlambda3(pkgpayload[2]*0.001);
            m_dashboard->setlambda4(pkgpayload[3]*0.001);
            break;
        case 0x369:
            m_dashboard->setmissccount(pkgpayload[0]);
            m_dashboard->settriggerccounter(pkgpayload[1]);
            m_dashboard->sethomeccounter(pkgpayload[2]);
            m_dashboard->settriggersrsinceasthome(pkgpayload[3]);
            break;
        case 0x36A:
            m_dashboard->setknocklevlogged1(pkgpayload[0]);
            m_dashboard->setknocklevlogged2(pkgpayload[1]);
            m_dashboard->setknockretardbank1(pkgpayload[2]*0.1);
            m_dashboard->setknockretardbank2(pkgpayload[3]*0.1);
            break;
        case 0x36B:
            m_dashboard->setbrakepress(pkgpayload[0]);
            m_dashboard->setnospress(pkgpayload[1]);
            m_dashboard->setturborpm(pkgpayload[2]);
            //G-Sensor (pkgpayload[3]);
            break;
        case 0x36C:
            m_dashboard->setwheelspdftleft(pkgpayload[0]*0.1);
            m_dashboard->setwheelspdftright(pkgpayload[1]*0.1);
            //Wheel speed RL(pkgpayload[2]*0.1);
            //Wheel speed RR(pkgpayload[3]*0.1);
            break;
        case 0x36D:
            m_dashboard->setSVSS(pkgpayload[0]*0.1); //wheel speed front
            m_dashboard->setMVSS(pkgpayload[1]*0.1);//wheel speed rear
            m_dashboard->setexcamangle1(pkgpayload[2]*0.1);
            m_dashboard->setexcamangle2(pkgpayload[3]*0.1);
            break;
        case 0x36E:
            m_dashboard->setfuelcutperc(pkgpayload[0]*0.1);
            m_dashboard->setlaunchctrolignretard(pkgpayload[1]*0.1);
            m_dashboard->setlaunchcontolfuelenrich(pkgpayload[2]*0.1);
            break;
        case 0x36F:
            m_dashboard->setboostcontrol(pkgpayload[1]*0.01);
            m_dashboard->settimeddutyout1(pkgpayload[2]*0.1);
            m_dashboard->settimeddutyout2(pkgpayload[3]*0.1);
            break;
        case 0x370:
            m_dashboard->setSpeed(pkgpayload[0]*0.1);
            m_dashboard->setGear(pkgpayload[1]);
            m_dashboard->setincamangle1(pkgpayload[2]*0.1);
            m_dashboard->setincamangle2(pkgpayload[3]*0.1);
            break;
        case 0x371:
            m_dashboard->setfuelflow(pkgpayload[0]);
            m_dashboard->setfuelflowret(pkgpayload[1]);
            m_dashboard->setfuelflowdiff(pkgpayload[2]);
            break;
        case 0x372:
            m_dashboard->setBatteryV(pkgpayload[0]*0.1);
            m_dashboard->setairtempensor2((pkgpayload[1]*0.1)-273.15);
            m_dashboard->settargetbstlelkpa(pkgpayload[2]*0.1);
            m_dashboard->setambipress(pkgpayload[3]*0.1);
            break;
        case 0x373:
            m_dashboard->setegt1(pkgpayload[0]*0.1);
            m_dashboard->setegt2(pkgpayload[1]*0.1);
            m_dashboard->setegt3(pkgpayload[2]*0.1);
            m_dashboard->setegt4(pkgpayload[3]*0.1);
            break;
        case 0x374:
            m_dashboard->setegt5(pkgpayload[0]*0.1);
            m_dashboard->setegt6(pkgpayload[1]*0.1);
            m_dashboard->setegt7(pkgpayload[2]*0.1);
            m_dashboard->setegt8(pkgpayload[3]*0.1);
            break;
        case 0x375:
            m_dashboard->setegt9(pkgpayload[0]*0.1);
            m_dashboard->setegt10(pkgpayload[1]*0.1);
            m_dashboard->setegt11(pkgpayload[2]*0.1);
            m_dashboard->setegt12(pkgpayload[3]*0.1);
            break;
        case 0x3E0:
            m_dashboard->setWatertemp((pkgpayload[0]*0.1)-273.15);
            m_dashboard->setIntaketemp((pkgpayload[1]*0.1)-273.15);
            m_dashboard->setFueltemp((pkgpayload[2]*0.1)-273.15);
            m_dashboard->setoiltemp((pkgpayload[3]*0.1)-273.15);
            break;
        case 0x3E1:
            m_dashboard->settransoiltemp((pkgpayload[0]*0.1)-273.15);
            m_dashboard->setdiffoiltemp((pkgpayload[1]*0.1)-273.15);
            m_dashboard->setfuelcomposition(pkgpayload[2]*0.1);
            break;
        case 0x3E2:
            m_dashboard->setfuelconsrate(pkgpayload[1]*0.1);
            m_dashboard->setavfueleconomy(pkgpayload[2]*0.1);
            break;
        case 0x3E3:
            m_dashboard->setfueltrimshorttbank1(pkgpayload[0]*0.1);
            m_dashboard->setfueltrimshorttbank2(pkgpayload[1]*0.1);
            m_dashboard->setfueltrimlongtbank1(pkgpayload[2]*0.1);
            m_dashboard->setfueltrimlongtbank2(pkgpayload[3]*0.1);
            break;
        case 0x3E4:

            //Bit Flags ( too lazy to do that now )
            //(pkgpayload[0]*0.1);
            //(pkgpayload[1]*0.1);
            //(pkgpayload[2]*0.1);
            //(pkgpayload[3]*0.1);
            break;
        }
    }
}

