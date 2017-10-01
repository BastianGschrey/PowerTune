/*
  \file decoder.cpp
  \brief Power Tune Power FC related functions
  \author Bastian Gschrey & Markus Ippy
 */

#include "decoder.h"
#include "dashboard.h"
#include "serial.h"
#include <QTime>
#include <QTimer>

#include <QDebug>
#include <QBitArray>
#include <QModbusDataUnit>

#include <QFile>
#include <QTextStream>
#include <QThread>



int units;// 0 Metric / 1 Imperial
QByteArray serialdata;
QByteArray fullFuelBase;
qreal AN1AN2calc;
qreal AN3AN4calc;

//QBitArray flagArray;
QString Logfile;
QString Auxname1;
QString Auxname2;
qreal odometer;
QTime startTime = QTime::currentTime();
QTime loggerStartTime = QTime::currentTime();
int Model = 0;
int Logging =3;
int Loggerstat;
int auxval1;
int auxval2;
int auxval3;
int auxval4;



double mul[80] = FC_INFO_MUL;  // required values for calculation from raw to readable values for Advanced Sensor info
double add[] = FC_INFO_ADD;

static QString mapFD3S[] ={"InjDuty", "IGL","IGT","Rpm","Speed","Boost","Knock","WtrTemp","AirTemp","BatVolt","PIM","VTA1","VTA2","VMOP","WTRT","AIRT","FUEL","O2S","STR","A/C","PWS","NTR","CLT","STP","CAT","ELD","HWL"};//	FPD	FPR	APR	PAC	CCN	TCN	PRC	AN1 raw	AN2 raw	AN3 raw	AN4 raw	AN1-AN2 Wide Band	AN2 raw	AN3 raw	AN4 raw	MAPN	MAPP	RPM	PIM	PIM V	TPS V	InjFrPr	Inj +/-	IGL	IGT	FuelT	Oil	PC%	WG%	WtrT	AirT	Knock	BatV	Speed	???(2)	O2S	???	InjFrSc
/*{"rpm", "pim", "pimV",
                        "TPS Voltage", "InjFp ms", "Inj",
                        "IGL", "IGT",
                        "Fuel", "Moilp", "Boosttp",
                        "Boostwg", "Watertemp", "Intaketemp",
                        "Knock", "BatteryV",
                        "Speed", "Iscvduty", "O2volt",
                        "na1", "Secinjpulse", "na2",
                        "AUX1", "AUX2", "AUX3", "AUX4",
                        "Analog1", "Analog2", "Analog3", "Analog4",
                        "Power", "Accel", "GForce", "ForceN", "Gear", "PrimaryInjD", "AccelTimer",
                        "Rec","Sens_PIM","Sens_VTA1","Sens_VTA2","Sens_VMOP","Sens_Wtrt","Sens_Airt",
                        "Sens_Fuel","Sens_O2", "STR", "A/C", "PWS", "NTR", "CLT",
                        "STP", "CAT", "ELD", "HWL", "FPD", "FPR", "APR", "PAC", "CCN", "TCN", "PRC" ,"MAP_N","MAP_P",
                        "Basic_Injduty", "Basic_IGL", "Basic_IGT", "Basic_RPM", "Basic_KPH", "Basic_Boost", "Basic_Knock", "Basic_Watert", "Basic_Airt", "Basic_BattV",};
*/
Decoder::Decoder(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)
{
}

Decoder::Decoder(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}

void Decoder::setUnits(const int &unitSelect)
{
    units = unitSelect;
    //qDebug() << "Unitselection"<< units;
}


