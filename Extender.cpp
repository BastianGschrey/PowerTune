                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    /*
 * Copyright (C) 2018 Markus Ippy, Bastian Gschrey,
 * use this program at your own risk.

  \file Extender.cpp
  \brief request and receive messages from Haltech via CAN Haltech CAN Protocol V2
  \author Markus Ippy
 */

#include "Extender.h"
#include "dashboard.h"
#include <QtEndian>
#include <QDebug>
#include <QVector>
#include "math.h"


QVector<int>averagehz1(0);
qreal avghz1;
qreal test1;
quint32 canstartadress;
quint32 canstartadressrpm;
quint32 adress1;
quint32 adress2;
quint32 adress3;
quint32 adress4;
quint32 adress5;
int statusmask = 128;
int frequencymask = 127;
qreal cylinders = 0;

Extender::Extender(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)

{

}
Extender::Extender(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}

Extender::~Extender()
{
}
void Extender::variables(const qreal &Cylinder)
{

    cylinders = (Cylinder/2);
    //qDebug() << "cylinders " << cylinders;
}
void Extender::openCAN(const int &ExtenderBaseID,const int &RPMCANBaseID)
{

    canstartadress = ExtenderBaseID;
    canstartadressrpm =
   // qDebug() << "CAN Start Adress :" << canstartadress;
   // qDebug() << "Opening CANbus ";
    adress1 = canstartadress + 1;
    adress2 = canstartadress + 2;
    adress3 = canstartadress + 3;
    adress5 = RPMCANBaseID + 1;
    if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan")))
    {
        QString errorString;
        m_canDevice = QCanBus::instance()->createDevice(QStringLiteral("socketcan"),
                                                                       QStringLiteral("can0"),&errorString);

        if (!m_canDevice) {
            //qDebug() << ("Error creating device");
            return;
        }



        if(m_canDevice->connectDevice()){
            //qDebug() << m_canDevice->state();
           // qDebug() << m_canDevice;
          //  qDebug() << "device connected!";
            //connect(m_canDevice,SIGNAL(framesReceived()),this,SLOT(readyToRead()));
            connect(m_canDevice, &QCanBusDevice::framesReceived, this, &Extender::readyToRead);
        }

    }
}
void Extender::closeConnection()
{
    disconnect(m_canDevice,SIGNAL(framesReceived()),this,SLOT(readyToRead()));
    if (m_canDevice)
    m_canDevice->disconnectDevice();


}
void Extender::readyToRead()
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
// This section decodes the recevied Payload according to the frame ID


       QByteArray splitpayload = frame.payload();
        payload* info=reinterpret_cast<payload*>(splitpayload.data());
        pkgpayload[0] = qFromLittleEndian(info->CH1);
        pkgpayload[1] = qFromLittleEndian(info->CH2);
        pkgpayload[2] = qFromLittleEndian(info->CH3);
        pkgpayload[3] = qFromLittleEndian(info->CH4);
        int byte0 =  splitpayload[0] ;
        int byte1 =  splitpayload[1] ;
        int byte2 =  splitpayload[2] ;
        int byte3 =  splitpayload[3] ;
        int byte4 =  splitpayload[4] ;
        int byte5 =  splitpayload[5] ;
        int byte6 =  splitpayload[6] ;
        int byte7 =  splitpayload[7] ;

        //switch(frame.frameId()) {

        //case adress1:
           if (frame.frameId() == adress1) {
            // ON / Off Status :

               m_dashboard->setEXDigitalInput1((byte0 & statusmask)>0);				  //Digital Input 0
                m_dashboard->setEXDigitalInput2((byte1 & statusmask)>0);				  //Digital Input 1
                m_dashboard->setEXDigitalInput3((byte2 & statusmask)>0);	       		  //Digital Input 2
                m_dashboard->setEXDigitalInput4((byte3 & statusmask)>0);				  //Digital Input 3
                m_dashboard->setEXDigitalInput5((byte4 & statusmask)>0);				  //Digital Input 4
                m_dashboard->setEXDigitalInput6((byte5 & statusmask)>0);				  //Digital Input 5
                m_dashboard->setEXDigitalInput7((byte6 & statusmask)>0);				  //Digital Input 6
                m_dashboard->setEXDigitalInput8((byte7 & statusmask)>0);				  //Digital Input 7
/*
            // Frequency Counter :

                m_dashboard->setEXDigitalInput1((byte0 & frequencymask)*16.6*30);				  //Digital Input 0
                m_dashboard->setEXDigitalInput2((byte1 & frequencymask)*16.6);				  //Digital Input 1
                m_dashboard->setEXDigitalInput3((byte2 & frequencymask)*16.6);	       		  //Digital Input 2
                m_dashboard->setEXDigitalInput4((byte3 & frequencymask)*16.6);				  //Digital Input 3
                m_dashboard->setEXDigitalInput5((byte4 & frequencymask)*16.6);				  //Digital Input 4
                m_dashboard->setEXDigitalInput6((byte5 & frequencymask)*16.6);				  //Digital Input 5
                m_dashboard->setEXDigitalInput7((byte6 & frequencymask)*16.6);				  //Digital Input 6
                m_dashboard->setEXDigitalInput8((byte7 & frequencymask)*16.6);				  //Digital Input 7


            //qDebug() << "Frequency :" << ((byte0 & frequencymask)*16.6);

            averagehz1.removeFirst();
            averagehz1.append((byte0 & frequencymask));
            //qDebug() << "Vector HZ " << averagehz1;
            avghz1 = 0;
            for (int i = 0; i <= 10-1; i++){avghz1+= averagehz1[i];}
            test1 = avghz1/10;
            averagehz1.resize(10);
            //qDebug() << "Frequency 10 samples :" << ((avghz1/10)*16.6);
            m_dashboard->setEXDigitalInput1((avghz1/10)*16.6*30);
            //qDebug() << "Test  :" << test1;

*/
}
        //case 0x402:
        if (frame.frameId() == adress2) {
                m_dashboard->setEXAnalogInput0(pkgpayload[0]*0.001);								  //Analog 0
                m_dashboard->setEXAnalogInput1(pkgpayload[1]*0.001);						  	  	  //Analog 1
                m_dashboard->setEXAnalogInput2(pkgpayload[2]*0.001);         					      //Analog 2
                m_dashboard->setEXAnalogInput3(pkgpayload[3]*0.001);						  	      //Analog 3
          //  break;
        }
        //case 0x403:
        if (frame.frameId() == adress3) {
                m_dashboard->setEXAnalogInput4(pkgpayload[0]*0.001);								  //Analog 4
                m_dashboard->setEXAnalogInput5(pkgpayload[1]*0.001);						      	  //Analog 5
                m_dashboard->setEXAnalogInput6(pkgpayload[2]*0.001);         				  		  //Analog 6
                m_dashboard->setEXAnalogInput7(pkgpayload[3]*0.001);						          //Analog 7
        //break;
        }
        if (frame.frameId() == adress5 && cylinders != 0) {
                m_dashboard->setrpm(qRound((pkgpayload[0]*4) / cylinders));                               //RPM

        //break;
        }

       // default:
       // break;
       // }
    }
}

