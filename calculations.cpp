/*
 * Copyright (C) 2018 Markus Ippy, Bastian Gschrey,
 * use this program at your own risk.
  \file calculations.cpp
  \brief Various Calculations Power / Torque / Gear / 0-100 ...
  \author Markus Ippy, Bastian Gschrey
 */

#include "calculations.h"
#include "dashboard.h"
#include <QDebug>

qreal Power;
qreal Torque;
qreal odometer;
qreal tripmeter;
qreal traveleddistance;

QTime startTime = QTime::currentTime();
QTime reactiontimerdiff = QTime::currentTime();
qreal dragdistance;
qreal dragdistancetotal;
qreal totaldragtime;
qreal zerotohundredtime;
qreal twohundredtime;
qreal threehundredtime;
qreal reactiontime;
qreal qmlgreentime;

int zerotohundredset = 0;
int hundredtotwohundredset = 0;
int twohundredtothreehundredset = 0;
int sixtyfootset = 0;
int threhundredthirtyfootset = 0;
int eightmileset = 0;
int quartermileset = 0;
int thousandfootset = 0;
int startdragcalculation = 0;

int weight; //just set this to 1300 for testing
int gearratio;
int odoisset;
int PreviousSpeed;
int Gear1;
int Gear2;
int Gear3;
int Gear4;
int Gear5;
int Gear6;
int GearN;

calculations::calculations(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)

