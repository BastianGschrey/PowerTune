#include "datalogger.h"
#include "dashboard.h"
#include <QFile>
#include <QTextStream>
#include <QThread>

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
                << endl;
            mFile.close();
        }
    }
}



void datalogger::createHeader()
{

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
                    << endl;
            mFile.close();
        }
    }
}
