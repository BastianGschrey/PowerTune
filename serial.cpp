
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
  \author Suriyan Laohaprapanon & Jacob Donley & Bastian Gschrey
 */


#include "serial.h"


serial::serial(QObject *parent) : QObject(parent)
{
serialport = new QSerialPort(this);
}



// FD3S map
static QString map[] = {"RPM", "Intakepress", "PressureV",
                       "ThrottleV", "Primaryinp", "Fuelc", "Leadingign", "Trailingign",
                       "Fueltemp", "Moilp", "Boosttp", "Boostwg", "Watertemp", "Intaketemp", "Knock", "BatteryV",
                       "Speed", "Iscvduty", "O2volt", "na1", "Secinjpulse",
                       "na2",
                       "AUX1", "AUX2", "AUX3", "AUX4", "AUX5", "AUX6", "AUX7", "AUX8",
                       "Analog1", "Analog2", "Analog3", "Analog4",
                       "Power", "Accel", "GForce", "ForceN", "Gear", "PrimaryInjD", "AccelTimer",
                       "Rec" };

//static double rtv[MAP_ELEMENTS];


/*!
    \brief Wrapper function that does a nonblocking select()/read loop .
    \param fd is the serial port filedescriptor
    \param buf is the pointer to where to stick the data
    \param count is how many bytes to read
    \param len is the pointer to length read
    \returns TRUE on success, FALSE otherwise
    */

void serial::read() const
{

}

//function to open serial port
void serial::openConnection(SerialSetting::Settings *p)
{
serialport->setBaudRate(p->baudRate);
serialport->setPortName(p->portName);
serialport->setParity(serialport->EvenParity);
serialport->setRequestToSend(true);
serialport->open(QIODevice::ReadWrite);
}
