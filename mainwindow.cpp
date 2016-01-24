#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     wndwSerial = new SerialSetting();
     serial = new Serial();
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
    if(!p.portName.isEmpty() || p.baudRate == false)
    {
        serial->openConnection(wndwSerial->settings());
        this->ui->btnConnect->setDisabled(true);
    }
}

