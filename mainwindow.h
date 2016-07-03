/*
  \file mainwindow.hwndwSerial->show();
  \brief Power Tune Power FC related functions
  \author Bastian Gschrey & Markus Ippy
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <serialsetting.h>
#include <serial.h>
#include <QBitArray>
#include <QMessageBox>
#include <QMetaType>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    double packageADV[33];

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
        quint8 checksum;
        fc_adv_info_t parse(const QByteArray &);
    };

    double packageSens[20];

    struct fc_sens_info_t{

        quint16 requesttype;
        quint16 pim;
        quint16 vta1;
        quint16 vta2;
        quint16 vmop;
        quint16 wtrt;
        quint16 airt;
        quint16 fuelt;
        quint16 O2S;
        quint16 flags;
        quint8  checksum;

        fc_sens_info_t parse(const QByteArray &);

    };

    double packageMap[2];

    struct fc_map_info_t{

        quint16 requesttype;
        quint8 Map_N;
        quint8 Map_P;
        quint8 checksum;

        fc_map_info_t parse(const QByteArray &);
    };

    double packageAux[4];

    struct fc_aux_info_t{

        quint16 requesttype;
        quint8 AN1;
        quint8 AN2;
        quint8 AN3;
        quint8 AN4;
        quint8 checksum;

        fc_aux_info_t parse(const QByteArray &);
    };

    // FD3S
      #define FC_INFO_MUL		{1, 0.0001, 1, 1, 1.0/256, 1.0/256, 1, 1, 1, 212.0/256, 0.4, 0.4, 1, 1, 1, 0.1, 1, 0.1, 0.02, 1, 1.0/256, 1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0/255, 5.0/255, 5.0/255, 5.0/255}
      #define FC_INFO_ADD		{0,-1.0332, 0, 0, 0, 0, -25, -25, -80, 0, 0, 0, -80, -80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

private slots:
    void on_btnSerialSettings_clicked();
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void readData(QByteArray serialdata);
    void decodeAdv(QByteArray serialdata);
    void decodeSensor(QByteArray serialdata);
    void decodeAux(QByteArray serialdata);
    void decodeMap(QByteArray serialdata);


private:
    Ui::MainWindow *ui;
    SerialSetting *wndwSerial;
    Serial *serial;

signals:
    void SIG_connectSerial(SerialSetting::Settings settings);
    void SIG_requestSerial(int requestID);
    void SIG_closeSerial();

};

#endif // MAINWINDOW_H
