#include "AdaptronicSelect.h"
#include "connect.h"
#include "serialport.h"
#include "dashboard.h"
#include "appsettings.h"
#include <QDebug>
#include <QThread>
//#include <QSerialPort>
//#include <QSerialPortInfo>
#include <QModbusRtuSerialMaster>


AdaptronicSelect::~AdaptronicSelect()
{

    if (modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;

}

AdaptronicSelect::AdaptronicSelect(DashBoard *dashboard, QObject *parent)
    : QObject(parent),
      m_dashboard(dashboard),
      lastRequest(nullptr),
      modbusDevice(nullptr)

    {

    }




//function to open serial port
void AdaptronicSelect::openConnection(const QString &portName)
{

    if (!modbusDevice)
    {
    modbusDevice = new QModbusRtuSerialMaster(this);
    connect(this,SIGNAL(sig_adaptronicReadFinished()),this,SLOT(AdaptronicStartStream()));
    qDebug() << "Modbusdevice created" ;
    }

     {



        if (modbusDevice->state() != QModbusDevice::ConnectedState)
        {
            modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,portName);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,57600);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,8);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,0);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,1);
            modbusDevice->setTimeout(200);
            modbusDevice->setNumberOfRetries(10);
            modbusDevice->connectDevice();
            if (modbusDevice->state() != QModbusDevice::ConnectedState)
            {
                qDebug()<< "error creating Modbus device";
                delete modbusDevice;
                modbusDevice = nullptr;
            }
            else
            AdaptronicSelect::AdaptronicStartStream();

       }

    }

}

void AdaptronicSelect::closeConnection()
{
    if (modbusDevice) {
        modbusDevice->disconnectDevice();
        delete modbusDevice;
        modbusDevice = nullptr;
    }
}


// Adaptronic streaming comms

void AdaptronicSelect::AdaptronicStartStream()
{
    auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 4096, 21),1); // read first twenty-one realtime values
    qDebug()<< "send :" <<((QModbusDataUnit::HoldingRegisters, 4096, 21),1);
    if (!reply->isFinished())
        connect(reply, &QModbusReply::finished, this,&AdaptronicSelect::readyToRead);
    else
        delete reply;

}



void AdaptronicSelect::readyToRead()
{

        auto reply = qobject_cast<QModbusReply *>(sender());
        qDebug()<< "recieve :" <<reply;
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

    //qDebug()<<"Watertemp: " <<unit.value(3);
    m_dashboard->setSpeed(unit.value(10)); // <-This is for the "main" speedo KMH
    m_dashboard->setrpm(unit.value(0));
    m_dashboard->setMAP(unit.value(1));
    m_dashboard->setIntaketemp(unit.value(2));
    m_dashboard->setWatertemp(unit.value(3));
    m_dashboard->setAUXT(unit.value(4));
    m_dashboard->setauxcalc1(unit.value(5)/2570.00);
    m_dashboard->setKnock(unit.value(6)/256);
    m_dashboard->setTPS(unit.value(7));
    m_dashboard->setIdleValue(unit.value(8));
    m_dashboard->setBatteryV(unit.value(9)/10);
    m_dashboard->setMVSS(unit.value(10));
    m_dashboard->setSVSS(unit.value(11));
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

