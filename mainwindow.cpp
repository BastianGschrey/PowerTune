#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>

static QString map[] = {"RPM", "Intakepress", "PressureV",
                       "ThrottleV", "Primaryinp", "Fuelc",
                       "Leadingign", "Trailingign",
                       "Fueltemp", "Moilp", "Boosttp",
                       "Boostwg", "Watertemp", "Intaketemp",
                       "Knock", "BatteryV",
                       "Speed", "Iscvduty", "O2volt",
                       "na1", "Secinjpulse", "na2",
                       "AUX1", "AUX2", "AUX3", "AUX4", "AUX5", "AUX6", "AUX7", "AUX8",
                       "Analog1", "Analog2", "Analog3", "Analog4",
                       "Power", "Accel", "GForce", "ForceN", "Gear", "PrimaryInjD", "AccelTimer",
                       "Rec" };






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

    connect(serial,SIGNAL(advRequested()),this,SLOT(advRequested()));


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
    SerialSetting::Settings p;
    p = wndwSerial->settings();
    if(p.portName == "")
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
        //this->ui->txtConsole->append("Request sended.");
    }
}

void MainWindow::on_btnDisconnect_clicked()
{
    serial->closeConnection();
    ui->btnDisconnect->setDisabled(true);
    ui->btnConnect->setDisabled(false);
}

void MainWindow::advRequested()
{
 qDebug() << "signal received from serial getAdvData().";
}

void MainWindow::readData()
{
    double mul[] = FC_ADV_INFO_MUL;  // required values for calculation from raw to readable values
    double add[] = FC_ADV_INFO_ADD;


    QByteArray serialdata = serial->read();
    serial->clear();

    QByteArray serialByteData = QByteArray::fromHex(serialdata);


    qDebug() << serialdata.length();

    if(serialdata.length() == 33)
    {
         fc_adv_info_t* info=reinterpret_cast<fc_adv_info_t*>(serialByteData.data());
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
         ui->txtConsole->append(map[0] + " " + QString::number(info->RPM));
         ui->txtConsole->append(map[1] + " " + QString::number(info->Intakepress));
         ui->txtConsole->append(map[2] + " " + QString::number(rtv[2]));
         ui->txtConsole->append(map[3] + " " + QString::number(rtv[3]));
         ui->txtConsole->append(map[4] + " " + QString::number(rtv[4]));
         ui->txtConsole->append(map[5] + " " + QString::number(rtv[5]));
         ui->txtConsole->append(map[6] + " " + QString::number(rtv[6]));
         ui->txtConsole->append(map[7] + " " + QString::number(rtv[7]));
         ui->txtConsole->append(map[8] + " " + QString::number(rtv[8]));
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
         QThread::msleep(2000);
    }
    serial->getAdvData();
}


