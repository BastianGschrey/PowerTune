/*
 * Copyright (C) 2016 Markus Ippy, Bastian Gschrey
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
  \file raspexi/powerfc.h
  \brief Raspexi Viewer Power FC related functions
  \author Suriyan Laohaprapanon & Jacob Donley
 */



#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


class serial : public QObject
{
    Q_OBJECT

public:

    /*
     * Source: http://www.rx7.org/public/PowerFC-DataLogIt.htm
     * ------------------
     * "Advanced" Information (Cooked Averages?)
     * ------------------
     * 0xF0
     * ------------------
     * short word : rpm (just as a short word, not worked over)
     * short word : pim (don't know... FCEdit just displays it as a short word)
     * short word : pim voltage * 1000.0f (divide by 1000.0f to get the voltage)
     * short word : tps voltage * 1000.0f (divide by 1000.0f to get the voltage)
     * short word : InjFP ms (short float)
     * short word : INJ (inj what? dunno... FCEdit shows it as a short word...)
     * byte : IGL (byte degree)
     * byte : IGT (byte degree)
     * byte : Fuel Temperature (as byte temperature)
     * byte : oil (FCEdit displays as just a byte...)
     * byte : Precontrol % (FCEdit calls it a %, but looks like it's just displaying the byte)
     * byte : Wastegate % (FCEdit calls it a %, but looks like it's just displaying the byte)
     * byte : water temperature (as byte temperature)
     * byte : air temperature (as byte temperature)
     * byte : knock
     * byte : battery voltage * 10.0f (divide by 10.0f to get voltage)
     *
     * NOTE: From here, FCEdit is unsure of what's what... Consequently, I'm unsure of what's what.
     *
     * short word : kph (don't know the units yet)
     * short word : unknown
     * byte : O2
     * byte : unknown
     * short word : InjFS (ms)
     */

    /*
    *Structure for FD3S information :
    */

    typedef struct {
        unsigned short RPM;				//0
        unsigned short Intakepress;		//1
        unsigned short PressureV;		//2
        unsigned short ThrottleV;		//3
        unsigned short Primaryinp;		//4
        unsigned short Fuelc;			//5
        unsigned char Leadingign;		//6
        unsigned char Trailingign;		//7
        unsigned char Fueltemp;			//8
        unsigned char Moilp;			//9
        unsigned char Boosttp;			//10
        unsigned char Boostwg;			//11
        unsigned char Watertemp;		//12
        unsigned char Intaketemp;		//13
        unsigned char Knock;			//14
        unsigned char BatteryV;			//15
        unsigned short Speed;			//16
        unsigned short Iscvduty;		//17
        unsigned char O2volt;			//18
        unsigned char na1;				//19
        unsigned short Secinjpulse;		//20
        unsigned char na2;				//21
    } fc_adv_info_t;

    /*
    *Structure for Auxiliary information :
    */
    typedef struct {
        unsigned char AUX1;
        unsigned char AUX2;
        unsigned char AUX3;
        unsigned char AUX4;
        unsigned char AUX5;
        unsigned char AUX6;
        unsigned char AUX7;
        unsigned char AUX8;
    } fc_aux_info_t;


    /*
    * Maximum number of elements in the above structs
    */
    #define FC_ADV_INFO_MAX_ELEMENTS	21 + 1  // Plus one is for the last unavailable item (e.g. na2, na1)
    #define FC_AUX_INFO_MAX_ELEMENTS	8
    #define ANALOG_INFO_MAX_ELEMENTS	4
    #define EXTRA_INFO_MAX_ELEMENTS		7
    #define MISC_INFO_MAX_ELEMENTS		1		// Miscellaneous
    #define MAP_ELEMENTS

    /*
    *Advanced Information :
    */
    #define FC_ADV_INFO_LEN		(0x20)
    #define FC_REQ_ADV_INFO		{0xF0, 0x02, 0x0D}

    /*
    * Auxiliary Information
    */
    #define FC_REQ_AUX_INFO		{0x00, 0x02, 0xFD}

    /*
    *Calculation to display KG/cm2 for Boost
    *
    */
    // FD3S
    #define FC_ADV_INFO_MUL		{1, 0.0001, 1, 1, 1.0/256, 1.0/256, 1, 1, 1, 212.0/256, 0.4, 0.4, 1, 1, 1, 0.1, 1, 0.1, 0.02, 1, 1.0/256, 1}
    #define FC_ADV_INFO_ADD		{0,-1.0332, 0, 0, 0, 0, -25, -25, -80, 0, 0, 0, -80, -80, 0, 0, 0, 0, 0, 0, 0, 0}



    double powerfc_get_current_value(QChar *);

    bool powerfc_process_advanced(void);
    bool powerfc_process_auxiliary(void);
    bool powerfc_process_extra(void);
    bool powerfc_process_misc(void);



public:
    explicit serial(QObject *parent = 0);

private:
QSerialPort *serialport;

signals:

public slots:
};

#endif // SERIAL_H
