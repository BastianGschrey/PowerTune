/*
  \file mainwindow.cpp
  \brief Power Tune Power FC related functions
  \author Bastian Gschrey & Markus Ippy
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include <QStandardItemModel>
#include <QHeaderView>

int requestID = 0; //ID for requested data type
QByteArray serialdata;

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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wndwSerial = new SerialSetting();
    ui->btnDisconnect->setDisabled(true);
    QHeaderView* horizontalHeaderFuelTable = ui->tableFuelBase->horizontalHeader();
    horizontalHeaderFuelTable->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView* verticalHeaderFuelTable = ui->tableFuelBase->verticalHeader();
    verticalHeaderFuelTable->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeaderFuelTable->setStyleSheet("QHeaderView::section {background-color:grey}");
    verticalHeaderFuelTable->setStyleSheet("QHeaderView::section {background-color:grey}");
    serial = new Serial();

    connect(serial,SIGNAL(SIG_dataAvailable(QByteArray)),this,SLOT(readData(QByteArray)));




    }



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSerialSettings_clicked()
{
    wndwSerial->show();
}
void MainWindow::on_btnReadAll_clicked()
{

    SerialSetting::Settings settings;
    settings = wndwSerial->settings();
    if(settings.portName == "")
    {
        QMessageBox msgBox;
        msgBox.warning(this,"Warning","\n No serialport selected. \n",QMessageBox::Ok);
        wndwSerial->show();
        return;
    }
    else
    {
        this->ui->btnConnect->setDisabled(true);
        this->ui->btnDisconnect->setDisabled(false);
        serial->openConnection(settings);
    //    serial->sendRequestMap(allrequestID);
    }
}

void MainWindow::on_btnConnect_clicked()
{

    SerialSetting::Settings settings;
    settings = wndwSerial->settings();
    if(settings.portName == "")
    {
        QMessageBox msgBox;
        msgBox.warning(this,"Warning","\n No serialport selected. \n",QMessageBox::Ok);
        wndwSerial->show();
        return;
    }
    else
    {
        this->ui->btnConnect->setDisabled(true);
        this->ui->btnDisconnect->setDisabled(false);
        this->ui->btnReadAll->setDisabled(true);
        serial->openConnection(settings);
        serial->sendRequest(requestID);
    }
}


void MainWindow::on_btnDisconnect_clicked()
{
    emit SIG_closeSerial();
    ui->btnDisconnect->setDisabled(true);
    ui->btnConnect->setDisabled(false);
}


void MainWindow::readData(QByteArray ClassSerialData)
{
    serialdata.append(ClassSerialData);
    qDebug() << "readdata";
    if(serialdata != NULL)
    {
        quint8 requesttype = serialdata[0];
        if(serialdata[1] + 1 == serialdata.length())
        {
            if(serialdata.length() == 33 && requesttype == 0xF0){MainWindow::decodeAdv(serialdata);}
            if(serialdata.length() == 21 && requesttype == 0xDE){MainWindow::decodeSensor(serialdata);}
            if(serialdata.length() == 7 && requesttype == 0x00){MainWindow::decodeAux(serialdata);}
            if(serialdata.length() == 5 && requesttype == 0xDB){MainWindow::decodeMap(serialdata);}
            if(serialdata.length() == 23 && requesttype == 0xDA){MainWindow::decodeBasic(serialdata);}
            if(serialdata.length() == 17 && requesttype == 0xB8){MainWindow::decodeRevIdle(serialdata);}
            if(serialdata.length() == 12 && requesttype == 0x7D){MainWindow::decodeTurboTrans(serialdata);}
            if(serialdata.length() == 103 && requesttype == 0x76){MainWindow::decodeLeadIgn(serialdata, 0);}
            if(serialdata.length() == 103 && requesttype == 0x77){MainWindow::decodeLeadIgn(serialdata, 5);}
            if(serialdata.length() == 103 && requesttype == 0x78){MainWindow::decodeLeadIgn(serialdata, 10);}
            if(serialdata.length() == 103 && requesttype == 0x79){MainWindow::decodeLeadIgn(serialdata, 15);}
            if(serialdata.length() == 103 && requesttype == 0x81){MainWindow::decodeTrailIgn(serialdata, 0);}
            if(serialdata.length() == 103 && requesttype == 0x82){MainWindow::decodeTrailIgn(serialdata, 5);}
            if(serialdata.length() == 103 && requesttype == 0x83){MainWindow::decodeTrailIgn(serialdata, 10);}
            if(serialdata.length() == 103 && requesttype == 0x84){MainWindow::decodeTrailIgn(serialdata, 15);}
            if(serialdata.length() == 103 && requesttype == 0x86){MainWindow::decodeInjcorr(serialdata, 0);}
            if(serialdata.length() == 103 && requesttype == 0x87){MainWindow::decodeInjcorr(serialdata, 5);}
            if(serialdata.length() == 103 && requesttype == 0x88){MainWindow::decodeInjcorr(serialdata, 10);}
            if(serialdata.length() == 103 && requesttype == 0x89){MainWindow::decodeInjcorr(serialdata, 15);}

            if(serialdata.length() == 103 && requesttype == 0xB0){MainWindow::decodeFuelBase(serialdata, 0);}
            if(serialdata.length() == 103 && requesttype == 0xB1){MainWindow::decodeFuelBase(serialdata, 2);}
            if(serialdata.length() == 103 && requesttype == 0xB2){MainWindow::decodeFuelBase(serialdata, 4);}
            if(serialdata.length() == 103 && requesttype == 0xB3){MainWindow::decodeFuelBase(serialdata, 6);}
            if(serialdata.length() == 103 && requesttype == 0xB4){MainWindow::decodeFuelBase(serialdata, 8);}
            if(serialdata.length() == 103 && requesttype == 0xB5){MainWindow::decodeFuelBase(serialdata, 10);}
            if(serialdata.length() == 103 && requesttype == 0xB6){MainWindow::decodeFuelBase(serialdata, 12);}
            if(serialdata.length() == 103 && requesttype == 0xB7){MainWindow::decodeFuelBase(serialdata, 14);}

            if(serialdata.length() == 8 && requesttype == 0xF5){MainWindow::decodeVersion(serialdata);}
            if(serialdata.length() == 11 && requesttype == 0xF3){MainWindow::decodeInit(serialdata);}
            if(serialdata.length() == 14 && requesttype == 0xAB){MainWindow::decodeBoostCont(serialdata);}
            if(serialdata.length() == 9 && requesttype == 0x7B){MainWindow::decodeInjOverlap(serialdata);}
            if(serialdata.length() == 15 && requesttype == 0x92){MainWindow::decodeInjPriLagvsBattV(serialdata);}
            if(serialdata.length() == 15 && requesttype == 0x9F){MainWindow::decodeInjScLagvsBattV(serialdata);}
            if(serialdata.length() == 27 && requesttype == 0x8D){MainWindow::decodeFuelInjectors(serialdata);}


            serialdata.clear();
            serialdata.clear();
            if(requestID <= 61){requestID++;}
            else{requestID = 58;}

            serial->sendRequest(requestID);
        }
    }


}


void MainWindow::decodeAdv(QByteArray serialdata)
{
    fc_adv_info_t* info=reinterpret_cast<fc_adv_info_t*>(serialdata.data());

    packageADV[0] = mul[0] * info->RPM + add[0];
    packageADV[1] = mul[1] * info->Intakepress + add[1];
    packageADV[2] = mul[34] * info->PressureV + add[2];  //Value in Volt
    packageADV[3] = mul[34] * info->ThrottleV + add[3];  //Value in Volt
    packageADV[4] = mul[4] * info->Primaryinp + add[4];
    packageADV[5] = mul[5] * info->Fuelc + add[5];
    packageADV[6] = mul[6] * info->Leadingign + add[6];
    packageADV[7] = mul[7] * info->Trailingign + add[7];
    packageADV[8] = mul[8] * info->Fueltemp + add[8];
    packageADV[9] = mul[9] * info->Moilp + add[9];     //Value lower by 10 compared to FC Edit
    packageADV[10] = mul[10] * info->Boosttp + add[10];    //Value shows correctly in Percent (FC edit shows just raw value
    packageADV[11] = mul[11] * info->Boostwg + add[11];    //Value shows correctly in Percent (FC edit shows just raw value
    packageADV[12] = mul[12] * info->Watertemp + add[12];
    packageADV[13] = mul[13] * info->Intaketemp + add[13];
    packageADV[14] = mul[14] * info->Knock + add[14];
    packageADV[15] = mul[15] * info->BatteryV + add[15];
    packageADV[16] = mul[16] * info->Speed + add[16];
    packageADV[17] = mul[17] * info->Iscvduty + add[17];
    packageADV[18] = mul[18] * info->O2volt + add[18];
    packageADV[19] = mul[19] * info->na1 + add[19];
    packageADV[20] = mul[20] * info->Secinjpulse + add[20];
    packageADV[21] = mul[21] * info->na2 + add[21];

    ui->txtConsole->clear();

    ui->txtConsole->append(map[0] + " " + QString::number(packageADV[0]));
    ui->txtConsole->append(map[1] + " " + QString::number(packageADV[1]));
    ui->txtConsole->append(map[2] + " " + QString::number(packageADV[2]));
    ui->txtConsole->append(map[3] + " " + QString::number(packageADV[3]));
    ui->txtConsole->append(map[4] + " " + QString::number(packageADV[4]));
    ui->txtConsole->append(map[5] + " " + QString::number(packageADV[5]));
    ui->txtConsole->append(map[6] + " " + QString::number(packageADV[6]));
    ui->txtConsole->append(map[7] + " " + QString::number(packageADV[7]));
    ui->txtConsole->append(map[8] + " " + QString::number(packageADV[8]));
    ui->txtConsole->append(map[9] + " " + QString::number(packageADV[9]));
    ui->txtConsole->append(map[10] + " " + QString::number(packageADV[10]));
    ui->txtConsole->append(map[11] + " " + QString::number(packageADV[11]));
    ui->txtConsole->append(map[12] + " " + QString::number(packageADV[12]));
    ui->txtConsole->append(map[13] + " " + QString::number(packageADV[13]));
    ui->txtConsole->append(map[14] + " " + QString::number(packageADV[14]));
    ui->txtConsole->append(map[15] + " " + QString::number(packageADV[15]));
    ui->txtConsole->append(map[16] + " " + QString::number(packageADV[16]));
    ui->txtConsole->append(map[17] + " " + QString::number(packageADV[17]));
    ui->txtConsole->append(map[18] + " " + QString::number(packageADV[18]));
    ui->txtConsole->append(map[19] + " " + QString::number(packageADV[19]));
    ui->txtConsole->append(map[20] + " " + QString::number(packageADV[20]));
    ui->txtConsole->append(map[21] + " " + QString::number(packageADV[21]));


}

void MainWindow::decodeSensor(QByteArray serialdata)
{
    fc_sens_info_t* info=reinterpret_cast<fc_sens_info_t*>(serialdata.data());

    packageSens[0] = mul[33] * info->pim + add[0];
    packageSens[1] = mul[33] * info->vta1 + add[0];
    packageSens[2] = mul[33] * info->vta2 + add[0];
    packageSens[3] = mul[33] * info->vmop + add[0];  //calculation incorrect compared with FC Edit
    packageSens[4] = mul[33] * info->wtrt + add[0];
    packageSens[5] = mul[33] * info->airt + add[0];
    packageSens[6] = mul[33] * info->fuelt + add[0]; //calculation incorrect
    packageSens[7] = mul[33] * info->O2S + add[0];

    QBitArray flagArray(16);
    for (int i=0; i<16; i++)
        flagArray.setBit(i, info->flags>>i & 1);

    ui->txtSensConsole->clear();

    ui->txtSensConsole->append(map[42] + " " + QString::number(packageSens[0]));
    ui->txtSensConsole->append(map[43] + " " + QString::number(packageSens[1]));
    ui->txtSensConsole->append(map[44] + " " + QString::number(packageSens[2]));
    ui->txtSensConsole->append(map[45] + " " + QString::number(packageSens[3]));
    ui->txtSensConsole->append(map[46] + " " + QString::number(packageSens[4]));
    ui->txtSensConsole->append(map[47] + " " + QString::number(packageSens[5]));
    ui->txtSensConsole->append(map[48] + " " + QString::number(packageSens[6]));
    ui->txtSensConsole->append(map[49] + " " + QString::number(packageSens[7]));
    //from here, bit flags
    ui->txtSensConsole->append(map[50] + " " + QString::number(flagArray[0]));
    ui->txtSensConsole->append(map[51] + " " + QString::number(flagArray[1]));
    ui->txtSensConsole->append(map[52] + " " + QString::number(flagArray[2]));
    ui->txtSensConsole->append(map[53] + " " + QString::number(flagArray[3]));
    ui->txtSensConsole->append(map[54] + " " + QString::number(flagArray[4]));
    ui->txtSensConsole->append(map[55] + " " + QString::number(flagArray[5]));
    ui->txtSensConsole->append(map[56] + " " + QString::number(flagArray[6]));
    ui->txtSensConsole->append(map[57] + " " + QString::number(flagArray[7]));
    ui->txtSensConsole->append(map[58] + " " + QString::number(flagArray[8]));
    ui->txtSensConsole->append(map[59] + " " + QString::number(flagArray[9]));
    ui->txtSensConsole->append(map[60] + " " + QString::number(flagArray[10]));
    ui->txtSensConsole->append(map[61] + " " + QString::number(flagArray[11]));
    ui->txtSensConsole->append(map[62] + " " + QString::number(flagArray[12]));
    ui->txtSensConsole->append(map[63] + " " + QString::number(flagArray[13]));
    ui->txtSensConsole->append(map[64] + " " + QString::number(flagArray[14]));
    ui->txtSensConsole->append(map[65] + " " + QString::number(flagArray[15]));
}

void MainWindow::decodeAux(QByteArray serialdata)
{
    fc_aux_info_t* info=reinterpret_cast<fc_aux_info_t*>(serialdata.data());


    packageAux[0] = mul[29] * info->AN1 + add[29];
    packageAux[1] = mul[30] * info->AN2 + add[30];
    packageAux[2] = mul[31] * info->AN3 + add[31];
    packageAux[3] = mul[32] * info->AN4 + add[32];

    ui->txtAuxConsole->clear();

    ui->txtAuxConsole->append(map[22] + " " + QString::number(packageAux[0]));
    ui->txtAuxConsole->append(map[23] + " " + QString::number(packageAux[1]));
    ui->txtAuxConsole->append(map[24] + " " + QString::number(packageAux[2]));
    ui->txtAuxConsole->append(map[25] + " " + QString::number(packageAux[3]));
}

void MainWindow::decodeMap(QByteArray serialdata)
{
    fc_map_info_t* info=reinterpret_cast<fc_map_info_t*>(serialdata.data());

    packageMap[0] = mul[0] * info->Map_N + add[0];
    packageMap[1] = mul[0] * info->Map_P + add[0];

    ui->txtMapConsole->clear();

    ui->txtMapConsole->append(map[66] + " " + QString::number(packageMap[0]));
    ui->txtMapConsole->append(map[67] + " " + QString::number(packageMap[1]));
}
void MainWindow::decodeBasic(QByteArray serialdata)
{
    fc_Basic_info_t* info=reinterpret_cast<fc_Basic_info_t*>(serialdata.data());

    packageBasic[0] = mul[15] * info->Basic_Injduty + add[0];
    packageBasic[1] = mul[0] * info->Basic_IGL + add[6];
    packageBasic[2] = mul[0] * info->Basic_IGT + add[6];
    packageBasic[3] = mul[0] * info->Basic_RPM + add[0];
    packageBasic[4] = mul[0] * info->Basic_KPH + add[0];
    packageBasic[5] = mul[0] * info->Basic_Boost + add[0];  //calculation not yet correct
    packageBasic[6] = mul[0] * info->Basic_Knock + add[0];
    packageBasic[7] = mul[0] * info->Basic_Watert + add[8];
    packageBasic[8] = mul[0] * info->Basic_Airt + add[8];
    packageBasic[9] = mul[15] * info->Basic_BattV + add[0];

    ui->txtBasicConsole->clear();

    ui->txtBasicConsole->append(map[68] + " " + QString::number(packageBasic[0]));
    ui->txtBasicConsole->append(map[69] + " " + QString::number(packageBasic[1]));
    ui->txtBasicConsole->append(map[70] + " " + QString::number(packageBasic[2]));
    ui->txtBasicConsole->append(map[71] + " " + QString::number(packageBasic[3]));
    ui->txtBasicConsole->append(map[72] + " " + QString::number(packageBasic[4]));
    ui->txtBasicConsole->append(map[73] + " " + QString::number(packageBasic[5]));
    ui->txtBasicConsole->append(map[74] + " " + QString::number(packageBasic[6]));
    ui->txtBasicConsole->append(map[75] + " " + QString::number(packageBasic[7]));
    ui->txtBasicConsole->append(map[76] + " " + QString::number(packageBasic[8]));
    ui->txtBasicConsole->append(map[77] + " " + QString::number(packageBasic[9]));
}

void MainWindow::decodeRevIdle(QByteArray serialdata)
{
    fc_RevIdle_info_t* info=reinterpret_cast<fc_RevIdle_info_t*>(serialdata.data());

    packageRevIdle[0] = info->RevLIM;
    packageRevIdle[1] = info->FCAE;
    packageRevIdle[2] = info->FCEL;
    packageRevIdle[3] = info->FCAC;
    packageRevIdle[4] = info->IdleAE;
    packageRevIdle[5] = info->IdleEL;
    packageRevIdle[6] = info->IdleAC;

    ui->lineRevlim->setText (QString::number(packageRevIdle[0]));
    ui->lineFCAE->setText (QString::number(packageRevIdle[1]));
    ui->lineFCEL->setText (QString::number(packageRevIdle[2]));
    ui->lineFCAC->setText (QString::number(packageRevIdle[3]));
    ui->lineIdleAE->setText (QString::number(packageRevIdle[4]));
    ui->lineIdleEL->setText (QString::number(packageRevIdle[5]));
    ui->lineIdleAC->setText (QString::number(packageRevIdle[6]));
}

void MainWindow::decodeTurboTrans(QByteArray serialdata)
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

    ui->lineTPS01->setText (QString::number(packageTurboTrans[0]));
    ui->lineTPS02->setText (QString::number(packageTurboTrans[1]));
    ui->lineTPS03->setText (QString::number(packageTurboTrans[2]));
    ui->lineLowRPM1->setText (QString::number(packageTurboTrans[3]));
    ui->lineLowRPM2->setText (QString::number(packageTurboTrans[4]));
    ui->lineLowRPM3->setText (QString::number(packageTurboTrans[5]));
    ui->lineHighRPM1->setText (QString::number(packageTurboTrans[6]));
    ui->lineHighRPM2->setText (QString::number(packageTurboTrans[7]));
    ui->lineHighRPM3->setText (QString::number(packageTurboTrans[8]));
}

void MainWindow::decodeLeadIgn(QByteArray serialdata, quint8 column)
{
    //Fill Table view with Leading ignition Table1


    quint8 columnLimit = column + 5;
    quint8 countarray = 1; //counter for the position in the array
        for (column; column < columnLimit; column++) //increases the counter column by 1 until column 5
        {

            for (int row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
            {
                if(countarray <= 102){countarray++;} //Increases the counter "countarray till 100"
                    QStandardItem *value = new QStandardItem(QString::number(serialdata[countarray]-25)); //insert the array here and use count array for position in array
                    model->setItem(row,column,value);
                    ui->tableLeadIgn->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                    ui->tableLeadIgn->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                    ui->tableLeadIgn->setModel(model);
            }
        }
}


//Trailing Ignition Map

void MainWindow::decodeTrailIgn(QByteArray serialdata, quint8 column)
{
    //Fill Table view with Trailing ignition Table1

    quint8 columnLimit = column + 5;
    quint8 countarray = 1; //counter for the position in the array
        for (column; column < columnLimit; column++) //increases the counter column by 1 until column 5
        {
            for (quint8 row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
            {
                if(countarray <= 102){countarray++;} //Increases the counter "countarray till 100"
                    QStandardItem *value = new QStandardItem(QString::number(serialdata[countarray]-25)); //insert the array here and use count array for position in array
                    model1->setItem(row,column,value);
                    ui->tableTrailIgn->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                    ui->tableTrailIgn->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                    ui->tableTrailIgn->setModel(model1);
            }
        }
}

//Injector correction

void MainWindow::decodeInjcorr(QByteArray serialdata, quint8 column)
{
    //Fill Table view with Injector correction Table1
    quint8 columnLimit = column + 5;

    quint8 countarray = 1; //counter for the position in the array
        for (column; column < columnLimit; column++) //increases the counter column by 1 until column 5
        {
            for (quint8 row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
            {
                if(countarray <= 102){countarray++;} //Increases the counter "countarray till 100"
                    QStandardItem *value = new QStandardItem(QString::number((serialdata[countarray]-128)*mul[40])); //insert the array here and use count array for position in array
                    model2->setItem(row,column,value);
                    ui->tableInjCorr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                    ui->tableInjCorr->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                    ui->tableInjCorr->setModel(model2);
            }
        }
}

void MainWindow::decodeFuelBase(QByteArray serialdata, quint8 column)
{

    fc_FuelBase_info_t* info=reinterpret_cast<fc_FuelBase_info_t*>(serialdata.data());
    quint8 columnLimit = column + 5;
    quint8 baseIndex = 0;
    for (column; column < columnLimit; column++)
    {
        for (quint8 row = 0; row < 20; row++)
        {

            ui->tableFuelBase->setItem(row, column, new QTableWidgetItem(QString::number(info->fuelBase[baseIndex])));
            /*QStandardItem *value = new QStandardItem(QString::number((info->fuelBase[baseIndex])));
            model->setItem(row,column,value);
            ui->tableFuelBase->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableFuelBase->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableFuelBase->setModel(model);
            baseIndex++;*/

        }
    }

}


