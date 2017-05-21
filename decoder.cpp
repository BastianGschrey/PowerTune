/*
  \file decoder.cpp
  \brief Power Tune Power FC related functions
  \author Bastian Gschrey & Markus Ippy
 */

#include "decoder.h"
#include "dashboard.h"
#include "serial.h"

#include <QDebug>
#include <QBitArray>
#include <QModbusDataUnit>

QByteArray serialdata;
QByteArray fullFuelBase;


double mul[80] = FC_INFO_MUL;  // required values for calculation from raw to readable values for Advanced Sensor info
double add[] = FC_INFO_ADD;

static QString map[] = {"rpm", "pim", "pimV",
                        "TPS Voltage", "InjFp ms", "Inj",
                        "IGL", "IGT",
                        "Fuel", "Moilp", "Boosttp",
                        "Boostwg", "Watertemp", "Intaketemp",
                        "Knock", "BatteryV",
                        "Speed", "Iscvduty", "O2volt",
                        "na1", "Secinjpulse", "na2",
                        "AUX1", "AUX2", "AUX3", "AUX4", "AUX5", "AUX6", "AUX7", "AUX8",
                        "Analog1", "Analog2", "Analog3", "Analog4",
                        "Power", "Accel", "GForce", "ForceN", "Gear", "PrimaryInjD", "AccelTimer",
                        "Rec","Sens_PIM","Sens_VTA1","Sens_VTA2","Sens_VMOP","Sens_Wtrt","Sens_Airt",
                        "Sens_Fuel","Sens_O2", "STR", "A/C", "PWS", "NTR", "CLT",
                        "STP", "CAT", "ELD", "HWL", "FPD", "FPR", "APR", "PAC", "CCN", "TCN", "PRC" ,"MAP_N","MAP_P",
                        "Basic_Injduty", "Basic_IGL", "Basic_IGT", "Basic_RPM", "Basic_KPH", "Basic_Boost", "Basic_Knock", "Basic_Watert", "Basic_Airt", "Basic_BattV",};

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

void Decoder::decodeAdv(QByteArray serialdata)
{
    fc_adv_info_t* info=reinterpret_cast<fc_adv_info_t*>(serialdata.data());

    packageADV[0] = info->RPM + add[0];
   // packageADV[1] = info->Boostcal * 0.0001 -1.03;
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
    packageADV[12] = info->Watertemp -80;
    packageADV[13] = info->Intaketemp -80;
    packageADV[14] = info->Knock;
    packageADV[15] = info->BatteryV * 0.1;
    packageADV[16] = info->Speed;
    packageADV[17] = info->Iscvduty * 0.001;
    packageADV[18] = info->O2volt;
    packageADV[19] = info->na1;
    packageADV[20] = info->Secinjpulse * 0.001;
    packageADV[21] = info->na2;
/*
    if (Boostcal < 0)
        Boostcal * 760 // convert Boost to mmhg in case the number is negative
*/

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


}

void Decoder::decodeSensor(QByteArray serialdata)
{
    fc_sens_info_t* info=reinterpret_cast<fc_sens_info_t*>(serialdata.data());

    packageSens[0] = info->pim * 0.01;
    packageSens[1] = info->vta1 * 0.01;
    packageSens[2] = info->vta2 * 0.01;
    packageSens[3] = info->vmop;  //calculation incorrect compared with FC Edit
    packageSens[4] = info->wtrt * 0.01;
    packageSens[5] = info->airt * 0.01;
    packageSens[6] = info->fuelt; //calculation incorrect
    packageSens[7] = info->O2S * 0.01;

    QBitArray flagArray(16);
    for (int i=0; i<16; i++)
        flagArray.setBit(i, info->flags>>i & 1);


   // m_dashboard->setpim(packageSens[0]);
    m_dashboard->setvta1(packageSens[1]);
    m_dashboard->setvta2(packageSens[2]);
    m_dashboard->setvmop(packageSens[3]);
    m_dashboard->setwtrt(packageSens[4]);
    m_dashboard->setairt(packageSens[5]);
    m_dashboard->setfuelt(packageSens[6]);
    m_dashboard->setO2S(packageSens[7]);

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

}