void Decoder::decodeAdv(QByteArray serialdata)
{

    fc_adv_info_t* info=reinterpret_cast<fc_adv_info_t*>(serialdata.data());
    if (Model == 1)
    {

    packageADV[0] = info->RPM + add[0];
    packageADV[1] = info->Intakepress;
    packageADV[2] = info->PressureV * 0.001; //value in V
    packageADV[3] = info->ThrottleV * 0.001; //value in V
    packageADV[4] = info->Primaryinp * 0.001;
    packageADV[5] = info->Fuelc;
    packageADV[6] = info->Leadingign -25;
    packageADV[7] = info->Trailingign -25;
    packageADV[8] = info->Fueltemp + add[8];
    packageADV[9] = info->Moilp;     //Value lower by 10 compared to FC Edit
    packageADV[10] = info->Boosttp / 2.56;    // (FC edit shows just raw value
    packageADV[11] = info->Boostwg / 2.56;     // (FC edit shows just raw value
    if (units == 0 )
    {
    packageADV[12] = info->Watertemp -80;
    packageADV[13] = info->Intaketemp -80;
    }
    if (units == 1 )
    {
    packageADV[12] = ((info->Watertemp -80)* 1.8) + 32 ;
    packageADV[13] = ((info->Intaketemp -80)* 1.8) + 32 ;
    }
    packageADV[14] = info->Knock;
    packageADV[15] = info->BatteryV * 0.1;
    if (units == 0 )
    {
    packageADV[16] = info->Speed ;
    }
    if (units == 1 )
    {
    packageADV[16] = info->Speed  * 0.621371;
    }
    packageADV[17] = info->Iscvduty * 0.001;
    packageADV[18] = info->O2volt;
    packageADV[19] = info->na1;
    packageADV[20] = info->Secinjpulse * 0.001;
    packageADV[21] = info->na2;

    m_dashboard->setRevs(packageADV[0]);
    m_dashboard->setIntakepress(packageADV[1]);
    m_dashboard->setPressureV(packageADV[2]);
    m_dashboard->setThrottleV(packageADV[3]);
    m_dashboard->setPrimaryinp(packageADV[4]);
    m_dashboard->setFuelc(packageADV[5]);
    m_dashboard->setLeadingign(packageADV[6]);
    m_dashboard->setTrailingign(packageADV[7]);
    m_dashboard->setFueltemp(packageADV[8]);
    m_dashboard->setMoilp(packageADV[9]);
    m_dashboard->setBoosttp(packageADV[10]);
    m_dashboard->setBoostwg(packageADV[11]);
    m_dashboard->setWatertemp(packageADV[12]);
    m_dashboard->setIntaketemp(packageADV[13]);
    m_dashboard->setKnock(packageADV[14]);
    m_dashboard->setBatteryV(packageADV[15]);
    m_dashboard->setSpeed(packageADV[16]);
    m_dashboard->setIscvduty(packageADV[17]);
    m_dashboard->setO2volt(packageADV[18]);
    m_dashboard->setna1(packageADV[19]);
    m_dashboard->setSecinjpulse(packageADV[20]);
    m_dashboard->setna2(packageADV[21]);




//    //qDebug() << "Time passed since last call"<< startTime.msecsTo(QTime::currentTime());
    odometer += ((startTime.msecsTo(QTime::currentTime())) * ((packageADV[16]) / 3600000)); // Odometer
    m_dashboard->setOdo(odometer);
    startTime.restart(); //(QTime::currentTime())
//    //qDebug() << "Odometer"<< odometer;


    }
    // Nissan and Subaru
    if (Model == 2)
    {
    fc_adv_info_t2* info=reinterpret_cast<fc_adv_info_t2*>(serialdata.data());

    packageADV2[0] = info->RPM;
    packageADV2[1] = mul[1] * info->EngLoad + add[1];
    packageADV2[2] = mul[2] * info->MAF1V + add[2];
    packageADV2[3] = mul[3] * info->MAF2V + add[3];
    packageADV2[4] = mul[4] * info->injms + add[4];
    packageADV2[5] = mul[5] * info->Inj + add[5];
    packageADV2[6] = mul[6] * info->Ign + add[6];
    packageADV2[7] = mul[7] * info->Dwell + add[7];
    packageADV2[8] = mul[8] * info->BoostPres + add[8];
    if (packageADV2[8] >= 0x8000)
        packageADV2[8] = (packageADV[8] - 0x8000) * 0.01;
    else
        packageADV2[8] = (1.0 / 2560 + 0.001) * packageADV[8];
    packageADV2[9] = mul[9] * info->BoostDuty + add[9];
    packageADV2[10] = info->Watertemp -80;
    packageADV2[11] = info->Intaketemp -80;
    packageADV2[12] = mul[12] * info->Knock + add[12];
    packageADV2[13] = mul[13] * info->BatteryV + add[13];
    packageADV2[14] = mul[14] * info->Speed + add[14];
//    packageADV2[14] *= speed_correction;
//    previousSpeed_kph[buf_currentIndex] = packageADV[14];
    packageADV2[15] = mul[15] * info->MAFactivity + add[15];
    packageADV2[16] = mul[16] * info->O2volt + add[16];
    packageADV2[17] = mul[17] * info->O2volt_2 + add[17];
    packageADV2[18] = mul[18] * info->ThrottleV + add[18];
    packageADV2[19] = mul[19] * info->na1 + add[19];
    packageADV2[20] = 0;
    packageADV2[21] = 0;
 //qDebug() << "Advanced 2";
    m_dashboard->setRevs(packageADV2[0]);
    m_dashboard->setEngLoad(packageADV2[1]);
    m_dashboard->setMAF1V(packageADV2[2]);
    m_dashboard->setMAF2V(packageADV2[3]);
    m_dashboard->setinjms(packageADV2[4]);
    m_dashboard->setInj(packageADV2[5]);
    m_dashboard->setIgn(packageADV2[6]);
    m_dashboard->setDwell(packageADV2[7]);
    m_dashboard->setBoostPres(packageADV2[8]);
    m_dashboard->setBoostDuty(packageADV2[9]);
    m_dashboard->setWatertemp(packageADV2[10]);
    m_dashboard->setIntaketemp(packageADV2[11]);
    m_dashboard->setKnock(packageADV2[12]);
    m_dashboard->setBatteryV(packageADV2[13]);
    m_dashboard->setSpeed(packageADV2[14]);
    m_dashboard->setMAFactivity(packageADV2[15]);
    m_dashboard->setO2volt(packageADV2[16]);
    m_dashboard->setO2volt_2(packageADV2[17]);
    m_dashboard->setO2volt(packageADV2[18]);
    m_dashboard->setThrottleV(packageADV2[19]);

    }

    if (Model == 3)
    {
        fc_adv_info_t3* info=reinterpret_cast<fc_adv_info_t3*>(serialdata.data());

        packageADV3[0] = mul[0] * info->RPM3 + add[0];
        //previousRev_rpm[buf_currentIndex] = packageADV[0];
        packageADV3[1] = info->Intakepress3;
        packageADV3[2] = info->PressureV3 * 0.001;
        packageADV3[3] = info->ThrottleV3 * 0.001;
        packageADV3[4] = info->Primaryinp3;
        packageADV3[5] = info->Fuelc3;
        packageADV3[6] = info->Ign3;
        packageADV3[7] = info->Dwell3;
        packageADV3[8] = -760 + info->BoostPres3;
/*
        if (packageADV3[8] >= 0x8000)
            packageADV3[8] = (packageADV3[8] - 0x8000) * 0.01;
        else
            packageADV3[8] = (1.0 / 2560 + 0.001) * packageADV3[8];
*/
        packageADV3[9] = mul[9] * info->BoostDuty3 + add[9];
        packageADV3[10] = info->Watertemp3 -80;
        packageADV3[11] = info->Intaketemp3 -80;
        packageADV3[12] = info->Knock3;
        packageADV3[13] = info->BatteryV3 *0.1;
        packageADV3[14] = mul[14] * info->Speed3 + add[14];
       // packageADV3[14] *= speed_correction;
        //previousSpeed_kph[buf_currentIndex] = packageADV[14];
//        packageADV3[15] = mul[15] * info->Iscvduty + add[15];
        packageADV3[16] = mul[16] * info->O2volt3 + add[16];
//        packageADV3[17] = mul[17] * info->SuctionAirTemp + add[17];
//        packageADV3[18] = mul[18] * info->ThrottleV_2 + add[18];
        packageADV3[19] = mul[19] * info->na13 + add[19];
        packageADV3[20] = 0;
        packageADV3[21] = 0;

 //qDebug() << "Advanced 3";
    m_dashboard->setRevs(packageADV3[0]); //correct
    m_dashboard->setIntakepress(packageADV3[1]); //correct
    m_dashboard->setPressureV(packageADV3[2]); //correct
    m_dashboard->setThrottleV(packageADV3[3]); //correct
    m_dashboard->setPrimaryinp(packageADV3[4]); //correct
    m_dashboard->setFuelc(packageADV3[5]); //correct
    m_dashboard->setLeadingign(packageADV3[6]);
    m_dashboard->setTrailingign(packageADV3[7]);
    m_dashboard->setpim(packageADV3[8]);
    m_dashboard->setWatertemp(packageADV3[10]);  //correct
    m_dashboard->setIntaketemp(packageADV3[11]); //verified
    m_dashboard->setKnock(packageADV3[12]); //correct
    m_dashboard->setBatteryV(packageADV3[13]); //correct
    m_dashboard->setSpeed(packageADV3[14]); //correct
  //  m_dashboard->setIscvduty(packageADV3[17]);
  //  m_dashboard->setO2volt(packageADV3[18]);
  //  m_dashboard->setna1(packageADV3[19]);
  //  m_dashboard->setSecinjpulse(packageADV3[20]);
  //  m_dashboard->setna2(packageADV3[21]);
 //qDebug() << "0"<< packageADV3[0];
    //qDebug() << "1"<< packageADV3[1];
  //qDebug() << "2"<< packageADV3[2];
  //qDebug() << "3"<< packageADV3[3];
  //qDebug() << "4"<< packageADV3[4];
  //qDebug() << "5"<< packageADV3[5];
  //qDebug() << "6"<< packageADV3[6];
  //qDebug() << "7"<< packageADV3[7];
  //qDebug() << "8"<< packageADV3[8];
  //qDebug() << "9"<< packageADV3[9];
  //qDebug() << "10"<< packageADV3[10];
  //qDebug() << "11"<< packageADV3[11];
  //qDebug() << "12"<< packageADV3[12];
  //qDebug() << "13"<< packageADV3[13];
  //qDebug() << "14"<< packageADV3[14];
  //qDebug() << "15"<< packageADV3[15];
  //qDebug() << "16"<< packageADV3[16];
  //qDebug() << "17"<< packageADV3[17];
  //qDebug() << "18"<< packageADV3[18];
  //qDebug() << "19"<< packageADV3[19];
  //qDebug() << "20"<< packageADV3[20];
  //qDebug() << "22"<< packageADV3[21];

    }

}



