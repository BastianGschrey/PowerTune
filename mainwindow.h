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
        quint16 requesttype;
        quint16 RPM;
        quint16 Intakepress;
        quint16 PressureV;
        quint16 ThrottleV;
        quint16 Primaryinp;
        quint16 Fuelc;
        quint8 Leadingign;
        quint8 Trailingign;
        quint8 Fueltemp;
        quint8 Moilp;
        quint8 Boosttp;
        quint8 Boostwg;
        quint8 Watertemp;
        quint8 Intaketemp;
        quint8 Knock;
        quint8 BatteryV;
        quint16 Speed;
        quint16 Iscvduty;
        quint8 O2volt;
        quint8 na1;
        quint16 Secinjpulse;
        quint8 na2;
        //quint8 checksum;
        fc_adv_info_t parse(const QByteArray &);
    };

    struct  fc_aux_info_t{
        unsigned char AUX1;
        unsigned char AUX2;
        unsigned char AUX3;
        unsigned char AUX4;
        unsigned char AUX5;
        unsigned char AUX6;
        unsigned char AUX7;
        unsigned char AUX8;
    };


    // FD3S
    #define FC_ADV_INFO_MUL		{1, 0.0001, 1, 1, 1.0/256, 1.0/256, 1, 1, 1, 212.0/256, 0.4, 0.4, 1, 1, 1, 0.1, 1, 0.1, 0.02, 1, 1.0/256, 1}
    #define FC_ADV_INFO_ADD		{0,-1.0332, 0, 0, 0, 0, -25, -25, -80, 0, 0, 0, -80, -80, 0, 0, 0, 0, 0, 0, 0, 0}




private slots:
    void on_btnSerialSettings_clicked();
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void readData();

private:
    Ui::MainWindow *ui;
    SerialSetting *wndwSerial;
    Serial *serial;

};

#endif // MAINWINDOW_H
