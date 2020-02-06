#include "datalogger.h"
#include "dashboard.h"
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QDebug>

// Run this as a thread and update every 50 ms
// still need to find a way to make this configurable
QTime loggerStartT;
QString Log;

datalogger::datalogger(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)


{

}
datalogger::datalogger(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)

{
}

void datalogger::startLog(QString Logfilename)
{
        connect(&m_updatetimer, &QTimer::timeout, this, &datalogger::updateLog);
        Log = Logfilename;
        loggerStartT = QTime::currentTime();
        m_updatetimer.start(100);
        datalogger::createHeader();
}

void datalogger::stopLog()
{
    m_updatetimer.stop();
}

void datalogger::updateLog()
{

    m_updatetimer.start(50);
    QString filename = Log + ".csv";
    QFile file( filename );

    if ( file.open(QIODevice::ReadWrite) )
    {
        {
            QString fileName = Log + ".csv";
            //qDebug() << Logfile;
            QFile mFile(fileName);
            if(!mFile.open(QFile::Append | QFile::Text)){
            }
            QTextStream out(&mFile);

            switch(m_dashboard->ecu())
            {
            case 0: ////Apexi ECU
            out << (loggerStartT.msecsTo(QTime::currentTime())) << ","
                << m_dashboard->rpm() << ","
                << m_dashboard->Intakepress()  << ","
                << m_dashboard->PressureV()  << ","
                << m_dashboard->ThrottleV()  << ","
                << m_dashboard->Primaryinp() << ","
                << m_dashboard->Fuelc()  << ","
                << m_dashboard->Leadingign()  << ","
                << m_dashboard->Trailingign() << ","
                << m_dashboard->Fueltemp()  << ","
                << m_dashboard->Moilp()  << ","
                << m_dashboard->Boosttp()  << ","
                << m_dashboard->Boostwg()  << ","
                << m_dashboard->Watertemp()  << ","
                << m_dashboard->Intaketemp()  << ","
                << m_dashboard->Knock()  << ","
                << m_dashboard->BatteryV()  << ","
                << m_dashboard->speed()  << ","
                << m_dashboard->Iscvduty()  << ","
                << m_dashboard->O2volt()  << ","
                << m_dashboard->na1()  << ","
                << m_dashboard->Secinjpulse()  << ","
                << m_dashboard->na2()  << ","
                << m_dashboard->InjDuty()  << ","
                << m_dashboard->EngLoad()  << ","
                << m_dashboard->MAF1V()  << ","
                << m_dashboard->MAF2V()  << ","
                << m_dashboard->injms()  << ","
                << m_dashboard->Inj()  << ","
                << m_dashboard->Ign()  << ","
                << m_dashboard->Dwell()  << ","
                << m_dashboard->BoostPres()  << ","
                << m_dashboard->BoostDuty()  << ","
                << m_dashboard->MAFactivity()  << ","
                << m_dashboard->O2volt_2()  << ","
                << m_dashboard->pim()  << ","
                << m_dashboard->auxcalc1()  << ","
                << m_dashboard->auxcalc2()  << ","
                << m_dashboard->sens1()  << ","
                << m_dashboard->sens2()  << ","
                << m_dashboard->sens3()  << ","
                << m_dashboard->sens4()  << ","
                << m_dashboard->sens5()  << ","
                << m_dashboard->sens6()  << ","
                << m_dashboard->sens7()  << ","
                << m_dashboard->sens8()  << ","
                << m_dashboard->Flag1()  << ","
                << m_dashboard->Flag2()  << ","
                << m_dashboard->Flag3()  << ","
                << m_dashboard->Flag4()  << ","
                << m_dashboard->Flag5()  << ","
                << m_dashboard->Flag6()  << ","
                << m_dashboard->Flag7()  << ","
                << m_dashboard->Flag8() << ","
                << m_dashboard->Flag9()  << ","
                << m_dashboard->Flag10()  << ","
                << m_dashboard->Flag11()  << ","
                << m_dashboard->Flag12()  << ","
                << m_dashboard->Flag13()  << ","
                << m_dashboard->Flag14()  << ","
                << m_dashboard->Flag15()  << ","
                << m_dashboard->Flag16()  << ","
                << m_dashboard->MAP()  << ","
                << m_dashboard->AUXT()  << ","
                << m_dashboard->AFR()  << ","
                << m_dashboard->TPS()  << ","
                << m_dashboard->IdleValue()  << ","
                << m_dashboard->MVSS()  << ","
                << m_dashboard->SVSS()  << ","
                << m_dashboard->Inj1()  << ","
                << m_dashboard->Inj2()  << ","
                << m_dashboard->Inj3()  << ","
                << m_dashboard->Inj4()  << ","
                << m_dashboard->Ign1()  << ","
                << m_dashboard->Ign2()  << ","
                << m_dashboard->Ign3()  << ","
                << m_dashboard->Ign4()  << ","
                << m_dashboard->TRIM()  << ","
                << m_dashboard->gpsTime()   << ","
                << m_dashboard->gpsAltitude()   << ","
                << m_dashboard->gpsLatitude()   << ","
                << m_dashboard->gpsLongitude()   << ","
                << m_dashboard->gpsSpeed()   << ","
                << m_dashboard->gpsVisibleSatelites()   << ","
                << m_dashboard->accelx()  << ","
                << m_dashboard->accely()  << ","
                << m_dashboard->accelz()  << ","
                << m_dashboard->gyrox()  << ","
                << m_dashboard->gyroy()  << ","
                << m_dashboard->gyroz()  << ","
                << m_dashboard->compass()  << ","
                << m_dashboard->ambitemp()  << ","
                << m_dashboard->ambipress() << ","
                << m_dashboard->currentLap() << ","
                << m_dashboard->laptime()  << ","
                << endl;
            mFile.close();
            break;
            case 1: ////Link ECU Generic CAN
                out << (loggerStartT.msecsTo(QTime::currentTime())) << ","
                    << m_dashboard->rpm() << ","
                    << m_dashboard->MAP()  << ","
                    << "MGP"  << ","
                    << m_dashboard->ambipress()  << ","
                    << m_dashboard->TPS()  << ","
                    << m_dashboard->InjDuty()  << ","
                    << m_dashboard->InjDuty2()  << ","
                    << m_dashboard->injms()  << ","
                    << m_dashboard->Watertemp()  << ","
                    << m_dashboard->Intaketemp()   << ","
                    << m_dashboard->BatteryV()  << ","
                    << m_dashboard->MAFactivity()  << ","
                    << m_dashboard->Gear()  << ","
                    << m_dashboard->InjAngle()  << ","
                    << m_dashboard->Ign()  << ","
                    << m_dashboard->incamangle1()  << ","
                    << m_dashboard->incamangle2() << ","
                    << m_dashboard->excamangle1()  << ","
                    << m_dashboard->excamangle2()  << ","
                    << m_dashboard->LAMBDA()  << ","
                    << m_dashboard->lambda2()  << ","
                    << "Trig 1 Error Counter"  << ","
                    << m_dashboard->Error()  << ","
                    << m_dashboard->FuelPress() << ","
                    << m_dashboard->oiltemp() << ","
                    << m_dashboard->oilpres() << ","
                    << m_dashboard->wheelspdftleft()  << ","
                    << m_dashboard->wheelspdrearleft()  << ","
                    << m_dashboard->wheelspdftright()  << ","
                    << m_dashboard->wheelspdrearright()  << ","
                    << m_dashboard->Knock()  << ","
                    << "Knock Level 2"  << ","
                    << "Knock Level 3"  << ","
                    << "Knock Level 4"  << ","
                    << "Knock Level 5"  << ","
                    << "Knock Level 6"  << ","
                    << "Knock Level 7"  << ","
                    << "Knock Level 8"  << ","
                    << m_dashboard->currentLap() << ","
                    << m_dashboard->laptime()  << ","
                    << endl;
            mFile.close();
            break;
            case 2: ////Toyota86 BRZ FRS
                out << (loggerStartT.msecsTo(QTime::currentTime())) << ","
                    << m_dashboard->rpm() << ","
                    << m_dashboard->Watertemp()  << ","
                                   << m_dashboard->oiltemp() << ","
                                   << m_dashboard->wheelspdftleft()  << ","
                                   << m_dashboard->wheelspdrearleft()  << ","
                                   << m_dashboard->wheelspdftright()  << ","
                                   << m_dashboard->wheelspdrearright()  << ","
                                   << m_dashboard->SteeringWheelAngle()<< ","
                                   << m_dashboard->brakepress()<< ","
                                   << m_dashboard->gpsTime()   << ","
                                   << m_dashboard->gpsAltitude()   << ","
                                   << m_dashboard->gpsLatitude()   << ","
                                   << m_dashboard->gpsLongitude()   << ","
                                   << m_dashboard->gpsSpeed()   << ","
                                   << m_dashboard->currentLap() << ","
                                   << m_dashboard->laptime()  << ","
                                   << endl;
                mFile.close();
                break;
            case 5: ////ECU MASTERS EMU CAN
                out << (loggerStartT.msecsTo(QTime::currentTime())) << ","

                                   << m_dashboard->rpm() << ","
                                   << m_dashboard->TPS()  << ","
                                   << m_dashboard->injms() << ","
                                   << m_dashboard->speed()  << ","
                                   << m_dashboard->ambipress()  << ","
                                   << m_dashboard->oiltemp()  << ","
                                   << m_dashboard->oilpres()  << ","
                                   << m_dashboard->FuelPress()<< ","
                                   << m_dashboard->Watertemp()<< ","
                                   << m_dashboard->Ign()<< ","
                                   << m_dashboard->Dwell()<< ","
                                   << m_dashboard->LAMBDA()<< ","
                                   << m_dashboard->LAMBDA()<< ","
                                   << m_dashboard->egt1()<< ","
                                   << m_dashboard->egt2()<< ","
                                   << m_dashboard->Gear()<< ","
                                   << m_dashboard->BatteryV()<< ","
                                   << m_dashboard->fuelcomposition()<< ","
                                   << m_dashboard->Analog1()<< ","
                                   << m_dashboard->Analog2()<< ","
                                   << m_dashboard->Analog3()<< ","
                                   << m_dashboard->Analog4()<< ","
                                   << m_dashboard->Analog5()<< ","
                                   << m_dashboard->Analog6()<< ","
                                   << m_dashboard->gpsTime()   << ","
                                   << m_dashboard->gpsAltitude()   << ","
                                   << m_dashboard->gpsLatitude()   << ","
                                   << m_dashboard->gpsLongitude()   << ","
                                   << m_dashboard->gpsSpeed()   << ","
                                   << m_dashboard->currentLap() << ","
                                   << m_dashboard->laptime()  << ","
                                   << endl;
                mFile.close();
                break;

        }
    }
}
}


