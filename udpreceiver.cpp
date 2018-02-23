#include "udpreceiver.h"
#include "dashboard.h"
#include <QUdpSocket>
#include <QHostAddress>
#include <QDataStream>


udpreceiver::udpreceiver(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)

{

}
udpreceiver::udpreceiver(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)

{

}

void udpreceiver::startreceiver()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
}

void udpreceiver::closeConnection()
{
    udpSocket->close();
    delete udpSocket;
}
void udpreceiver::processPendingDatagrams()
{

QByteArray datagram;

    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());


        QString ident;
        double Value;
        QDataStream in(&datagram, QIODevice::ReadOnly);
        in >> ident  >> Value;
        if (ident == "RPM"){m_dashboard->setRevs(Value);}
        if (ident == "MAP"){m_dashboard->setMAP(Value);}
        if (ident == "MAPV"){m_dashboard->setPressureV(Value);}
        if (ident == "ThroV"){m_dashboard->setThrottleV(Value);}
        if (ident == "Primaryinp"){m_dashboard->setPrimaryinp(Value);}
        if (ident == "Secinjpulse"){m_dashboard->setSecinjpulse(Value);}
        if (ident == "Fuelc"){m_dashboard->setFuelc(Value);}
        if (ident == "Leadingign"){m_dashboard->setLeadingign(Value);}
        if (ident == "Trailingign"){m_dashboard->setTrailingign(Value);}
        if (ident == "Fueltemp"){m_dashboard->setFueltemp(Value);}
        if (ident == "Moilp"){m_dashboard->setMoilp(Value);}
        if (ident == "Boosttp"){m_dashboard->setBoosttp(Value);}
        if (ident == "Boostwg"){m_dashboard->setBoostwg(Value);}
        if (ident == "Watertemp"){m_dashboard->setWatertemp(Value);}
        if (ident == "Intaketemp"){m_dashboard->setIntaketemp(Value);}
        if (ident == "Knock"){m_dashboard->setKnock(Value);}
        if (ident == "Knock Value"){m_dashboard->setRevs(Value);}
        if (ident == "BatteryV"){m_dashboard->setBatteryV(Value);}
        if (ident == "MSpeed"){m_dashboard->setSpeed(Value);}
        if (ident == "SSpeed"){m_dashboard->setMVSS(Value);}
        if (ident == "Iscvduty"){m_dashboard->setIscvduty(Value);}
        if (ident == "O2volt"){m_dashboard->setO2volt(Value);}
        if (ident == "O2volt2"){m_dashboard->setO2volt_2(Value);}
        if (ident == "EngLoad"){m_dashboard->setEngLoad(Value);}
        if (ident == "MAF1V"){m_dashboard->setMAF1V(Value);}
        if (ident == "MAF2V"){m_dashboard->setMAF2V(Value);}
        if (ident == "injms"){m_dashboard->setinjms(Value);}
        if (ident == "Inj"){m_dashboard->setInj(Value);}
        if (ident == "Dwell"){m_dashboard->setDwell(Value);}
        if (ident == "BoostPres"){m_dashboard->setBoostPres(Value);}
        if (ident == "BoostDuty"){m_dashboard->setBoostDuty(Value);}
        if (ident == "MAFactivity"){m_dashboard->setMAFactivity(Value);}
    }
}
