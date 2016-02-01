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
     //ui->btnConnect->setDisabled(true);

     //connect(ui->btnApply, SIGNAL(clicked()),this, SLOT(apply()));

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
    }
}

void MainWindow::on_btnDisconnect_clicked()
{
    serial->closeConnection();
    ui->btnDisconnect->setDisabled(true);
    ui->btnConnect->setDisabled(false);
}
