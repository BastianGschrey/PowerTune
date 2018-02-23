/*
 * Copyright (C) 2018 Markus Ippy, Bastian Gschrey,
 * use this program at your own risk.

  \file HaltechCAN.cpp
  \brief request and receive messages from Haltech via CAN Haltech CAN Protocol V2
  \author Markus Ippy
 */

#include "HaltechCAN.h"
#include "dashboard.h"
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
    //Check if the plugin is available
    if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan")))
    {
        QCanBusDevice *m_canDevice = QCanBus::instance()->createDevice(
                    QStringLiteral("socketcan"), QStringLiteral("can0"));
        m_canDevice->connectDevice();
        connect(m_canDevice, &QCanBusDevice::framesReceived,this, &HaltechCAN::readyToRead);
        //connect(this->m_canDevice,SIGNAL(framesReceived()),this,SLOT(readyToRead()));
        qDebug() << "Successfully connected to socketcan ";
    }
    else
        qDebug() << "Could not connect to Haltech CAN device";
}
void HaltechCAN::closeConnection()
{
    disconnect(m_canDevice, &QCanBusDevice::framesReceived,this, &HaltechCAN::readyToRead);
    m_canDevice->disconnectDevice();
    delete m_canDevice;
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
        pkgpayload[0] = info->CH1;
        pkgpayload[1] = info->CH2;
        pkgpayload[2] = info->CH3;
        pkgpayload[3] = info->CH4;

        switch(frame.frameId()) {

        case 0x360:
             m_dashboard->setRevs(pkgpayload[0]);
             m_dashboard->setMAP(pkgpayload[1]*0.1);
            //m_dashboard->setTPS(pkgpayload[2]*0.1);
            //m_dashboard->setCoolantPressure(pkgpayload[3]*0.1);
            break;
        case 0x361:
            //m_dashboard->Fuel Pressure (pkgpayload[0]*0.1)
            //m_dashboard->Oil Pressure (pkgpayload[1]*0.1)
            //m_dashboard->Accelerator Pedal (pkgpayload[2]*0.1)
            //m_dashboard->Wastegate Pressure (pkgpayload[3]*0.1)
            break;
        case 0x362:
            m_dashboard->setInj1(pkgpayload[0]*0.1);
            m_dashboard->setInj2(pkgpayload[1]*0.1);
            m_dashboard->setLeadingign(pkgpayload[2]*0.1);
            m_dashboard->setTrailingign(pkgpayload[3]*0.1);
            break;
        case 0x363:
            //Wheel Slip(pkgpayload[0]*0.1)
            //Wheel diff(pkgpayload[1]*0.1)
            //Engine Acceleration(pkgpayload[2])
            //Manifold Pressure2(pkgpayload[3]*0.1)
            break;
        case 0x368:
            //Lambda1 (pkgpayload[0]*0.001)
            //Lambda2 (pkgpayload[1]*0.001)
            //Lambda3 (pkgpayload[2]*0.001)
            //Lambda4 (pkgpayload[3]*0.001)
            break;
        case 0x369:
            //Misscount (pkgpayload[0])
            //trigger counter(pkgpayload[1])
            //Home counter(pkgpayload[2])
            //Triggers since last home(pkgpayload[3])
            break;
        case 0x36A:
            //knock Level Logged(pkgpayload[0])
            //knock level logged2(pkgpayload[1])
            //knock retard bank1(pkgpayload[2]*0.1)
            //knock retart bank 2(pkgpayload[3]*0.1)
            break;
        case 0x36B:
            //Brake Pressure(pkgpayload[0])
            //NOS Pressure(pkgpayload[1])
            //Turbo Speed Sensor(pkgpayload[2])
            //G-Sensor (pkgpayload[3])
            break;
        case 0x36C:
            //Wheel speed FL(pkgpayload[0]*0.1)
            //Wheel speed FR(pkgpayload[1]*0.1)
            //Wheel speed RL(pkgpayload[2]*0.1)
            //Wheel speed RR(pkgpayload[3]*0.1)
            break;
        case 0x36D:
            //Wheelspeed front(pkgpayload[0]*0.1)
            //Wheelspeed rear(pkgpayload[1]*0.1)
            //Exhaust CAM Angle 1(pkgpayload[2]*0.1)
            //Exhaust CAM ANgle 2(pkgpayload[3]*0.1)
            break;
        case 0x36E:
            //Fuel cut % (pkgpayload[0]*0.1)
            //Launch control IGN Retard(pkgpayload[1]*0.1)
            //Launch control fuel Enrich(pkgpayload[2]*0.1)
            break;
        case 0x36F:
            //Boost Control outpu (pkgpayload[1]*0.01)
            //Timed Duty output 1(pkgpayload[2]*0.1)
            //Timed Duty output 2(pkgpayload[3]*0.1)
            break;
        case 0x370:
            m_dashboard->setSpeed(pkgpayload[0]*0.1);
            //Gear (pkgpayload[1])
            //Intake CAM Angle 1 (pkgpayload[2]*0.1)
            //Intake CAM Angle 2 (pkgpayload[3]*0.1)
            break;
        case 0x371:
            //Fuel FLow (pkgpayload[0])
            //Fuel Flow Return(pkgpayload[1])
            //Fuel FLow Differential(pkgpayload[2])
            break;
        case 0x372:
            m_dashboard->setBatteryV(pkgpayload[0]*0.1);
            //Air Temp Sensor2(pkgpayload[1]*0.1)
            //Target Boost Level (pkgpayload[2]*0.1)
            //Barometric Pressure(pkgpayload[3]*0.1)
            break;
        case 0x373:
            //EGT1(pkgpayload[0]*0.1)
            //EGT2(pkgpayload[1]*0.1)
            //EGT3(pkgpayload[2]*0.1)
            //EGT4(pkgpayload[3]*0.1)
            break;
        case 0x374:
            //EGT5(pkgpayload[0]*0.1)
            //EGT6(pkgpayload[1]*0.1)
            //EGT7(pkgpayload[2]*0.1)
            //EGT8(pkgpayload[3]*0.1)
            break;
        case 0x375:
            //EGT9(pkgpayload[0]*0.1)
            //EGT10(pkgpayload[1]*0.1)
            //EGT11(pkgpayload[2]*0.1)
            //EGT12(pkgpayload[3]*0.1)
            break;
        case 0x3E0:
            m_dashboard->setWatertemp(pkgpayload[0]*0.1);
            m_dashboard->setIntaketemp(pkgpayload[1]*0.1);
            m_dashboard->setFueltemp(pkgpayload[2]*0.1);
            //Oil Temp(pkgpayload[3]*0.1)
            break;
        case 0x3E1:
            //Transmission Oil Temp (pkgpayload[0]*0.1)
            //Diff oil temp (pkgpayload[1]*0.1)
            //Fuel Composition(pkgpayload[2]*0.1)
            break;
        case 0x3E2:
            //Fuel composition rate (pkgpayload[1]*0.1)
            //Average fuel economy(pkgpayload[2]*0.1)
            break;
        case 0x3E3:
            //Fuel Trim Short Term Bank 1 (pkgpayload[0]*0.1)
            //Fuel Trim Short Term Bank 2 (pkgpayload[1]*0.1)
            //Fuel Trim Long Term Bank 1(pkgpayload[2]*0.1)
            //Fuel Trim Long Term Bank 2(pkgpayload[3]*0.1)
            break;
        case 0x3E4:

            //Bit Flags ( too lazy to do that now )
            //(pkgpayload[0]*0.1)
            //(pkgpayload[1]*0.1)
            //(pkgpayload[2]*0.1)
            //(pkgpayload[3]*0.1)
            break;
        }
    }
}