void Decoder::decodeSensor(QByteArray serialdata)
{
    fc_sens_info_t* info=reinterpret_cast<fc_sens_info_t*>(serialdata.data());

    packageSens[0] = info->sens1 * 0.01;
    packageSens[1] = info->sens2 * 0.01;
    packageSens[2] = info->sens3 * 0.01;
    packageSens[3] = info->sens4 * 0.01;
    packageSens[4] = info->sens5 * 0.01;
    packageSens[5] = info->sens6 * 0.01;
    packageSens[6] = info->sens7 * 0.01;
    packageSens[7] = info->sens8 * 0.01;

    QBitArray flagArray(16);
    for (int i=0; i<16; i++)
        flagArray.setBit(i, info->flags>>i & 1);


    m_dashboard->setsens1(packageSens[0]);
    m_dashboard->setsens2(packageSens[1]);
    m_dashboard->setsens3(packageSens[2]);
    m_dashboard->setsens4(packageSens[3]);
    m_dashboard->setsens5(packageSens[4]);
    m_dashboard->setsens6(packageSens[5]);
    m_dashboard->setsens7(packageSens[6]);
    m_dashboard->setsens8(packageSens[7]);

    //Bit Flags for Sensors
    m_dashboard->setFlag1(flagArray[0]);
    m_dashboard->setFlag2(flagArray[1]);
    m_dashboard->setFlag3(flagArray[2]);
    m_dashboard->setFlag4(flagArray[3]);
    m_dashboard->setFlag5(flagArray[4]);
    m_dashboard->setFlag6(flagArray[5]);
    m_dashboard->setFlag7(flagArray[6]);
    m_dashboard->setFlag8(flagArray[7]);
    m_dashboard->setFlag9(flagArray[8]);
    m_dashboard->setFlag10(flagArray[9]);
    m_dashboard->setFlag11(flagArray[10]);
    m_dashboard->setFlag12(flagArray[11]);
    m_dashboard->setFlag13(flagArray[12]);
    m_dashboard->setFlag14(flagArray[13]);
    m_dashboard->setFlag15(flagArray[14]);
    m_dashboard->setFlag16(flagArray[15]);


    if (Loggerstat ==1 && Model >= 1)
    {
    QString fileName = Logfile;
    QFile mFile(fileName);
    if(!mFile.open(QFile::Append | QFile::Text)){
        //qDebug() << "Could not open file for writing";
    }
    QTextStream out(&mFile);
    out.setFieldAlignment(QTextStream::AlignLeft);
    out.setFieldWidth(8);
            out << (loggerStartTime.msecsTo(QTime::currentTime()))<< packageBasic[0]<< packageBasic[1]<< packageBasic[2] << packageBasic[3] << packageBasic[4] << packageBasic[5] << packageBasic[6]<< packageBasic[7]<< packageBasic[8]
                << packageBasic[9] << packageSens[0] << packageSens[1] << packageSens[2] << packageSens[3] << packageSens[4] << packageSens[5] << packageSens[6] << packageSens[7]
                << flagArray[0] << flagArray[1] << flagArray[2] << flagArray[3] << flagArray[4] << flagArray[5] << flagArray[6] << flagArray[7] << flagArray[8] << flagArray[9] << flagArray[10] << flagArray[11] << flagArray[12] << flagArray[13] << flagArray[14] << flagArray[15]
                << AN1AN2calc << AN3AN4calc
               // << packageAux2[0] << packageAux2[1] << packageAux2[2] << packageAux2[3]<< packageAux2[4] << packageAux2[5] << packageAux2[6] << packageAux2[7]
                << packageMap[0] << packageMap[1] << packageADV[0] << packageADV[1] << packageADV[2] << packageADV[3] << packageADV[4] << packageADV[5] << packageADV[6] << packageADV[7]
                << packageADV[8] << packageADV[9] << packageADV[10] << packageADV[11] << packageADV[12] << packageADV[13] << packageADV[14] << packageADV[15] << packageADV[16] << packageADV[17] << packageADV[18]

                << packageADV[19] << packageADV[20] << packageADV[21] <<m_dashboard->gpsTime() << qSetFieldWidth(0) << endl <<qSetFieldWidth(8);
    mFile.close();
    }


}