void Decoder::decodeAux(QByteArray serialdata)
{
    fc_aux_info_t* info=reinterpret_cast<fc_aux_info_t*>(serialdata.data());


    packageAux[0] = mul[29] * info->AN1 + add[29];
    packageAux[1] = mul[30] * info->AN2 + add[30];
    packageAux[2] = mul[31] * info->AN3 + add[31];
    packageAux[3] = mul[32] * info->AN4 + add[32];

    //    ui->txtAuxConsole->clear();

    //    ui->txtAuxConsole->append(map[22] + " " + QString::number(packageAux[0]));
    //    ui->txtAuxConsole->append(map[23] + " " + QString::number(packageAux[1]));
    //    ui->txtAuxConsole->append(map[24] + " " + QString::number(packageAux[2]));
    //    ui->txtAuxConsole->append(map[25] + " " + QString::number(packageAux[3]));
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
    packageBasic[4] = mul[0] * info->Basic_KPH + add[0];
    packageBasic[5] = mul[0] * info->Basic_Boost -760;
    packageBasic[6] = mul[0] * info->Basic_Knock + add[0];
    packageBasic[7] = mul[0] * info->Basic_Watert + add[8];
    packageBasic[8] = mul[0] * info->Basic_Airt + add[8];
    packageBasic[9] = mul[15] * info->Basic_BattV + add[0];

    if (packageBasic[5] >= 0) // while boost pressure is positive multiply by 0.01 to show kg/cm2
    {
        Boost = packageBasic[5] *0.01;
    }
    else Boost = packageBasic[5]; // while boost pressure is negative show pressure in mmhg

    m_dashboard->setInjDuty(packageBasic[0]);
    m_dashboard->setLeadingign(packageBasic[1]);
    m_dashboard->setTrailingign(packageBasic[2]);
    m_dashboard->setRevs(packageBasic[3]);
    m_dashboard->setSpeed(packageBasic[4]);
    m_dashboard->setpim(Boost);
    m_dashboard->setKnock(packageBasic[6]);
    m_dashboard->setWatertemp(packageBasic[7]);
    m_dashboard->setIntaketemp(packageBasic[8]);
    m_dashboard->setBatteryV(packageBasic[9]);


    //    ui->txtBasicConsole->clear();

    //    ui->txtBasicConsole->append(map[68] + " " + QString::number(packageBasic[0]));
    //    ui->txtBasicConsole->append(map[69] + " " + QString::number(packageBasic[1]));
    //    ui->txtBasicConsole->append(map[70] + " " + QString::number(packageBasic[2]));
    //    ui->txtBasicConsole->append(map[71] + " " + QString::number(packageBasic[3]));
    //    ui->txtBasicConsole->append(map[72] + " " + QString::number(packageBasic[4]));
    //    ui->txtBasicConsole->append(map[73] + " " + QString::number(packageBasic[5]));
    //    ui->txtBasicConsole->append(map[74] + " " + QString::number(packageBasic[6]));
    //    ui->txtBasicConsole->append(map[75] + " " + QString::number(packageBasic[7]));
    //    ui->txtBasicConsole->append(map[76] + " " + QString::number(packageBasic[8]));
    //    ui->txtBasicConsole->append(map[77] + " " + QString::number(packageBasic[9]));
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
}


//Trailing Ignition Map

void Decoder::decodeTrailIgn(QByteArray serialdata, quint8 column)
{
    //Fill Table view with Trailing ignition Table1

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
}

//Injector correction

void Decoder::decodeInjcorr(QByteArray serialdata, quint8 column)
{
    //Fill Table view with Injector correction Table1
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
}

void Decoder::decodeFuelBase(QByteArray serialdata, quint8 package)
{
    quint8 index = 0;
    qDebug() << "add package!";

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
                qDebug() << row << " : " << column;
            }
        }
        qDebug() << fullFuelBase.length();
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
//    ui->linePlatform->setText (QString(serialdata).mid(2,8));
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
    m_dashboard->setSpeed(unit.value(10)); // <-This is for the "main" speedo
    m_dashboard->setRevs(unit.value(0));
    m_dashboard->setMAP(unit.value(1));
    m_dashboard->setIntaketemp(unit.value(2));
    m_dashboard->setWatertemp(unit.value(3));
    m_dashboard->setAUXT(unit.value(4));
    m_dashboard->setAFR(unit.value(5)/2570.00);
    m_dashboard->setKnock(unit.value(6)/256);
    m_dashboard->setTPS(unit.value(7));
    m_dashboard->setIdleValue(unit.value(8));
    m_dashboard->setBatteryV(unit.value(9)/10);
    m_dashboard->setMVSS(unit.value(10));
    m_dashboard->setSVSS(unit.value(11));
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

    emit sig_adaptronicReadFinished();
}
