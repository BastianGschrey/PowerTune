#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <serialsetting.h>
#include <serial.h>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    double rtv[33];

    struct fc_adv_info_t{
        quint16 RPM;             //0
        quint16 Intakepress;     //1
        quint16 PressureV;       //2
        quint16 ThrottleV;       //3
        quint16 Primaryinp;      //4
        quint16 Fuelc;           //5
        quint8 Leadingign;       //6
        quint8 Trailingign;      //7
        quint8 Fueltemp;         //8
        quint8 Moilp;            //9
        quint8 Boosttp;          //10
        quint8 Boostwg;          //11
        quint8 Watertemp;        //12
        quint8 Intaketemp;       //13
        quint8 Knock;            //14
        quint8 BatteryV;         //15
        quint16 Speed;           //16
        quint16 Iscvduty;        //17
        quint8 O2volt;           //18
        quint8 na1;              //19
        quint16 Secinjpulse;     //20
        quint8 na2;              //21
        fc_adv_info_t parse(const QByteArray &);
    };


    // FD3S
    #define FC_ADV_INFO_MUL		{1, 0.0001, 1, 1, 1.0/256, 1.0/256, 1, 1, 1, 212.0/256, 0.4, 0.4, 1, 1, 1, 0.1, 1, 0.1, 0.02, 1, 1.0/256, 1}
    #define FC_ADV_INFO_ADD		{0,-1.0332, 0, 0, 0, 0, -25, -25, -80, 0, 0, 0, -80, -80, 0, 0, 0, 0, 0, 0, 0, 0}




private slots:
    void on_btnSerialSettings_clicked();
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void advRequested();
    void readData();
private:
    Ui::MainWindow *ui;
    SerialSetting *wndwSerial;
    Serial *serial;

};

#endif // MAINWINDOW_H
