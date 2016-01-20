#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSerialSettings_clicked()
{
    //Call windows for Serial settings
    wndwSerial = new SerialSetting();
    wndwSerial->show();
}