void MainWindow::decodeBoostCont(QByteArray serialdata)
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

    ui->lineBoostPri1->setText (QString::number(packageBoostControl[3]));
    ui->lineBoostSec1->setText (QString::number(packageBoostControl[4]));
    ui->lineBoostPri2->setText (QString::number(packageBoostControl[5]));
    ui->lineBoostSec2->setText (QString::number(packageBoostControl[6]));
    ui->lineBoostDutyPri1->setText (QString::number(packageBoostControl[7]));
    ui->lineBoostDutySec1->setText (QString::number(packageBoostControl[8]));
    ui->lineBoostDutyPri2->setText (QString::number(packageBoostControl[9]));
    ui->lineBoostDutySec2->setText (QString::number(packageBoostControl[10]));

}
void MainWindow::decodeInjOverlap(QByteArray serialdata)
{
    fc_InjOverlap_info_t* info=reinterpret_cast<fc_InjOverlap_info_t*>(serialdata.data());

    packageInjOverlap[0] = mul[39] * info->InjOvBoost1;
    packageInjOverlap[1] = info->lineInjOvSet1;
    packageInjOverlap[2] = mul[39] * info->InjOvBoost2;
    packageInjOverlap[3] = info->lineInjOvSet2;
    packageInjOverlap[4] = mul[39] * info->InjOvBoost3;
    packageInjOverlap[5] = info->lineInjOvSet3;


    ui->lineInjOvBoost1->setText (QString::number(packageInjOverlap[0]));
    ui->lineInjOvSet1->setText (QString::number(packageInjOverlap[1]));
    ui->lineInjOvBoost2->setText (QString::number(packageInjOverlap[2]));
    ui->lineInjOvSet2->setText (QString::number(packageInjOverlap[3]));
    ui->lineInjOvBoost3->setText (QString::number(packageInjOverlap[4]));
    ui->lineInjOvSet3->setText (QString::number(packageInjOverlap[5]));


}