void Decoder::decodeAux(QByteArray serialdata)
{
    fc_aux_info_t* info=reinterpret_cast<fc_aux_info_t*>(serialdata.data());


    packageAux[0] = mul[29] * info->AN1 + add[29];
    packageAux[1] = mul[30] * info->AN2 + add[30];
    packageAux[2] = mul[31] * info->AN3 + add[31];
    packageAux[3] = mul[32] * info->AN4 + add[32];

    //Analog1
    AN1AN2calc = ((((auxval2-auxval1)/5) * (packageAux[0] - packageAux[1])) + auxval1);
    AN3AN4calc = ((((auxval4-auxval3)/5) * (packageAux[2] - packageAux[3])) + auxval3);
    m_dashboard->setauxcalc1(AN1AN2calc);
    //Analog2
    m_dashboard->setauxcalc2(AN3AN4calc);

}

void Decoder::decodeAux2(QByteArray serialdata)
{
    fc_aux2_info_t* info=reinterpret_cast<fc_aux2_info_t*>(serialdata.data());


    packageAux2[0] = mul[29] * info->AN1 + add[29];
    packageAux2[1] = mul[30] * info->AN2 + add[30];
    packageAux2[2] = mul[31] * info->AN3 + add[31];
    packageAux2[3] = mul[32] * info->AN4 + add[32];
    packageAux2[4] = mul[29] * info->AN5 + add[29];
    packageAux2[5] = mul[30] * info->AN6 + add[30];
    packageAux2[6] = mul[31] * info->AN7 + add[31];
    packageAux2[7] = mul[32] * info->AN8 + add[32];

    AN1AN2calc =((((auxval2-auxval1)/5) * (packageAux2[0] - packageAux2[1])) + auxval1);
    AN3AN4calc =((((auxval3-auxval2)/5) * (packageAux2[2] - packageAux2[3])) + auxval3);


    //Analog1
    m_dashboard->setauxcalc1(AN1AN2calc);
    //Analog2
    m_dashboard->setauxcalc2(AN3AN4calc);

}
void Decoder::decodeMap(QByteArray serialdata)
{
    fc_map_info_t* info=reinterpret_cast<fc_map_info_t*>(serialdata.data());

    packageMap[0] = mul[0] * info->Map_N + add[0];
    packageMap[1] = mul[0] * info->Map_P + add[0];

    //    ui->txtMapConsole->clear();

    //    ui->txtMapConsole->append(map[66] + " " + QString::number(packageMap[0]));
    //    ui->txtMapConsole->append(map[67] + " " + QString::number(packageMap[1]));
}
void Decoder::decodeBasic(QByteArray serialdata)
{
    fc_Basic_info_t* info=reinterpret_cast<fc_Basic_info_t*>(serialdata.data());

    int Boost;

    packageBasic[0] = mul[15] * info->Basic_Injduty + add[0];
    packageBasic[1] = mul[0] * info->Basic_IGL + add[6];
    packageBasic[2] = mul[0] * info->Basic_IGT + add[6];
    packageBasic[3] = mul[0] * info->Basic_RPM + add[0];
    if (units == 0)
    {
    packageBasic[4] = mul[0] * info->Basic_KPH + add[0];
    }
    if (units == 1)
    {
    packageBasic[4] = (mul[0] * info->Basic_KPH + add[0]) * 0.621371;
    }
    packageBasic[5] = mul[0] * info->Basic_Boost -760;
    packageBasic[6] = mul[0] * info->Basic_Knock + add[0];
    if (units == 0)
    {
    packageBasic[7] = mul[0] * info->Basic_Watert + add[8];
    }
    if (units == 1)
    {
        packageBasic[7] = ((mul[0] * info->Basic_Watert + add[8])*1.8) + 32 ;
    }
    if (units == 0)
    {
    packageBasic[8] = mul[0] * info->Basic_Airt + add[8];
    }
    if (units == 1)
    {
    packageBasic[8] = ((mul[0] * info->Basic_Airt + add[8]) *1.8) + 32 ;
    }
    packageBasic[9] = mul[15] * info->Basic_BattV + add[0];
    if (units == 0)
    {
    if (packageBasic[5] >= 0) // while boost pressure is positive multiply by 0.01 to show kg/cm2
    {
        Boost = packageBasic[5] *0.01;
    }
    else Boost = packageBasic[5]; // while boost pressure is negative show pressure in mmhg
    }
    if (units == 1)
    {
    if (packageBasic[5] >= 0) // while boost pressure is positive multiply by 0.01 to show PSI
    {
        Boost = packageBasic[5] * 0.142233;
    }
    else Boost = packageBasic[5] * 0.039370079; // while boost pressure is negative show pressure in inhg
    }

   // m_dashboard->setInjDuty(packageBasic[0]);
    m_dashboard->setLeadingign(packageBasic[1]);
    m_dashboard->setTrailingign(packageBasic[2]);
    m_dashboard->setRevs(packageBasic[3]);
    m_dashboard->setSpeed(packageBasic[4]);
    m_dashboard->setpim(Boost);
    m_dashboard->setKnock(packageBasic[6]);
    m_dashboard->setWatertemp(packageBasic[7]);
    m_dashboard->setIntaketemp(packageBasic[8]);
    m_dashboard->setBatteryV(packageBasic[9]);

}

void Decoder::decodeRevIdle(QByteArray serialdata)
{
    fc_RevIdle_info_t* info=reinterpret_cast<fc_RevIdle_info_t*>(serialdata.data());

    packageRevIdle[0] = info->RevLIM;
    packageRevIdle[1] = info->FCAE;
    packageRevIdle[2] = info->FCEL;
    packageRevIdle[3] = info->FCAC;
    packageRevIdle[4] = info->IdleAE;
    packageRevIdle[5] = info->IdleEL;
    packageRevIdle[6] = info->IdleAC;

    //    ui->lineRevlim->setText (QString::number(packageRevIdle[0]));
    //    ui->lineFCAE->setText (QString::number(packageRevIdle[1]));
    //    ui->lineFCEL->setText (QString::number(packageRevIdle[2]));
    //    ui->lineFCAC->setText (QString::number(packageRevIdle[3]));
    //    ui->lineIdleAE->setText (QString::number(packageRevIdle[4]));
    //    ui->lineIdleEL->setText (QString::number(packageRevIdle[5]));
    //    ui->lineIdleAC->setText (QString::number(packageRevIdle[6]));
}

