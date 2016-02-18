#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


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
    QByteArray serialdata = serial->read();
    QByteArray serialByteData = QByteArray::fromHex(serialdata);

    qDebug() << serialdata.length();

    if(serialdata.length() == 33)
    {
        ui->txtConsole->append("Data received: " + serialdata + " -> " + QString::number(serialdata.length()) + " bytes length");
        //ui->txtConsole->append(QString::number(serialdata.length()));
    }
    serial->getAdvData();
}
