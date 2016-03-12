/*
 * Copyright (C) 2016 Markus Ippy, Bastian Gschrey, Jan
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

/*
  \file serial.h
  \brief Raspexi Viewer Power FC related functions
  \author Suriyan Laohaprapanon & Jacob Donley & Bastian Gschrey
 */


#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <serialsetting.h>


class Serial : public QObject
{
    Q_OBJECT

public:

    char* FC_REQ_ADV_INFO[2];

    /*
    *Structure for FD3S infrmation :
    */


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
    #define MAP_ELEMENTS	FC_ADV_INFO_MAX_ELEMENTS + FC_AUX_INFO_MAX_ELEMENTS + ANALOG_INFO_MAX_ELEMENTS + EXTRA_INFO_MAX_ELEMENTS + MISC_INFO_MAX_ELEMENTS

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

    QByteArray read() const;

public:
    explicit Serial(QObject *parent = 0);

    void openConnection(SerialSetting::Settings); //open serial connection with settings
    void closeConnection();
    void getAdvData();

private slots:
    void readyToRead();

private:
QSerialPort *serialport;

signals:
void advRequested();
void readyRead();

public slots:
};

#endif // SERIAL_H