void Decoder::decodeTurboTrans(QByteArray serialdata)
{
    fc_TurboTrans_info_t* info=reinterpret_cast<fc_TurboTrans_info_t*>(serialdata.data());

    packageTurboTrans[0] = mul[35] * info->TPS01;
    packageTurboTrans[1] = mul[35] * info->TPS02;
    packageTurboTrans[2] = mul[35] * info->TPS03;
    packageTurboTrans[3] = mul[36] * info->LowRPM1;
    packageTurboTrans[4] = mul[36] * info->LowRPM2;
    packageTurboTrans[5] = mul[36] * info->LowRPM3;
    packageTurboTrans[6] = mul[36] * info->HighRPM1;
    packageTurboTrans[7] = mul[36] * info->HighRPM2;
    packageTurboTrans[8] = mul[36] * info->HighRPM3;

    //    ui->lineTPS01->setText (QString::number(packageTurboTrans[0]));
    //    ui->lineTPS02->setText (QString::number(packageTurboTrans[1]));
    //    ui->lineTPS03->setText (QString::number(packageTurboTrans[2]));
    //    ui->lineLowRPM1->setText (QString::number(packageTurboTrans[3]));
    //    ui->lineLowRPM2->setText (QString::number(packageTurboTrans[4]));
    //    ui->lineLowRPM3->setText (QString::number(packageTurboTrans[5]));
    //    ui->lineHighRPM1->setText (QString::number(packageTurboTrans[6]));
    //    ui->lineHighRPM2->setText (QString::number(packageTurboTrans[7]));
    //    ui->lineHighRPM3->setText (QString::number(packageTurboTrans[8]));
}

void Decoder::decodeLeadIgn(QByteArray serialdata, quint8 column)
{
    //Fill Table view with Leading ignition Table1
/*

    quint8 columnLimit = column + 5;
    quint8 countarray = 1; //counter for the position in the array
    for (column; column < columnLimit; column++) //increases the counter column by 1 until column 5
    {

        for (int row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
        {
            if(countarray <= 102){countarray++;} //Increases the counter "countarray till 100"
            //                    QStandardItem *value = new QStandardItem(QString::number(serialdata[countarray]-25)); //insert the array here and use count array for position in array
            //                    model->setItem(row,column,value);
            //                    ui->tableLeadIgn->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableLeadIgn->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableLeadIgn->setModel(model);
        }
    }
*/
}


//Trailing Ignition Map

void Decoder::decodeTrailIgn(QByteArray serialdata, quint8 column)
{
    //Fill Table view with Trailing ignition Table1
/*
    quint8 columnLimit = column + 5;
    quint8 countarray = 1; //counter for the position in the array
    for (column; column < columnLimit; column++) //increases the counter column by 1 until column 5
    {
        for (quint8 row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
        {
            if(countarray <= 102){countarray++;} //Increases the counter "countarray till 100"
            //                    QStandardItem *value = new QStandardItem(QString::number(serialdata[countarray]-25)); //insert the array here and use count array for position in array
            //                    model1->setItem(row,column,value);
            //                    ui->tableTrailIgn->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableTrailIgn->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableTrailIgn->setModel(model1);
        }
    }
*/
}

//Injector correction

void Decoder::decodeInjcorr(QByteArray serialdata, quint8 column)
{
    //Fill Table view with Injector correction Table1
 /*
    quint8 columnLimit = column + 5;

    quint8 countarray = 1; //counter for the position in the array
    for (column; column < columnLimit; column++) //increases the counter column by 1 until column 5
    {
        for (quint8 row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
        {
            if(countarray <= 102){countarray++;} //Increases the counter "countarray till 100"
            //                    QStandardItem *value = new QStandardItem(QString::number((serialdata[countarray]-128)*mul[40])); //insert the array here and use count array for position in array
            //                    model2->setItem(row,column,value);
            //                    ui->tableInjCorr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableInjCorr->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableInjCorr->setModel(model2);
        }
    }
 */
}

