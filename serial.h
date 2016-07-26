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
  \author Suriyan Laohaprapanon & Jacob Donley & Bastian Gschrey & Markus Ippy
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
    void clear() const;

public:
    explicit Serial(QObject *parent = 0);


    void closeConnection();
    void getAdvData();
    void getAux();
    void getSensorData();
    void getMapIndices();
    void getBasic();
    void getRevIdle();
    void getSensorStrings();
    void getPimStrInjA();
    void getVersion();
    void getMapRef();
    void getLeadign1();
    void getLeadign2();
    void getLeadign3();
    void getLeadign4();
    void getTrailIgn1();
    void getTrailIgn2();
    void getTrailIgn3();
    void getTrailIgn4();
    void getInitPlatform();
    void getInjOverlap();
    void getInjvsFuelT();
    void getTurboTrans();
    void getOilervsWaterT();
    void getFanvsWater();
    void getInjcorr1();
    void getInjcorr2();
    void getInjcorr3();
    void getInjcorr4();
    void getFuelInj();
    void getCranking();
    void getWaterTcorr();
    void getInjvsWaterBoost();
    void getInjvsAirTBoost();
    void getInjPrimaryLag();
    void getAccInj();
    void getInjvsAccel();
    void getIgnvsAircold();
    void getIgnvsWater();
    void getIgnvsAirwarm();
    void getLIgnvsRPM();
    void getIgnvsBatt();
    void getBoostvsIgn();
    void getTrailIgnvsRPM();
    void getInjSecLagvsBattV();
    void getInjWarn();
    void getKnockWarn();
    void getO2Feedback();
    void getBoostcontrol();
    void getSettingProtections();
    void getTunerString();
    void getInjvsAirTemp();
    void getInjvsTPS();
    void getIgnvsTPS();
    void getPIMScaleOffset();
    void getWarConStrFlags();
    void getNotdocumented();

private:
QSerialPort *serialport;
void getFuelBase0();
void getFuelBase1();
void getFuelBase2();
void getFuelBase3();
void getFuelBase4();
void getFuelBase5();
void getFuelBase6();
void getFuelBase7();


signals:
void finished();
void error(QString err);
void SIG_dataAvailable(QByteArray);

public slots:
    void readyToRead();
//    void openConnection(SerialSetting::Settings p); //open serial connection with settings
    void sendRequest(int requestIndex);
};

#endif // SERIAL_H