void MainWindow::decodeVersion(QByteArray serialdata)
{
        ui->lineVersion->setText (QString(serialdata).mid(2,5));
}
void MainWindow::decodeInit(QByteArray serialdata)
{
        ui->linePlatform->setText (QString(serialdata).mid(2,8));
}


void MainWindow::decodeInjPriLagvsBattV(QByteArray serialdata)
{
    fc_InjPriLagvsBattV_info_t* info=reinterpret_cast<fc_InjPriLagvsBattV_info_t*>(serialdata.data());

    packageInjPriLagvsBattV[0] = mul[38] * info->InjPriLag16V;
    packageInjPriLagvsBattV[1] = mul[38] * info->InjPriLag14V;
    packageInjPriLagvsBattV[2] = mul[38] * info->InjPriLag12V;
    packageInjPriLagvsBattV[3] = mul[38] * info->InjPriLag10V;
    packageInjPriLagvsBattV[4] = mul[38] * info->InjPriLag8V;
    packageInjPriLagvsBattV[5] = mul[38] * info->InjPriLag6V;

    ui->lineInjPrLag16V->setText (QString::number(packageInjPriLagvsBattV[0]));
    ui->lineInjPrLag14V->setText (QString::number(packageInjPriLagvsBattV[1]));
    ui->lineInjPrLag12V->setText (QString::number(packageInjPriLagvsBattV[2]));
    ui->lineInjPrLag10V->setText (QString::number(packageInjPriLagvsBattV[3]));
    ui->lineInjPrLag8V->setText (QString::number(packageInjPriLagvsBattV[4]));
    ui->lineInjPrLag6V->setText (QString::number(packageInjPriLagvsBattV[5]));
}
void MainWindow::decodeInjScLagvsBattV(QByteArray serialdata)
{
    fc_InjScLagvsBattV_info_t* info=reinterpret_cast<fc_InjScLagvsBattV_info_t*>(serialdata.data());

    packageInjScLagvsBattV[0] = mul[38] * info->InjScLag16V;
    packageInjScLagvsBattV[1] = mul[38] * info->InjScLag14V;
    packageInjScLagvsBattV[2] = mul[38] * info->InjScLag12V;
    packageInjScLagvsBattV[3] = mul[38] * info->InjScLag10V;
    packageInjScLagvsBattV[4] = mul[38] * info->InjScLag8V;
    packageInjScLagvsBattV[5] = mul[38] * info->InjScLag6V;

    ui->lineInjScLag16V->setText (QString::number(packageInjScLagvsBattV[0]));
    ui->lineInjScLag14V->setText (QString::number(packageInjScLagvsBattV[1]));
    ui->lineInjScLag12V->setText (QString::number(packageInjScLagvsBattV[2]));
    ui->lineInjScLag10V->setText (QString::number(packageInjScLagvsBattV[3]));
    ui->lineInjScLag8V->setText (QString::number(packageInjScLagvsBattV[4]));
    ui->lineInjScLag6V->setText (QString::number(packageInjScLagvsBattV[5]));
}
void MainWindow::decodeFuelInjectors(QByteArray serialdata)
{
    fc_FuelInjectors_info_t* info=reinterpret_cast<fc_FuelInjectors_info_t*>(serialdata.data());

    packageFuelInjectors[1] = mul[41] * info->frontpulse * mul[42];
    packageFuelInjectors[3] = mul[41] * info->rearpulse * mul[42];
    packageFuelInjectors[4] = mul[38] * info->frntprilag;//(multiply by 0.004)
    packageFuelInjectors[6] = mul[38] * info->frntseclag;//(multiply by 0.004)
    packageFuelInjectors[8] =  mul[38] *info->rearprilag;//(multiply by 0.004)
    packageFuelInjectors[10] = mul[38] *info->rearseclag;//(multiply by 0.004)
    packageFuelInjectors[12] = info->prinjsize;
    packageFuelInjectors[13] = info->secinjsize;
    packageFuelInjectors[14] = mul[15] * info->prisectransprc; // divide by 10 to get %
    packageFuelInjectors[15] = mul[38] * info->prisectransms; //(multiply by 0.004)


    ui->linefrontpulse->setText (QString::number(packageFuelInjectors[1]));
    ui->linerearpulse->setText (QString::number(packageFuelInjectors[3]));
    ui->linefrntprilag->setText (QString::number(packageFuelInjectors[4]));
    ui->linefrntseclag->setText (QString::number(packageFuelInjectors[6]));
    ui->linerearprilag->setText (QString::number(packageFuelInjectors[8]));
    ui->linerearseclag->setText (QString::number(packageFuelInjectors[10]));
    ui->linePriInjSize->setText (QString::number(packageFuelInjectors[12]));
    ui->lineSecInjSize->setText (QString::number(packageFuelInjectors[13]));
    ui->linePriSecTransPrc->setText (QString::number(packageFuelInjectors[14]));
    ui->linePriSecTransms->setText (QString::number(packageFuelInjectors[15]));
}
