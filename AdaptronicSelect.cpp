#include "AdaptronicSelect.h"
#include "dashboard.h"
#include "connect.h"
#include "serialport.h"
#include <QtSerialPort/QSerialPort>
#include <QModbusRtuSerialMaster>
#include <QModbusClient>
#include <QModbusReply>



AdaptronicSelect::AdaptronicSelect(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)

{
}

AdaptronicSelect::AdaptronicSelect(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
    , lastRequest(nullptr)
    , modbusDevice(nullptr)

{

    //connect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));


}


int units2;




//function to open serial port
void AdaptronicSelect::openConnection(const QString &portName)
{
    modbusDevice = new QModbusRtuSerialMaster(this);
    connect(this,SIGNAL(sig_adaptronicReadFinished()),this,SLOT(AdaptronicStartStream()));

    if (!modbusDevice)
        return;

    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
/*
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,portName);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,57600);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,8);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,0);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,1);
        modbusDevice->setTimeout(200);
        modbusDevice->setNumberOfRetries(10);
        modbusDevice->connectDevice();
*/
        AdaptronicSelect::AdaptronicStartStream();

    }


}

AdaptronicSelect::~AdaptronicSelect()
{

    if (modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;

}
// Adaptronic streaming comms

void AdaptronicSelect::AdaptronicStartStream()
{
    auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 4096, 21),1); // read first twenty-one realtime values
    if (!reply->isFinished())
        connect(reply, &QModbusReply::finished, this,&AdaptronicSelect::readyToRead);
    else
        delete reply;

}


void AdaptronicSelect::setUnits(const int &unitSelect)
{
    units2 = unitSelect;
    if (units2 == 0 )
    {m_dashboard->setunits("metric");}
    if (units2 == 1 )
    {m_dashboard->setunits("imperial");}

}

void AdaptronicSelect::readyToRead()
{

        auto reply = qobject_cast<QModbusReply *>(sender());
        if(!reply)
            return;
        if(reply->error() == QModbusDevice::NoError){
            const QModbusDataUnit unit = reply->result();
            AdaptronicSelect::decodeAdaptronic(unit);

}
}

void AdaptronicSelect::decodeAdaptronic(QModbusDataUnit unit)
{

    qreal realBoost;
    int Boostconv;


 if (units2 == 0)
 {
     //qDebug() << "i am at 0 " ;
    m_dashboard->setSpeed(unit.value(10)); // <-This is for the "main" speedo KMH
 }
 if (units2 == 1)
 {
    m_dashboard->setSpeed(unit.value(10)*0.621371); // <-This is for the "main" speedo in MPH
 }
    m_dashboard->setRevs(unit.value(0));
    m_dashboard->setMAP(unit.value(1));
    if (units2 == 0)
    {
    m_dashboard->setIntaketemp(unit.value(2));
    }
    if (units2 == 1)
    {
    m_dashboard->setIntaketemp(qRound(unit.value(2)* 1.8 + 32));
    }
    if (units2 == 0)
    {
    m_dashboard->setWatertemp(unit.value(3));
    }
    if (units2 == 1)
    {
    m_dashboard->setWatertemp(qRound(unit.value(3)* 1.8 + 32));
    }
    if (units2 == 0)
    {
    m_dashboard->setAUXT(unit.value(4));
    }
    if (units2 == 1)
    {
    m_dashboard->setAUXT(unit.value(4)* 1.8 + 32);
    }
    m_dashboard->setauxcalc1(unit.value(5)/2570.00);
    m_dashboard->setKnock(unit.value(6)/256);
    m_dashboard->setTPS(unit.value(7));
    m_dashboard->setIdleValue(unit.value(8));
    m_dashboard->setBatteryV(unit.value(9)/10);
    if (units2 == 0)
    {
    m_dashboard->setMVSS(unit.value(10));
    }
    if (units2 == 1)
    {
    m_dashboard->setMVSS(qRound(unit.value(10)*0.621371));
    }
    if (units2 == 0)
    {
    m_dashboard->setSVSS(unit.value(11));
    }
    if (units2 == 1)
    {
    m_dashboard->setSVSS(qRound(unit.value(11)*0.621371));
    }
    m_dashboard->setInj1((unit.value(12)/3)*2);
    m_dashboard->setInj2((unit.value(13)/3)*2);
    m_dashboard->setInj3((unit.value(14)/3)*2);
    m_dashboard->setInj4((unit.value(15)/3)*2);
    m_dashboard->setIgn1((unit.value(16)/5));
    m_dashboard->setIgn2((unit.value(17)/5));
    m_dashboard->setIgn3((unit.value(18)/5));
    m_dashboard->setIgn4((unit.value(19)/5));
    m_dashboard->setTRIM((unit.value(20)));


    // Convert absolute pressure in KPA to relative pressure mmhg/Kg/cm2

        if ((unit.value(1)) > 103) // while boost pressure is positive multiply by 0.01 to show kg/cm2
        {
            Boostconv = ((unit.value(1))-103) ;
            realBoost = Boostconv* 0.01;
            //qDebug() << realBoost;
        }
        else if ((unit.value(1)) < 103) // while boost pressure is negative  multiply by 0.01 to show kg/cm2
        {
            Boostconv = ((unit.value(1))-103) * 7.50061561303;
            realBoost = Boostconv;

        }

    m_dashboard->setpim(realBoost);
    emit sig_adaptronicReadFinished();
}