void Decoder::decodeFuelBase(QByteArray serialdata, quint8 package)
{
    quint8 index = 0;
    ////qDebug() << "add package!";

    for(quint8 index = 2; index < 102; index++)
    {
        fullFuelBase.append(serialdata[index]);
    }

    if(package == 7)
    {
        fc_fullFuelBase_info_t* info=reinterpret_cast<fc_fullFuelBase_info_t*>(fullFuelBase.data());

        for (quint8 column = 0; column <= 20; column++) //increases the counter column by 1 until column 5
        {
            for (quint8 row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
            {
//                ui->tableFuelBase->setItem(row, column, new QTableWidgetItem(QString::number(info->fuelBase[index])));
                index++;
               // //qDebug() << row << " : " << column;
            }
        }
        ////qDebug() << fullFuelBase.length();
    }
}

void Decoder::decodeBoostCont(QByteArray serialdata)
{
    fc_BoostCont_info_t* info=reinterpret_cast<fc_BoostCont_info_t*>(serialdata.data());

    packageBoostControl[0] = info->Setting1;
    packageBoostControl[1] = info->Setting2;
    packageBoostControl[2] = info->Setting3;
    packageBoostControl[3] = mul[37] * info->BoostPrimary1;
    packageBoostControl[4] = mul[37] * info->BoostSecondary1;
    packageBoostControl[5] = mul[37] * info->BoostPrimary2;
    packageBoostControl[6] = mul[37] * info->BoostSecondary2;
    packageBoostControl[7] = info->DutyPrimary1;
    packageBoostControl[8] = info->DutySecondary1;
    packageBoostControl[9] = info->DutyPrimary2;
    packageBoostControl[10] = info->DutySecondary2;

//    ui->lineBoostPri1->setText (QString::number(packageBoostControl[3]));
//    ui->lineBoostSec1->setText (QString::number(packageBoostControl[4]));
//    ui->lineBoostPri2->setText (QString::number(packageBoostControl[5]));
//    ui->lineBoostSec2->setText (QString::number(packageBoostControl[6]));
//    ui->lineBoostDutyPri1->setText (QString::number(packageBoostControl[7]));
//    ui->lineBoostDutySec1->setText (QString::number(packageBoostControl[8]));
//    ui->lineBoostDutyPri2->setText (QString::number(packageBoostControl[9]));
//    ui->lineBoostDutySec2->setText (QString::number(packageBoostControl[10]));

}
void Decoder::decodeInjOverlap(QByteArray serialdata)
{
    fc_InjOverlap_info_t* info=reinterpret_cast<fc_InjOverlap_info_t*>(serialdata.data());

    packageInjOverlap[0] = mul[39] * info->InjOvBoost1;
    packageInjOverlap[1] = info->lineInjOvSet1;
    packageInjOverlap[2] = mul[39] * info->InjOvBoost2;
    packageInjOverlap[3] = info->lineInjOvSet2;
    packageInjOverlap[4] = mul[39] * info->InjOvBoost3;
    packageInjOverlap[5] = info->lineInjOvSet3;


//    ui->lineInjOvBoost1->setText (QString::number(packageInjOverlap[0]));
//    ui->lineInjOvSet1->setText (QString::number(packageInjOverlap[1]));
//    ui->lineInjOvBoost2->setText (QString::number(packageInjOverlap[2]));
//    ui->lineInjOvSet2->setText (QString::number(packageInjOverlap[3]));
//    ui->lineInjOvBoost3->setText (QString::number(packageInjOverlap[4]));
//    ui->lineInjOvSet3->setText (QString::number(packageInjOverlap[5]));


}

void Decoder::decodeVersion(QByteArray serialdata)
{
    //    ui->lineVersion->setText (QString(serialdata).mid(2,5));
}
void Decoder::decodeInit(QByteArray serialdata)
{
    QString Modelname = QString(serialdata).mid(2,8);
    //Mazda
    if (Modelname == "13B-REW ")
    {
        Model =1;
    }

    //Nissan
    if (Modelname == "RB20DET " || Modelname == "RB26DETT" || Modelname == "SR20DET1" || Modelname == "CA18DET " || Modelname == "RB25DET ")
    {
        Model =2;
    }

    //Toyota
    if (Modelname == "4E-FTE2 " || Modelname == "1JZ-GTE "||Modelname == "1JZ-GTE3"|| Modelname == "1ZZ-FRE " || Modelname == "2jZ-GTE1" || Modelname == "2ZZ-GE  " || Modelname == "3S-GE   " || Modelname == "3S-GTE3 " || Modelname == " 3S-GTE " || Modelname == "3E-FTE2 ")
    {
        Model =3;
    }

/*
       //Subaru
       if ((QString(serialdata).mid(2,8)== "")
          {
           Model =4;
       }
       //Honda
       if ((QString(serialdata).mid(2,8)==== "EJ20K   ")
          {
           Model =5;
       }
       //Mitsubishi
       if ((QString(serialdata).mid(2,8)==== "")
          {
           Model =6;
       }

*/
//    ui->linePlatform->setText (QString(serialdata).mid(2,8));
    //qDebug() << "Model ="<<Model;
    //qDebug() << "Model name ="<<(QString(serialdata).mid(2,8));
    m_dashboard->setPlatform(QString(serialdata).mid(2,8));
}

void Decoder::decodeSensorStrings(QByteArray serialdata)
{

    m_dashboard->setSensorString1 (QString(serialdata).mid(2,4));
    m_dashboard->setSensorString2 (QString(serialdata).mid(6,4));
    m_dashboard->setSensorString3 (QString(serialdata).mid(10,4));
    m_dashboard->setSensorString4 (QString(serialdata).mid(14,4));
    m_dashboard->setSensorString5 (QString(serialdata).mid(18,4));
    m_dashboard->setSensorString6 (QString(serialdata).mid(22,4));
    m_dashboard->setSensorString7 (QString(serialdata).mid(26,4));
    m_dashboard->setSensorString8 (QString(serialdata).mid(30,4));


    m_dashboard->setFlagString1 (QString(serialdata).mid(34,3));
    m_dashboard->setFlagString2 (QString(serialdata).mid(37,3));
    m_dashboard->setFlagString3 (QString(serialdata).mid(40,3));
    m_dashboard->setFlagString4 (QString(serialdata).mid(43,3));
    m_dashboard->setFlagString5 (QString(serialdata).mid(46,3));
    m_dashboard->setFlagString6 (QString(serialdata).mid(49,3));
    m_dashboard->setFlagString7 (QString(serialdata).mid(52,3));
    m_dashboard->setFlagString8 (QString(serialdata).mid(55,3));
    m_dashboard->setFlagString9 (QString(serialdata).mid(58,3));
    m_dashboard->setFlagString10 (QString(serialdata).mid(61,3));
    m_dashboard->setFlagString11 (QString(serialdata).mid(64,3));
    m_dashboard->setFlagString12 (QString(serialdata).mid(67,3));
    m_dashboard->setFlagString13 (QString(serialdata).mid(70,3));
    m_dashboard->setFlagString14 (QString(serialdata).mid(73,3));
    m_dashboard->setFlagString15 (QString(serialdata).mid(76,3));
    m_dashboard->setFlagString16 (QString(serialdata).mid(79,3));
}


void Decoder::decodeInjPriLagvsBattV(QByteArray serialdata)
{
    fc_InjPriLagvsBattV_info_t* info=reinterpret_cast<fc_InjPriLagvsBattV_info_t*>(serialdata.data());

    packageInjPriLagvsBattV[0] = mul[38] * info->InjPriLag16V;
    packageInjPriLagvsBattV[1] = mul[38] * info->InjPriLag14V;
    packageInjPriLagvsBattV[2] = mul[38] * info->InjPriLag12V;
    packageInjPriLagvsBattV[3] = mul[38] * info->InjPriLag10V;
    packageInjPriLagvsBattV[4] = mul[38] * info->InjPriLag8V;
    packageInjPriLagvsBattV[5] = mul[38] * info->InjPriLag6V;

    //    ui->lineInjPrLag16V->setText (QString::number(packageInjPriLagvsBattV[0]));
    //    ui->lineInjPrLag14V->setText (QString::number(packageInjPriLagvsBattV[1]));
    //    ui->lineInjPrLag12V->setText (QString::number(packageInjPriLagvsBattV[2]));
    //    ui->lineInjPrLag10V->setText (QString::number(packageInjPriLagvsBattV[3]));
//    ui->lineInjPrLag8V->setText (QString::number(packageInjPriLagvsBattV[4]));
//    ui->lineInjPrLag6V->setText (QString::number(packageInjPriLagvsBattV[5]));
}
void Decoder::decodeInjScLagvsBattV(QByteArray serialdata)
{
    fc_InjScLagvsBattV_info_t* info=reinterpret_cast<fc_InjScLagvsBattV_info_t*>(serialdata.data());

    packageInjScLagvsBattV[0] = mul[38] * info->InjScLag16V;
    packageInjScLagvsBattV[1] = mul[38] * info->InjScLag14V;
    packageInjScLagvsBattV[2] = mul[38] * info->InjScLag12V;
    packageInjScLagvsBattV[3] = mul[38] * info->InjScLag10V;
    packageInjScLagvsBattV[4] = mul[38] * info->InjScLag8V;
    packageInjScLagvsBattV[5] = mul[38] * info->InjScLag6V;

//    ui->lineInjScLag16V->setText (QString::number(packageInjScLagvsBattV[0]));
//    ui->lineInjScLag14V->setText (QString::number(packageInjScLagvsBattV[1]));
//    ui->lineInjScLag12V->setText (QString::number(packageInjScLagvsBattV[2]));
//    ui->lineInjScLag10V->setText (QString::number(packageInjScLagvsBattV[3]));
//    ui->lineInjScLag8V->setText (QString::number(packageInjScLagvsBattV[4]));
//    ui->lineInjScLag6V->setText (QString::number(packageInjScLagvsBattV[5]));
}
void Decoder::decodeFuelInjectors(QByteArray serialdata)
{
    fc_FuelInjectors_info_t* info=reinterpret_cast<fc_FuelInjectors_info_t*>(serialdata.data());

    packageFuelInjectors[1] = mul[41] * info->frontpulse * mul[42];
    packageFuelInjectors[3] = mul[41] * info->rearpulse * mul[42];
    packageFuelInjectors[4] = 4 * info->frntprilag;//(multiply by 0.004)
    packageFuelInjectors[6] = 4 * info->frntseclag;//(multiply by 0.004)
    packageFuelInjectors[8] = 4 *info->rearprilag;//(multiply by 0.004)
    packageFuelInjectors[10] = 4 *info->rearseclag;//(multiply by 0.004)
    packageFuelInjectors[12] = info->prinjsize;
    packageFuelInjectors[13] = info->secinjsize;
    packageFuelInjectors[14] = info->prisectransprc /10; // divide by 10 to get %
    packageFuelInjectors[15] = info->prisectransms /10; //(multiply by 0.004)


//    ui->linefrontpulse->setText (QString::number(packageFuelInjectors[1]));
//    ui->linerearpulse->setText (QString::number(packageFuelInjectors[3]));
//    ui->linefrntprilag->setText (QString::number(packageFuelInjectors[4]));
//    ui->linefrntseclag->setText (QString::number(packageFuelInjectors[6]));
//    ui->linerearprilag->setText (QString::number(packageFuelInjectors[8]));
//    ui->linerearseclag->setText (QString::number(packageFuelInjectors[10]));
//    ui->linePriInjSize->setText (QString::number(packageFuelInjectors[12]));
//    ui->lineSecInjSize->setText (QString::number(packageFuelInjectors[13]));
//    ui->linePriSecTransPrc->setText (QString::number(packageFuelInjectors[14]));
//    ui->linePriSecTransms->setText (QString::number(packageFuelInjectors[15]));
}

// Adaptronic Select ECU

void Decoder::decodeAdaptronic(QModbusDataUnit unit)
{

    qreal realBoost;
    int Boostconv;


 if (units == 0)
 {
     //qDebug() << "i am at 0 " ;
    m_dashboard->setSpeed(unit.value(10)); // <-This is for the "main" speedo KMH
 }
 if (units == 1)
 {
    m_dashboard->setSpeed(unit.value(10)*0.621371); // <-This is for the "main" speedo in MPH
 }
    m_dashboard->setRevs(unit.value(0));
    m_dashboard->setMAP(unit.value(1));
    if (units == 0)
    {
    m_dashboard->setIntaketemp(unit.value(2));
    }
    if (units == 1)
    {
    m_dashboard->setIntaketemp(unit.value(2)* 1.8 + 32);
    }
    if (units == 0)
    {
    m_dashboard->setWatertemp(unit.value(3));
    }
    if (units == 1)
    {
    m_dashboard->setWatertemp(unit.value(3)* 1.8 + 32);
    }
    if (units == 0)
    {
    m_dashboard->setAUXT(unit.value(4));
    }
    if (units == 1)
    {
    m_dashboard->setAUXT(unit.value(4)* 1.8 + 32);
    }
    m_dashboard->setauxcalc1(unit.value(5)/2570.00);
    m_dashboard->setKnock(unit.value(6)/256);
    m_dashboard->setTPS(unit.value(7));
    m_dashboard->setIdleValue(unit.value(8));
    m_dashboard->setBatteryV(unit.value(9)/10);
    if (units == 0)
    {
    m_dashboard->setMVSS(unit.value(10));
    }
    if (units == 1)
    {
    m_dashboard->setMVSS(unit.value(10)*0.621371);
    }
    if (units == 0)
    {
    m_dashboard->setSVSS(unit.value(11));
    }
    if (units == 1)
    {
    m_dashboard->setSVSS(unit.value(11)*0.621371);
    }
    m_dashboard->setInj1((unit.value(12)/3)*2);
    m_dashboard->setInj2((unit.value(13)/3)*2);
    m_dashboard->setInj3((unit.value(14)/3)*2);
    m_dashboard->setInj4((unit.value(15)/3)*2);
    m_dashboard->setIgn1((unit.value(16)/5));
    m_dashboard->setIgn2((unit.value(17)/5));
    m_dashboard->setIgn3((unit.value(18)/5));
    m_dashboard->setIgn4((unit.value(19)/5));
    m_dashboard->setTRIM((unit.value(20)));
    //m_dashboard->setpim(packageAdaptronic[1]);
    //m_dashboard->setairt(packageAdaptronic[2]);
    //m_dashboard->setWatertemp(packageAdaptronic[3]);

    /*
    m_dashboard->setRevs(packageADV[0]);
    m_dashboard->setIntakepress(packageADV[1]);
    m_dashboard->setPressureV(packageADV[2]);
    m_dashboard->setThrottleV(packageADV[3]);
    m_dashboard->setPrimaryinp(packageADV[4]);
    m_dashboard->setFuelc(packageADV[5]);
    m_dashboard->setLeadingign(packageADV[6]);
    m_dashboard->setTrailingign(packageADV[7]);
    m_dashboard->setFueltemp(packageADV[8]);
    m_dashboard->setMoilp(packageADV[9]);
    m_dashboard->setBoosttp(packageADV[10]);
    m_dashboard->setBoostwg(packageADV[11]);
    m_dashboard->setWatertemp(packageADV[12]);
    m_dashboard->setIntaketemp(packageADV[13]);
    m_dashboard->setKnock(packageADV[14]);
    m_dashboard->setBatteryV(packageADV[15]);
    m_dashboard->setSpeed(packageADV[16]);
    m_dashboard->setIscvduty(packageADV[17]);
    m_dashboard->setO2volt(packageADV[18]);
    m_dashboard->setna1(packageADV[19]);
    m_dashboard->setSecinjpulse(packageADV[20]);
    m_dashboard->setna2(packageADV[21]);
*/


    // Convert absolute pressure in KPA to relative pressure mmhg/Kg/cm2

        if ((unit.value(1)) > 103) // while boost pressure is positive multiply by 0.01 to show kg/cm2
        {
            Boostconv = ((unit.value(1))-103) ;
            realBoost = Boostconv* 0.01;
            //qDebug() << realBoost;
        }
        else if ((unit.value(1)) < 103) // while boost pressure is negative  multiply by 0.01 to show kg/cm2
        {
            Boostconv = ((unit.value(1))-103) * 7.50061561303;
            realBoost = Boostconv;

        }


    m_dashboard->setpim(realBoost);


    //Datalogger Adaptronic Comma seperated Text File for easy import to Excel
    if (Loggerstat ==1)
    {
    QString fileName = Logfile;
    //qDebug() << Logfile;
    QFile mFile(fileName);
    if(!mFile.open(QFile::Append | QFile::Text)){
        //qDebug() << "Could not open Adaptronic Loggerfile for writing";
    }
    QTextStream out(&mFile);
    out << (loggerStartTime.msecsTo(QTime::currentTime()))<< "," << unit.value(0) << ","
        << unit.value(1) << "," << unit.value(2) << "," << unit.value(3) << ","
        << unit.value(4) << "," << (unit.value(5)/2570.00) << "," << (unit.value(6)/256)
        << "," << unit.value(7) << "," << unit.value(8) << "," <<(unit.value(9)/10) << ","
        << unit.value(10) << "," << unit.value(11) << ","<< ((unit.value(12)/3)*2) << ","
        <<((unit.value(13)/3)*2) << "," << ((unit.value(14)/3)*2) << ","
       << ((unit.value(15)/3)*2) << ","<< (unit.value(16)/5) << ","
       << (unit.value(17)/5) << "," << (unit.value(18)/5) << ","
       << (unit.value(19)/5) << "," << unit.value(20)<< "," << endl;

    mFile.close();
}

    emit sig_adaptronicReadFinished();
}

void Decoder::loggerAdaptronic(QString Logfilename)
{
Logfile = Logfilename+".csv";
loggerStartTime.restart();
}

void Decoder::loggerApexi(QString Logfilename)
{
Logfile = Logfilename+".txt";
loggerStartTime.restart();
QString filename = Logfilename + ".txt";
QTime waitforModel = QTime::currentTime();
int timeOut = 10000;

//Waiting until the Model has been Set
while (Model < 1)
{
    if ( waitforModel.msecsTo(QTime::currentTime()) > timeOut ) break;
    Loggerstat = 0;
}

QFile file( filename );
//qDebug() << "Apexi Start Log";
if ( file.open(QIODevice::ReadWrite) )
{
    QTextStream out( &file );
    out.setFieldAlignment(QTextStream::AlignLeft);
    out.setFieldWidth(8);
    if (Model == 1) // FD3S Header
    {
    out << "Time(ms)"<< "InjDuty" << "IGL" << "IGT" << "Rpm" << "Speed"
        << "Boost" << "Knock" << "WtrTemp" << "AirTemp"
        << "BatVolt" << "PIM" << "VTA1" << "VTA2" << "VMOP" << "WTRT"
        << "AIRT" << "FUEL" << "O2S" << "STR" << "A/C" << "PWS" << "NTR"
        << "CLT" << "STP" << "CAT" << "ELD"
        <<"HWL"<<"FPD"<<"FPR"<<"APR"
        <<"PAC"<<"CCN"<<"TCN"<<"PRC"
        << Auxname1 << Auxname2
        <<"MAPN"<<"MAPP"<<"RPM"<<"PIM"<<"PIM  V"
        <<"TPS  V"<<"InjFrPr"<<"Inj+/-"
        <<"IGL"<<"IGT"<<"FuelT"
        <<"Oil"<<"PC%"<<"WG%"<<"WtrT"
        <<"AirT"<<"Knock"<<"BatV"<<"Speed"
        <<"Iscvdty"<<"O2S"<<"(1)"<< "InjFrSc"<<"(2)"<< qSetFieldWidth(0) << endl <<qSetFieldWidth(8);
        out << endl;
    }
    if (Model == 2)
        {
        }
    if (Model == 3)
        {
        }
    if (Model == 4)
        {
        }
    if (Model == 5)
        {
        }
    }
file.close();
Loggerstat = 1;
}



void Decoder::loggerActivationstatus(int loggingstatus)
{
Loggerstat = loggingstatus;
//qDebug() <<"Decoder loggingstatus"<< loggingstatus;
}
void Decoder::calculatorAux(int aux1min,int aux2max,int aux3min,int aux4max,QString Auxunit1,QString Auxunit2)
{
    auxval1 = aux1min;
    auxval2 = aux2max;
    auxval3 = aux3min;
    auxval4 = aux4max;

    Auxname1 = Auxunit1;
    Auxname2 = Auxunit2;



}
void Decoder::decodeDicktator(QByteArray m_dicktatorMsg)
{
    dicktator_info_t* info=reinterpret_cast<dicktator_info_t*>(m_dicktatorMsg.data());
//qDebug() << "decoder Dicktator" <<m_dicktatorMsg.toHex();


        packageDicktator[5] = (info->b5);                //rpm
        if (info->b6 > 0)
        {
        packageDicktator[6] = ((3060 / info->b6) * 25.5);  //rpm
        }
        packageDicktator[7] = (info->b7 + 1);            //rpm
        packageDicktator[14] = info->boost * 0.00305859 - 0.989;     //Relative Boost
        packageDicktator[18] = (info->b18 /16); //Battery Voltage
        packageDicktator[19] = (info->b20 * 25 + info->b19*0.1 ); //TPS
        //qDebug() << "Battery" << packageDicktator[18];

        m_dashboard->setRevs(packageDicktator[6]/packageDicktator[7]);
        m_dashboard->setBatteryV(packageDicktator[18]);
        m_dashboard->setpim(packageDicktator[14]);
        dicktator_info_t parse(const QByteArray &);


}
