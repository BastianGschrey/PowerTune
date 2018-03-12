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
int PreviousSpeed;
int weight; //just set this to 1300 for testing
int gearratio;
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
    //loggerStartT = QTime::currentTime();
    m_updatetimer.start(25);

}

void calculations::calculate()
{

    weight = m_dashboard->Weight();
    //qDebug() << "Weight" << weight;

    //starting the timer again with 25 ms
    m_updatetimer.start(25);
    /*

    // Calculate selected Gear from gearratio
    //120, 70, 45, 35, 26

    gearratio = m_dashboard->revs() / m_dashboard->speed();
    if (gearratio == gear1)
       {
       m_dashboard->SetGear(1);
       }
    if (gearratio == gear2)
       {
       m_dashboard->SetGear(2);
       }
    if (gearratio == gear3)
       {
       m_dashboard->SetGear(3);
       }
    if (gearratio == gear4)
       {
       m_dashboard->SetGear(4);
       }
    if (gearratio == gear5)
       {
       m_dashboard->SetGear(5);
       }
    if (gearratio == gear6)
       {
       m_dashboard->SetGear(6);
       }

  */
    // Virtual Dyno to calculate Wheel Power and Wheel Torque


    if (m_dashboard->units() == "metric")
    {
        //To calculate kW when set to Metric
        //Weight (kg) * LongAcc (g) * Speed channel (km/h) * 0.0031107
        Power = ((weight * m_dashboard->accely()) * m_dashboard->speed()) * 0.0031107;
        //To calculate Torque in Nm when set to Metric
        //Power (kW) * 9549 / rotational speed (rpm)
        Torque =  (Power * 9549) / m_dashboard->revs();
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
        Torque =  (Power * 5252) / m_dashboard->revs();
        if (Power >= 1)
        {
            m_dashboard->setPower(Power);
            m_dashboard->setTorque(Torque);

        }
    }

    //calculate acceleration in G without speedo
    //Metric Calculation
    if (m_dashboard->units()  == "metric")
    {
    if (m_dashboard->speed() > PreviousSpeed)
    {
    m_dashboard->setaccely(((((m_dashboard->speed() - PreviousSpeed) *1000) / 3600 )/ (25 * 0.001))*0.10197162129779);
   // qDebug() << "G force "<< m_dashboard->accely();
    }
    }
    if (m_dashboard->units()  == "imperial")
    {
    if (m_dashboard->speed() > PreviousSpeed)
    {
    m_dashboard->setaccely((((((m_dashboard->speed() - PreviousSpeed)*1.60934) *1000) / 3600 )/ (25 * 0.001))*0.10197162129779);
    //qDebug() << "G force "<< m_dashboard->accely();
    }
    }

    PreviousSpeed = m_dashboard->speed();


}

