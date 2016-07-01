/*
  \file mainwindow.cpp
  \brief Power Tune Power FC related functions
  \author Bastian Gschrey & Markus Ippy
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>

int requestID = 0; //ID for requested data type

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
                       "STP", "CAT", "ELD", "HWL", "FPD", "FPR", "APR", "PAC", "CCN", "TCN", "PRC" ,"MAP_N","MAP_P"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wndwSerial = new SerialSetting();
    ui->btnDisconnect->setDisabled(true);

    QThread* serialthread = new QThread;
    Serial*  serial = new Serial();
    serial->moveToThread(serialthread);
    qRegisterMetaType<SerialSetting::Settings>();



//----------------------------SIGNALS---------------------------------
    //connect(serial,SIGNAL(readyRead()), this, SLOT(readData()));
    connect(serialthread, SIGNAL(started()), serial, SLOT(process()));
    connect(serial, SIGNAL(finished()), serialthread, SLOT(quit()));
    connect(serial, SIGNAL(finished()), serial, SLOT(deleteLater()));
    connect(serialthread, SIGNAL(finished()), serialthread, SLOT(deleteLater()));
    //Slots for Serial Communication
    connect(this, SIGNAL(SIG_connectSerial(SerialSetting::Settings)), serial, SLOT(openConnection(SerialSetting::Settings)),Qt::QueuedConnection);
    connect(this, SIGNAL(SIG_requestSerial(int)), serial, SLOT(sendRequest(int)), Qt::QueuedConnection);
    connect(serial, SIGNAL(SIG_dataAvailable(QByteArray)), this, SLOT(readData(QByteArray)), Qt::QueuedConnection);

    serialthread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSerialSettings_clicked()
{
    //Call windows for Serial settings

    wndwSerial->show();
}

void MainWindow::on_btnConnect_clicked()
{

    SerialSetting::Settings settings;
    settings = wndwSerial->settings();
    if(settings.portName == "")
    {
        QMessageBox msgBox;
        //msgBox.setText("No serialport selected");
        msgBox.warning(this,"Warning","\n No serialport selected. \n",QMessageBox::Ok);
        wndwSerial->show();
        return;
    }
    else
    {
        //serial->openConnection(wndwSerial->settings());
        this->ui->btnConnect->setDisabled(true);
        this->ui->btnDisconnect->setDisabled(false);
        //serial->sendRequest(requestID);
        emit SIG_connectSerial(settings);
        emit SIG_requestSerial(requestID);
    }
}

void MainWindow::on_btnDisconnect_clicked()
{
    //serial->closeConnection();
    ui->btnDisconnect->setDisabled(true);
    ui->btnConnect->setDisabled(false);
}


void MainWindow::readData(QByteArray serialdata)
{
    if(serialdata != NULL)
    {
    quint8 requesttype = serialdata[0];

    if(serialdata.length() == 33 && requesttype == 0xF0){MainWindow::decodeAdv(serialdata);}
    if(serialdata.length() == 21 && requesttype == 0xDE){MainWindow::decodeSensor(serialdata);}
    if(serialdata.length() == 7 && requesttype == 0x00){MainWindow::decodeAux(serialdata);}
    if(serialdata.length() == 5 && requesttype == 0xDB){MainWindow::decodeMap(serialdata);}
    }
    if(requestID <= 2){requestID++;}
    else{requestID = 0;}

    emit SIG_requestSerial(requestID);

}


void MainWindow::decodeAdv(QByteArray serialdata)
{
         fc_adv_info_t* info=reinterpret_cast<fc_adv_info_t*>(serialdata.data());

         packageADV[0] = mul[0] * info->RPM + add[0];
         packageADV[1] = mul[1] * info->Intakepress + add[1];
         packageADV[2] = mul[2] * info->PressureV + add[2];
         packageADV[3] = mul[3] * info->ThrottleV + add[3];
         packageADV[4] = mul[4] * info->Primaryinp + add[4];
         packageADV[5] = mul[5] * info->Fuelc + add[5];
         packageADV[6] = mul[6] * info->Leadingign + add[6];
         packageADV[7] = mul[7] * info->Trailingign + add[7];
         packageADV[8] = mul[8] * info->Fueltemp + add[8];
         packageADV[9] = mul[9] * info->Moilp + add[9];
         packageADV[10] = mul[10] * info->Boosttp + add[10];
         packageADV[11] = mul[11] * info->Boostwg + add[11];
         packageADV[12] = mul[12] * info->Watertemp + add[12];
         packageADV[13] = mul[13] * info->Intaketemp + add[13];
         packageADV[14] = mul[14] * info->Knock + add[14];
         packageADV[15] = mul[15] * info->BatteryV + add[15];
         packageADV[16] = mul[16] * info->Speed + add[16];
         //rtv[16] *= speed_correction;
         //previousSpeed_kph[buf_currentIndex] = rtv[16];
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
      //  fc_flag_info_t* info=reinterpret_cast<fc_flag_info_t*>(serialdata.data());



        packageSens[0] = mul[22] * info->pim + add[22];
        packageSens[1] = mul[23] * info->vta1 + add[23];
        packageSens[2] = mul[24] * info->vta2 + add[24];
        packageSens[3] = mul[25] * info->vmop + add[25];
        packageSens[4] = mul[26] * info->wtrt + add[26];
        packageSens[5] = mul[27] * info->airt + add[27];
        packageSens[6] = mul[28] * info->fuelt + add[28];
        packageSens[7] = mul[29] * info->O2S + add[29];
        packageSens[8] = info->Bitflags;


         ui->txtSensConsole->clear();

         ui->txtSensConsole->append(map[42] + " " + QString::number(packageSens[0]));
         ui->txtSensConsole->append(map[43] + " " + QString::number(packageSens[1]));
         ui->txtSensConsole->append(map[44] + " " + QString::number(packageSens[2]));
         ui->txtSensConsole->append(map[45] + " " + QString::number(packageSens[3]));
         ui->txtSensConsole->append(map[46] + " " + QString::number(packageSens[4]));
         ui->txtSensConsole->append(map[47] + " " + QString::number(packageSens[5]));
         ui->txtSensConsole->append(map[48] + " " + QString::number(packageSens[6]));
         ui->txtSensConsole->append(map[49] + " " + QString::number(packageSens[7]));
         //ui->txtSensConsole->append(map[50] + " " + QBitArray(info->Bitflags[0])); // From here Flags

         ui->txtSensConsole->append(map[51] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[52] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[53] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[54] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[55] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[56] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[57] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[58] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[59] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[60] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[61] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[62] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[63] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[64] + " " + QString::number(packageSens[8]));
         ui->txtSensConsole->append(map[65] + " " + QString::number(packageSens[8]));
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