void datalogger::createHeader()
{
    qDebug()<< "ECU" << m_dashboard->ecu();
    QString filename = Log + ".csv";
    QFile file( filename );
   // qDebug() << "update Log";
    if ( file.open(QIODevice::ReadWrite) )
    {
        {
            QString fileName = Log + ".csv";
                        QFile mFile(fileName);
            if(!mFile.open(QFile::Append | QFile::Text)){
                           }

QTextStream out(&mFile);
            switch(m_dashboard->ecu())
            {
            case 0: ////Apexi

            out     << "Time ms" << ","
                    << "RPM" << ","
                    << "Intakepress"  << ","
                    << "PressureV"  << ","
                    << "ThrottleV"  << ","
                    << "Primaryinp"  << ","
                    << "Fuelc"  << ","
                    << "Leadingign"  << ","
                    << "Trailingign"  << ","
                    << "Fueltemp"  << ","
                    << "Moilp"  << ","
                    << "Boosttp"  << ","
                    << "Boostwg"  << ","
                    << "Watertemp"  << ","
                    << "Intaketemp"  << ","
                    << "Knock"  << ","
                    << "BatteryV"  << ","
                    << "speed"  << ","
                    << "Iscvduty"  << ","
                    << "O2volt"  << ","
                    << "na1"  << ","
                    << "Secinjpulse"  << ","
                    << "na2"  << ","
                    << "InjDuty"  << ","
                    << "Engine Load" << ","
                    << "MAF1 Voltage " << ","
                    << "MAF2 Voltage " << ","
                    << "injms"  << ","
                    << "Inj"  << ","
                    << "Ign"  << ","
                    << "Dwell"  << ","
                    << "BoostPres"  << ","
                    << "BoostDuty"  << ","
                    << "MAFactivity"  << ","
                    << "O2volt_2"  << ","
                    << "pim"  << ","
                    << "auxcalc1"  << ","
                    << "auxcalc2"  << ","
                    << m_dashboard->SensorString1() << ","
                    << m_dashboard->SensorString2() << ","
                    << m_dashboard->SensorString3() << ","
                    << m_dashboard->SensorString4() << ","
                    << m_dashboard->SensorString5() << ","
                    << m_dashboard->SensorString6() << ","
                    << m_dashboard->SensorString7() << ","
                    << m_dashboard->SensorString8() << ","
                    << m_dashboard->FlagString1() << ","
                    << m_dashboard->FlagString2() << ","
                    << m_dashboard->FlagString3() << ","
                    << m_dashboard->FlagString4() << ","
                    << m_dashboard->FlagString5() << ","
                    << m_dashboard->FlagString6() << ","
                    << m_dashboard->FlagString7() << ","
                    << m_dashboard->FlagString8() << ","
                    << m_dashboard->FlagString9() << ","
                    << m_dashboard->FlagString10() << ","
                    << m_dashboard->FlagString11() << ","
                    << m_dashboard->FlagString12() << ","
                    << m_dashboard->FlagString13() << ","
                    << m_dashboard->FlagString14() << ","
                    << m_dashboard->FlagString15() << ","
                    << m_dashboard->FlagString16() << ","
                    << "MAP"  << ","
                    << "AUXT"  << ","
                    << "AFR"  << ","
                    << "TPS"  << ","
                    << "IdleValue"  << ","
                    << "Master Speed" << ","
                    << "Slave Speed " << ","
                    << "Inj1"  << ","
                    << "Inj2"  << ","
                    << "Inj3"  << ","
                    << "Inj4"  << ","
                    << "Ign1"  << ","
                    << "Ign2"  << ","
                    << "Ign3"  << ","
                    << "Ign4"  << ","
                    << "TRIM"  << ","
                    << "GPS Time"   << ","
                    << "GPS Altitude"  << ","
                    << "GPS Latitude" << ","
                    << "GPS Longitude"   << ","
                    << "GPS Speed"  << ","
                    << "Visible Satelites"  << ","
                    << "Lateral Accel" << ","
                    << "Longitudinal Accel"  << ","
                    << "Gravity"  << ","
                    << "Gyro X"  << ","
                    << "Gyro Y"  << ","
                    << "Gyro Z"  << ","
                    << "Azimuth"  << ","
                    << "Ambient Temperature"  << ","
                    << "Ambient Pressure" << ","
                    << "Current LAP"    << ","
                    << "LAP TIME"       << ","
                    << endl;
            mFile.close();
                break;
            case 1: ////Link ECU Generic CAN
            out     << "Time ms" << ","
                    << "RPM" << ","
                    << "MAP"  << ","
                    << "MGP"  << ","
                    << "Barometric Pressure"  << ","
                    << "TPS"  << ","
                    << "Injector DC (pri)"  << ","
                    << "Injector DC (sec)"  << ","
                    << "Injector Pulse Width (Actual)"  << ","
                    << "ECT"  << ","
                    << "IAT"  << ","
                    << "ECU Volts"  << ","
                    << "MAF"  << ","
                    << "Gear Position"  << ","
                    << "Injector Timing"  << ","
                    << "Ignition Timing"  << ","
                    << "Cam Inlet Position L"  << ","
                    << "Cam Inlet Position R"  << ","
                    << "Cam Exhaust Position L"  << ","
                    << "Cam Exhaust Position R"  << ","
                    << "Lambda 1"  << ","
                    << "Lambda 2"  << ","
                    << "Trig 1 Error Counter"  << ","
                    << "Fault Codes"  << ","
                    << "Fuel Pressure" << ","
                    << "Oil Temp " << ","
                    << "Oil Pressure" << ","
                    << "LF Wheel Speed"  << ","
                    << "LR Wheel Speed"  << ","
                    << "RF Wheel Speed"  << ","
                    << "RR Wheel Speed"  << ","
                    << "Knock Level 1"  << ","
                    << "Knock Level 2"  << ","
                    << "Knock Level 3"  << ","
                    << "Knock Level 4"  << ","
                    << "Knock Level 5"  << ","
                    << "Knock Level 6"  << ","
                    << "Knock Level 7"  << ","
                    << "Knock Level 8"  << ","
                    << "Current LAP"    << ","
                    << "LAP TIME"       << ","
                    << endl;
            mFile.close();
                break;

            case 2: ////Toyota86 BRZ FRS
            out     << "Time ms" << ","
            << "RPM" << ","
            << "Coolant Temp" << ","
                           << "Oil Temp" << ","
                           << "LF Wheel Speed"  << ","
                           << "LR Wheel Speed"  << ","
                           << "RF Wheel Speed"  << ","
                           << "RR Wheel Speed"  << ","
                           << "Steering Wheel Angle "<< ","
                           << "Brake Pressure" ","
                           << "GPS Time"   << ","
                           << "GPS Altitude"  << ","
                           << "GPS Latitude" << ","
                           << "GPS Longitude"   << ","
                           << "GPS Speed"  << ","
                           << "Current LAP"    << ","
                           << "LAP TIME"  << ","
                              << endl;
                              mFile.close();
                                  break;

            case 5: ////EMU CAN
            out     << "Time ms" << ","
                           << "RPM" << ","
                           << "TPS" << ","
                           << "IAT" << ","
                           << "MAP"  << ","
                           << "Inj PW (ms)"  << ","
                           << "Speed"  << ","
                           << "Barometric Pressure"  << ","
                           << "Oil Temp"<< ","
                           << "Oil Pressure" ","
                           << "Fuel Pressure" ","
                           << "Coolant Temp" ","
                           << "Ignition Angle" ","
                           << "Dwell (ms)" ","
                           << "LAMDA λ" ","
                           << "LAMDA Corr. %" ","
                           << "EGT 1" ","
                           << "EGT 2" ","
                           << "Gear" ","
                           << "Battery V" ","
                           << "Ethanol %" ","
                           << "Analog 1 V" ","
                           << "Analog 2 V" ","
                           << "Analog 3 V" ","
                           << "Analog 4 V" ","
                           << "Analog 5 V" ","
                           << "Analog 6 V" ","
                           << "GPS Time"   << ","
                           << "GPS Altitude"  << ","
                           << "GPS Latitude" << ","
                           << "GPS Longitude"   << ","
                           << "GPS Speed"  << ","
                           << "Current LAP"    << ","
                           << "LAP TIME"  << ","
                              << endl;
                              mFile.close();
                                  break;
        }
        }
    }
}
