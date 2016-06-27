/*
  \file mainwindow.cpp
  \brief Power Tune Power FC related functions
  \author Bastian Gschrey & Markus Ippy
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>

int requestIndex = 0;
double mul[] = FC_INFO_MUL;  // required values for calculation from raw to readable values for Advanced Sensor info
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
                       "Sens_Fuel","Sens_O2","Sens_Bitflags","MAP_N","MAP_P"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     wndwSerial = new SerialSetting();
     serial = new Serial();
     ui->btnDisconnect->setDisabled(true);

//connect signals to slots:
    connect(serial,SIGNAL(readyRead()), this, SLOT(readData()));
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
        return;
    }
    else
    {
        serial->openConnection(wndwSerial->settings());
        this->ui->btnConnect->setDisabled(true);
        this->ui->btnDisconnect->setDisabled(false);
        MainWindow::sendRequest();
    }
}

void MainWindow::on_btnDisconnect_clicked()
{
    serial->closeConnection();
    ui->btnDisconnect->setDisabled(true);
    ui->btnConnect->setDisabled(false);
}

void MainWindow::sendRequest()
{
    switch (requestIndex){
    case 0:
        serial->getAdvData();
        requestIndex++;
        break;
    case 1:
        serial->getAux();
        requestIndex++;
        break;
    case 2:
        serial->getMapIndices();
        requestIndex++;
        break;
    case 3:
        serial->getSensorData();
        requestIndex = 0;
        break;
    }
}


void MainWindow::readData()
{
    QByteArray serialdata = serial->read();
    quint8 requesttype = serialdata[0];
    qDebug() << "Requesttype: " << requesttype << " Length: " << serialdata.length();

    if(serialdata.length() == 33 && requesttype == 0xF0){MainWindow::decodeAdv(serialdata);}
    if(serialdata.length() == 20 && requesttype == 0xDE){MainWindow::decodeSensor(serialdata);}
    if(serialdata.length() == 5 && requesttype == 0xDB){MainWindow::decodeAux(serialdata);}
    if(serialdata.length() == 5 && requesttype == 0x00){MainWindow::decodeMap(serialdata);}

     QThread::msleep(10);
     MainWindow::sendRequest();
}

void MainWindow::decodeAdv(QByteArray serialdata)
{

        qDebug() << "in ADV stream";
        fc_adv_info_t* info=reinterpret_cast<fc_adv_info_t*>(serialdata.data());

         rtv[0] = mul[0] * info->RPM + add[0];
         // previousRev_rpm[buf_currentIndex] = rtv[0];
         rtv[1] = mul[1] * info->Intakepress + add[1];
         rtv[2] = mul[2] * info->PressureV + add[2];
         rtv[3] = mul[3] * info->ThrottleV + add[3];
         rtv[4] = mul[4] * info->Primaryinp + add[4];
         rtv[5] = mul[5] * info->Fuelc + add[5];
         rtv[6] = mul[6] * info->Leadingign + add[6];
         rtv[7] = mul[7] * info->Trailingign + add[7];
         rtv[8] = mul[8] * info->Fueltemp + add[8];
         rtv[9] = mul[9] * info->Moilp + add[9];
         rtv[10] = mul[10] * info->Boosttp + add[10];
         rtv[11] = mul[11] * info->Boostwg + add[11];
         rtv[12] = mul[12] * info->Watertemp + add[12];
         rtv[13] = mul[13] * info->Intaketemp + add[13];
         rtv[14] = mul[14] * info->Knock + add[14];
         rtv[15] = mul[15] * info->BatteryV + add[15];
         rtv[16] = mul[16] * info->Speed + add[16];
         //rtv[16] *= speed_correction;
         //previousSpeed_kph[buf_currentIndex] = rtv[16];
         rtv[17] = mul[17] * info->Iscvduty + add[17];
         rtv[18] = mul[18] * info->O2volt + add[18];
         rtv[19] = mul[19] * info->na1 + add[19];
         rtv[20] = mul[20] * info->Secinjpulse + add[20];
         rtv[21] = mul[21] * info->na2 + add[21];

         ui->txtConsole->clear();

         ui->txtConsole->append("Data received: " + serialdata + " -> " + QString::number(serialdata.length()) + " bytes length");
         ui->txtConsole->append(map[0] + " " + QString::number(rtv[0]));
         ui->txtConsole->append(map[1] + " " + QString::number(rtv[1]));
         ui->txtConsole->append(map[2] + " " + QString::number(rtv[2]));
         ui->txtConsole->append(map[3] + " " + QString::number(rtv[3]));
         ui->txtConsole->append(map[4] + " " + QString::number(rtv[4]));
         ui->txtConsole->append(map[5] + " " + QString::number(rtv[5]));
         ui->txtConsole->append(map[6] + " " + QString::number(rtv[6]));
         ui->txtConsole->append(map[7] + " " + QString::number(rtv[7]));
         ui->txtConsole->append(map[8] + " " + QString::number(rtv[8]));
         ui->txtConsole->append(map[0U] + " " + QString::number(rtv[8]));
         ui->txtConsole->append(map[9] + " " + QString::number(rtv[9]));
         ui->txtConsole->append(map[10] + " " + QString::number(rtv[10]));
         ui->txtConsole->append(map[11] + " " + QString::number(rtv[11]));
         ui->txtConsole->append(map[12] + " " + QString::number(rtv[12]));
         ui->txtConsole->append(map[13] + " " + QString::number(rtv[13]));
         ui->txtConsole->append(map[14] + " " + QString::number(rtv[14]));
         ui->txtConsole->append(map[15] + " " + QString::number(rtv[15]));
         ui->txtConsole->append(map[16] + " " + QString::number(rtv[16]));
         ui->txtConsole->append(map[17] + " " + QString::number(rtv[17]));
         ui->txtConsole->append(map[18] + " " + QString::number(rtv[18]));
         ui->txtConsole->append(map[19] + " " + QString::number(rtv[19]));
         ui->txtConsole->append(map[20] + " " + QString::number(rtv[20]));
         ui->txtConsole->append(map[21] + " " + QString::number(rtv[21]));
    }

void MainWindow::decodeSensor(QByteArray serialdata)
{
        qDebug() << "in sensor stream";
        fc_sens_info_t* info=reinterpret_cast<fc_sens_info_t*>(serialdata.data());
      //  fc_flag_info_t* info=reinterpret_cast<fc_flag_info_t*>(serialdata.data());



        rtv2[0] = mul[1] * info->pim + add[0];
        rtv2[1] = mul[1] * info->vta1 + add[0];
        rtv2[2] = mul[1] * info->vta2 + add[0];
        rtv2[3] = mul[1] * info->vmop + add[0];
        rtv2[4] = mul[1] * info->wtrt + add[0];
        rtv2[5] = mul[1] * info->airt + add[0];
        rtv2[6] = mul[1] * info->fuelt + add[0];
        rtv2[7] = mul[1] * info->O2S + add[0];
        rtv2[8] = info->Bitflags;



         ui->txtSensConsole->clear();

         ui->txtSensConsole->append("Data received: " + serialdata + " -> " + QString::number(serialdata.length()) + " bytes length");
         ui->txtSensConsole->append(map[42] + " " + QString::number(rtv2[0]));
         ui->txtSensConsole->append(map[43] + " " + QString::number(rtv2[1]));
         ui->txtSensConsole->append(map[44] + " " + QString::number(rtv2[2]));
         ui->txtSensConsole->append(map[45] + " " + QString::number(rtv2[3]));
         ui->txtSensConsole->append(map[46] + " " + QString::number(rtv2[4]));
         ui->txtSensConsole->append(map[47] + " " + QString::number(rtv2[5]));
         ui->txtSensConsole->append(map[48] + " " + QString::number(rtv2[6]));
         ui->txtSensConsole->append(map[49] + " " + QString::number(rtv2[7]));
         ui->txtSensConsole->append(map[50] + " " + QString::number(rtv2[8]));
    }

void MainWindow::decodeMap(QByteArray serialdata)
{
        qDebug() << "in map indicies stream";
        fc_map_info_t* info=reinterpret_cast<fc_map_info_t*>(serialdata.data());


        rtv3[0] = mul[0] * info->Map_N + add[0];
        rtv3[1] = mul[0] * info->Map_P + add[0];

         ui->txtMapConsole->clear();

         ui->txtMapConsole->append("Data received: " + serialdata + " -> " + QString::number(serialdata.length()) + " bytes length");
         ui->txtMapConsole->append(map[51] + " " + QString::number(rtv3[0]));
         ui->txtMapConsole->append(map[52] + " " + QString::number(rtv3[1]));
}

void MainWindow::decodeAux(QByteArray serialdata)
{
        qDebug() << "in aux stream";
        fc_aux_info_t* info=reinterpret_cast<fc_aux_info_t*>(serialdata.data());


        rtv4[0] = mul[0] * info->AN1 + add[0];
        rtv4[1] = mul[0] * info->AN2 + add[0];
        rtv4[2] = mul[0] * info->AN3 + add[0];
        rtv4[3] = mul[0] * info->AN4 + add[0];

         ui->txtAuxConsole->clear();

         ui->txtAuxConsole->append("Data received: " + serialdata + " -> " + QString::number(serialdata.length()) + " bytes length");
         ui->txtAuxConsole->append(map[22] + " " + QString::number(rtv4[0]));
         ui->txtAuxConsole->append(map[23] + " " + QString::number(rtv4[1]));
         ui->txtAuxConsole->append(map[24] + " " + QString::number(rtv4[2]));
         ui->txtAuxConsole->append(map[25] + " " + QString::number(rtv4[3]));
}
