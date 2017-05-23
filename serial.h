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
  \
  \author Bastian Gschrey & Markus Ippy
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QModbusDataUnit>

class SerialPort;
class DashBoard;
class Decoder;
class AppSettings;
class QModbusClient;
class QModbusReply;

class Serial : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList portsNames READ portsNames WRITE setPortsNames NOTIFY sig_portsNamesChanged)

public:
    explicit Serial(QObject *parent = 0);

    Q_INVOKABLE void clear() const;
    Q_INVOKABLE void initSerialPort();
    Q_INVOKABLE void openConnection(const QString &portName, const int &ecuSelect, const int &interfaceSelect);
    Q_INVOKABLE void closeConnection();

public slots:
    void getPorts();
    void getEcus();

public:
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

    //Adaptronic Streaming Comms


    void AdaptronicStopStream();

    QStringList portsNames() const { return m_portsNames; }

private:
    SerialPort *m_serialport;
    Decoder *m_decoder;
    DashBoard *m_dashBoard;
    AppSettings *m_appSettings;
    QStringList m_portsNames;
    QStringList *m_ecuList;
    QModbusReply *lastRequest;
    QModbusClient *modbusDevice;



    //QModbusReply reply;


    QModbusDataUnit readRequest() const;

    void getFuelBase0();
    void getFuelBase1();
    void getFuelBase2();
    void getFuelBase3();
    void getFuelBase4();
    void getFuelBase5();
    void getFuelBase6();
    void getFuelBase7();

signals:
    void sig_finished();
    void sig_error(QString err);
    void sig_ApexiDataAvailable(QByteArray);
    void sig_portsNamesChanged(QStringList portsNames);



public slots:
    void readyToRead();
    void AdaptronicStartStream();



        //void openConnection(SerialSetting::Settings p); //open serial connection with settings
    void sendRequest(int requestIndex);

    void setPortsNames(QStringList portsNames)
    {
        if (m_portsNames == portsNames)
            return;

        m_portsNames = portsNames;
        emit sig_portsNamesChanged(portsNames);
    }
    void readData(QByteArray serialdata);


};

#endif // SERIAL_H