{

}
calculations::calculations(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{

}

void calculations::start()
{
    connect(&m_updatetimer, &QTimer::timeout, this, &calculations::calculate);
    odometer = m_dashboard->Odo();
    tripmeter = m_dashboard->Trip();
    m_updatetimer.start(25);

}
void calculations::stop()
{
    m_updatetimer.stop();
}
void calculations::resettrip()
{
    tripmeter = 0;
    m_dashboard->setTrip(0);

}
void calculations::startdragtimer()
{

    zerotohundredtime= 0;
    twohundredtime = 0;
    threehundredtime = 0;

    dragdistance = 0;
    totaldragtime = 0;
    dragdistancetotal = 0;
    zerotohundredset = 0;
    hundredtotwohundredset = 0;
    twohundredtothreehundredset = 0;
    sixtyfootset = 0,
    threhundredthirtyfootset = 0;
    eightmileset = 0;
    quartermileset = 0;
    thousandfootset = 0;
    startdragcalculation = 0;
    startdragcalculation = 1;
}
void calculations::startreactiontimer()
{
    qDebug() << "Reactiontimer start";
    reactiontime = 0;
    qmlgreentime = 0;
    reactiontimerdiff = QTime::currentTime();
    m_reactiontimer.start();
}

void calculations::qmlrealtime()
{
    qDebug() << "QML Light Green";
    qmlgreentime = (reactiontimerdiff.msecsTo(QTime::currentTime())/ 1000); // reactiontime

}
void calculations::stopreactiontimer()
{
    qDebug() << "stop reaction timer";
    m_reactiontimer.stop();
    reactiontime = (reactiontimerdiff.msecsTo(QTime::currentTime())); // reactiontime

}
void calculations::calculatereactiontime()
{
    m_dashboard->setreactiontime((reactiontime / 1000) - qmlgreentime) ;
}
// 1 foot = 0,00018939 miles =
// 60 Feet = 0,0113634 miles = 0,01828762 km
// 330 Feet  = 0,0624987 miles = 0,10058191 km
void calculations::calculate()
{

    weight = m_dashboard->Weight();
    //qDebug() << "Weight" << weight;

    //starting the timer again with 25 ms
    m_updatetimer.start(25);

// Dragracing Calculations
if (m_dashboard->speedunits() == "metric" && startdragcalculation == 1)
    {
    dragdistance = ((startTime.msecsTo(QTime::currentTime())) * ((m_dashboard->speed()) / 3600000)); // Odometer
    totaldragtime += (startTime.msecsTo(QTime::currentTime()));
    dragdistancetotal += dragdistance;
    if (dragdistancetotal >= 0.01828762 && sixtyfootset == 0)
       {
        m_dashboard->setsixtyfoottime(totaldragtime / 1000);
        m_dashboard->setsixtyfootspeed(m_dashboard->speed());
        sixtyfootset = 1;
       }
    if (dragdistancetotal >= 0.10058191 &&  threhundredthirtyfootset == 0)
       {
        m_dashboard->setthreehundredthirtyfoottime(totaldragtime / 1000);
        m_dashboard->setthreehundredthirtyfootspeed(m_dashboard->speed());
        threhundredthirtyfootset = 1;
       }
    if (dragdistancetotal >= 0.201168 && eightmileset == 0)
       {
        m_dashboard->seteightmiletime(totaldragtime / 1000);
        m_dashboard->seteightmilespeed(m_dashboard->speed());
        eightmileset = 1;
       }
    if (dragdistancetotal >= 0.402336 && quartermileset == 0)
       {
        m_dashboard->setquartermiletime(totaldragtime / 1000);
        m_dashboard->setquartermilespeed(m_dashboard->speed());
        quartermileset = 1;
       }
    if (dragdistancetotal >= 0.3048 &&  thousandfootset == 0)
       {
        m_dashboard->setthousandfoottime(totaldragtime / 1000);
        m_dashboard->setthousandfootspeed(m_dashboard->speed());
        thousandfootset = 1;
       }
    if (m_dashboard->speed() >= 100 && zerotohundredset == 0)
        {
        zerotohundredtime = totaldragtime;
        m_dashboard->setzerotohundredt(totaldragtime / 1000);
        zerotohundredset = 1;
        }
    if (m_dashboard->speed() >= 200 && hundredtotwohundredset == 0)
        {
        twohundredtime = totaldragtime - zerotohundredtime;
        m_dashboard->sethundredtotwohundredtime(twohundredtime / 1000);
        hundredtotwohundredset = 1;
        }
    if (m_dashboard->speed() >= 300 && twohundredtothreehundredset == 0)
        {
        threehundredtime = totaldragtime - zerotohundredtime - twohundredtime;
        m_dashboard->settwohundredtothreehundredtime(threehundredtime / 1000);
        twohundredtothreehundredset = 1;
        }
}
if (m_dashboard->speedunits()  == "imperial"  && startdragcalculation == 1)
{    dragdistance = ((startTime.msecsTo(QTime::currentTime())) * ((m_dashboard->speed()) / 3600000)); // Odometer
     totaldragtime += (startTime.msecsTo(QTime::currentTime()));
     dragdistancetotal += dragdistance;
     if (dragdistancetotal >= 0.0113634 && sixtyfootset == 0)
        {
         m_dashboard->setsixtyfoottime(totaldragtime / 1000);
         m_dashboard->setsixtyfootspeed(m_dashboard->speed());
         sixtyfootset = 1;
        }
     if (dragdistancetotal >= 0.0624987 &&  threhundredthirtyfootset == 0)
        {
         m_dashboard->setthreehundredthirtyfoottime(totaldragtime / 1000);
         m_dashboard->setthreehundredthirtyfootspeed(m_dashboard->speed());
         threhundredthirtyfootset = 1;
        }
     if (dragdistancetotal >= 0.125 && eightmileset == 0)
        {
         m_dashboard->seteightmiletime(totaldragtime / 1000);
         m_dashboard->seteightmilespeed(m_dashboard->speed());
         eightmileset = 1;
        }
     if (dragdistancetotal >= 0.25 && quartermileset == 0)
        {
         m_dashboard->setquartermiletime(totaldragtime / 1000);
         m_dashboard->setquartermilespeed(m_dashboard->speed());
         quartermileset = 1;
        }
     if (dragdistancetotal >= 0.18939394 &&  thousandfootset == 0)
        {
         m_dashboard->setthousandfoottime(totaldragtime / 1000);
         m_dashboard->setthousandfootspeed(m_dashboard->speed());
         thousandfootset = 1;
        }
     if (m_dashboard->speed() >= 60 && zerotohundredset == 0)
         {
         zerotohundredtime = totaldragtime;
         m_dashboard->setzerotohundredt(totaldragtime / 1000);
         zerotohundredset = 1;
         }
     if (m_dashboard->speed() >= 120 && hundredtotwohundredset == 0)
         {
         twohundredtime = totaldragtime - zerotohundredtime;
         m_dashboard->sethundredtotwohundredtime(twohundredtime / 1000);
         hundredtotwohundredset = 1;
         }
     if (m_dashboard->speed() >= 180 && twohundredtothreehundredset == 0)
         {
         threehundredtime = totaldragtime - zerotohundredtime - twohundredtime;
         m_dashboard->settwohundredtothreehundredtime(threehundredtime / 1000);
         twohundredtothreehundredset = 1;
         }
}

// Dragracing Calculations END
   if (m_dashboard->gearcalcactivation() == 1)
     {
     //Gear Calculation borrowed from Raspexi big thanks to Jacob Donley
     int N = m_dashboard->rpm() / (m_dashboard->speed() == 0.0 ? 0.01 : m_dashboard->speed()); 
     int CurrentGear = (N > (m_dashboard->gearcalc1()*1.5) ? 0.0 : (N > ((m_dashboard->gearcalc1() + m_dashboard->gearcalc2()) / 2.0) ? 1.0 : (N > ((m_dashboard->gearcalc2() + m_dashboard->gearcalc3()) / 2.0) ? 2.0 : (N > ((m_dashboard->gearcalc3() + m_dashboard->gearcalc4()) / 2.0) ? 3.0 : (N > ((m_dashboard->gearcalc4() + m_dashboard->gearcalc5()) / 2.0) ? 4.0 : (m_dashboard->gearcalc5() == 0 ? 0.0 : (N > ((m_dashboard->gearcalc5() + m_dashboard->gearcalc6()) / 2.0) ? 5.0 : (m_dashboard->gearcalc6() == 0 ? 0.0 : (N > (m_dashboard->gearcalc6() / 2.0) ? 6.0 : 0.0)))))))));
     m_dashboard->setGear(CurrentGear);
     m_dashboard->setGearCalculation(CurrentGear);
     //qDebug()<<"Gear"<< m_dashboard->Gear();
    }
/*

     qDebug()<<"Gear1"<< m_dashboard->gearcalc1();
     qDebug()<<"Gear2"<< m_dashboard->gearcalc2();
     qDebug()<<"Gear3"<< m_dashboard->gearcalc3();
     qDebug()<<"Gear4"<< m_dashboard->gearcalc4();
     qDebug()<<"Gear5"<< m_dashboard->gearcalc5();
     qDebug()<<"Gear6"<< m_dashboard->gearcalc6();
*/


    //Odometer
    traveleddistance = ((startTime.msecsTo(QTime::currentTime())) * ((m_dashboard->speed()) / 3600000)); // Odometer
    odometer += traveleddistance;
    tripmeter += traveleddistance;
    m_dashboard->setOdo(odometer);
    m_dashboard->setTrip(tripmeter);
    startTime.restart(); //(QTime::currentTime())

    // Virtual Dyno to calculate Wheel Power and Wheel Torque


    if (m_dashboard->units() == "metric")
    {
        //To calculate kW when set to Metric
        //Weight (kg) * LongAcc (g) * Speed channel (km/h) * 0.0031107
        Power = ((weight * m_dashboard->accely()) * m_dashboard->speed()) * 0.0031107;
        //To calculate Torque in Nm when set to Metric
        //Power (kW) * 9549 / rotational speed (rpm)
        Torque =  (Power * 9549) / m_dashboard->rpm();
        //qDebug() << "metric Power" <<Power;
        if (Power >= 1)
        {
            m_dashboard->setPower(Power);
            m_dashboard->setTorque(Torque);

        }
    }
    if (m_dashboard->units()  == "imperial")
    {
        // Horsepower when set to Imperial
        // Weight (lbs) * LongAcc (g) * Speed channel (mph) * 0.003054
        Power = weight * m_dashboard->accely() * m_dashboard->speed() * 0.003054;
        //To calculate Torque in ft-lb when set to Imperial
        // Power (hp) * 5252 / rotational speed (rpm)
        Torque =  (Power * 5252) / m_dashboard->rpm();
        if (Power >= 1)
        {
            m_dashboard->setPower(Power);
            m_dashboard->setTorque(Torque);

        }
    }

/*
    //calculate acceleration in G without speedo
    //Metric Calculation
    if (m_dashboard->units()  == "metric")
    {
    if (m_dashboard->speed() > PreviousSpeed)
    {
    m_dashboard->setaccely((((m_dashboard->speed() - PreviousSpeed) *0.277778) / (25 * 0.001))*0.10197162129779);
   // qDebug() << "G force "<< m_dashboard->accely();
    }
    }
    if (m_dashboard->units()  == "imperial")
    {
    if (m_dashboard->speed() > PreviousSpeed)
    {
    m_dashboard->setaccely(((((m_dashboard->speed() - PreviousSpeed)* 1.60934) *0.277778) / (25 * 0.001))*0.10197162129779);
    //qDebug() << "G force "<< m_dashboard->accely();
    }
    }

    PreviousSpeed = m_dashboard->speed();
*/

    //Voltage

}

