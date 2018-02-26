/*
 * Copyright (C) 2018 Markus Ippy
 *
 * Nissan Consult Communication Protocol for PowerTune 
 *
 * This software comes under the GPL (GNU Public License)
 * You may freely copy,distribute etc. this as long as the source code
 * is made available for FREE.
 *
 * No warranty is made or implied. You use this program at your own risk.

  \file Nissanconsult.h
  \brief request and receive messages from Nissan Consult ECU’s
  \author Markus Ippy
 */


#ifndef NISSANCONSULT_H
#define NISSANCONSULT_H
#include <QtSerialPort/QSerialPort>
#include <QTimer>

namespace ConsultData {
        enum ENUM {

        LiveDataRequest     =   0x5A,
        CASPosRPMMSB 		=	0x00,
        CASPosRPMLSB 		=	0x01,
        CASRefRPMMSB 		=	0x02,
        CASRefRPMLSB 		=	0x03,
        MAFVoltMSB          =	0x04,
        MAFVoltLSB          =	0x05,
        RHMAFVoltMSB 		=	0x06,
        RHMAFVoltLSB 		=   0x07,
        CoolantTemp         =	0x08,
        LHO2Volt 			=	0x09,
        RHO2Volt			=	0x0a,
        Speed               =	0x0b,
        BattVolt 			=	0x0c,
        TPS                 =	0x0d,
        FuelTemp			=	0x0f,
        IAT                 =	0x11,
        EGT                 =	0x12,
        DigitalBitRegister 	=	0x13,
        InjectTimeLHMSB 	=	0x14,
        InjectTimeLHLSB 	=	0x15,
        IgnitionTiming 		=	0x16,
        AACValve			=	0x17,
        AFALPHALH			=   0x1a,
        AFALPHARH           =	0x1b,
        AFALPHASELFLEARNLH 	=	0x1c,
        AFALPHASELFLEARNRH 	=	0x1d,
        DigitalControlReg1	=	0x1e,
        DigitalControlReg2	=	0x1f,
        MRFCMNT             =	0x21,
        InjecttimeRHMSB 	=	0x22,
        InjecttimeRHLSB		= 	0x23,
        WasteGate			=	0x28,
        MAPVolt             =	0x29,
        EngineMount         =	0x2a,
        PositionCounter 	=	0x2e,
        PurgVolControlValve =	0x25,
        FueltTankTemp		=	0x26,
        FPCMDRVolt          =	0x27,
/*
        Fuel Gauge, Voltage =   0x2f,
        FR O2 Heater-B1 	=	0x30,
        FR O2 Heater-B2 	=	0x31,
        Ignition Switch 	=	0x32,
        CAL/LD Value, % 	=	0x33,
        B/Fuel Schedule, mS =	0x34,
        RR O2 Sensor Voltage =	0x35,
        RR O2 Sensor-B2 Voltage 		=	0x36,
        Absolute Throttle Position		=   0x37,
        MAF gm/S 				=	0x38,
        EvapSystemPressureVoltage 		=	0x39,
        Absolute Pressure SensorDual 	=   0x3a, 0x4a
        FPCM F/P VoltageDual 		=	0x52, 0x53
*/
        TerminateMessage	=	0xF0,
        Stop             	=	0x30


       };
    }
class DashBoard;
class SerialPort;



class Nissanconsult : public QObject
{
    Q_OBJECT

public:


    explicit Nissanconsult(QObject *parent = 0);
    explicit Nissanconsult(DashBoard *dashboard, QObject *parent = 0);
    Q_INVOKABLE void initSerialPort();
    Q_INVOKABLE void openConnection(const QString &portName);
    Q_INVOKABLE void closeConnection();

public slots:


public:


private:
    DashBoard *m_dashboard;
    SerialPort *m_serialconsult;
    QByteArray  m_readDataConsult;
    QByteArray  m_ECUResponsecomplete;
    QByteArray  m_buffer;
    QByteArray  m_consultreply;
    QTimer      m_DTCtimer;


signals:



public slots:
    void InitECU();
    void LiveReqMsg(const int &val1, const int &val2, const int &val3, const int &val4, const int &val5, const int &val6, const int &val7, const int &val8, const int &val9, const int &val10, const int &val11, const int &val12, const int &val13, const int &val14, const int &val15, const int &val16, const int &val17, const int &val18, const int &val19, const int &val20, const int &val21, const int &val22, const int &val23, const int &val24, const int &val25, const int &val26, const int &val27, const int &val28, const int &val29);
    void StopStream();
    void RequestDTC();
    void RequestLiveData();
    void readyToRead();
    void ProcessRawMessage(const QByteArray &buffer);
    void ProcessMessage(QByteArray m_ECUResponsecomplete);


};

#endif // NISSANCONSULT_H
