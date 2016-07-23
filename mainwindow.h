/*
  \file mainwindow.hwndwSerial->show();
  \brief Power Tune Power FC related functions
  \author Bastian Gschrey & Markus Ippy
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
#include <serialsetting.h>
#include <serial.h>
#include <QBitArray>
//#include <QMessageBox>
#include <QMetaType>
#include <QStandardItem>
#include <QObject>
#include <QWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWindow
{
    Q_OBJECT
/*

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStandardItemModel *model = new QStandardItemModel(20,20,this);
    QStandardItemModel *model1 = new QStandardItemModel(20,20,this);
    QStandardItemModel *model2 = new QStandardItemModel(20,20,this);
*/
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

    double packageBasic[22];

    struct fc_Basic_info_t{

        quint16 requesttype;
        quint16 Basic_Injduty;
        quint16 Basic_IGL;
        quint16 Basic_IGT;
        quint16 Basic_RPM;
        quint16 Basic_KPH;
        quint16 Basic_Boost;
        quint16 Basic_Knock;
        quint16 Basic_Watert;
        quint16 Basic_Airt;
        quint16 Basic_BattV;
        quint8 checksum;

        fc_Basic_info_t parse(const QByteArray &);
    };

     double packageRevIdle[16];

     struct fc_RevIdle_info_t{

        quint16 requesttype;
        quint16 RevLIM;
        quint16 FCAE;
        quint16 FCEL;
        quint16 FCAC;
        quint16 IdleAE;
        quint16 IdleEL;
        quint16 IdleAC;
        quint8 checksum;

        fc_RevIdle_info_t parse(const QByteArray &);
    };

     double packageTurboTrans[12];

     struct fc_TurboTrans_info_t{

        quint16 requesttype;
        quint8 TPS01;
        quint8 TPS02;
        quint8 TPS03;
        quint8 LowRPM1;
        quint8 LowRPM2;
        quint8 LowRPM3;
        quint8 HighRPM1;
        quint8 HighRPM2;
        quint8 HighRPM3;
        quint8 checksum;

        fc_TurboTrans_info_t parse(const QByteArray &);
    };

     double packageBoostControl[12];

     struct fc_BoostCont_info_t{

        quint16 requesttype;
        quint8 Setting1;
        quint8 Setting2;
        quint8 Setting3;
        quint8 BoostPrimary1;
        quint8 BoostSecondary1;
        quint8 BoostPrimary2;
        quint8 BoostSecondary2;
        quint8 DutyPrimary1;
        quint8 DutySecondary1;
        quint8 DutyPrimary2;
        quint8 DutySecondary2;
        quint8 checksum;

        fc_BoostCont_info_t parse(const QByteArray &);
    };
     double packageInjOverlap[12];

     struct fc_InjOverlap_info_t{

        quint16 requesttype;
        quint8 InjOvBoost1;
        quint8 lineInjOvSet1;
        quint8 InjOvBoost2;
        quint8 lineInjOvSet2;
        quint8 InjOvBoost3;
        quint8 lineInjOvSet3;
        quint8 checksum;
        fc_InjOverlap_info_t parse(const QByteArray &);
    };


    // FD3S
      #define FC_INFO_MUL		{1, 0.0001, 1, 1, 1.0/256, 1.0/256, 1, 1, 1, 212.0/256, 0.4, 0.4, 1, 1, 1, 0.1, 1, 0.1, 0.02, 1, 1.0/256, 1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0/255, 5.0/255, 5.0/255, 5.0/255, 0.01, 0.001, 0.019, 40, 0.05}
      #define FC_INFO_ADD		{0,-1.0332, 0, 0, 0, 0, -25, -25, -80, 0, 0, 0, -80, -80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

private slots:
    void on_btnSerialSettings_clicked();
    void on_btnReadAll_clicked();
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void readData(QByteArray ClassSerialData);
    void decodeAdv(QByteArray serialdata);
    void decodeSensor(QByteArray serialdata);
    void decodeAux(QByteArray serialdata);
    void decodeMap(QByteArray serialdata);
    void decodeBasic(QByteArray serialdata);
    void decodeRevIdle(QByteArray serialdata);
    void decodeTurboTrans(QByteArray serialdata);
    void decodeLeadIgn1(QByteArray serialdata);
    void decodeLeadIgn2(QByteArray serialdata);
    void decodeLeadIgn3(QByteArray serialdata);
    void decodeLeadIgn4(QByteArray serialdata);
    void decodeTrailIgn1(QByteArray serialdata);
    void decodeTrailIgn2(QByteArray serialdata);
    void decodeTrailIgn3(QByteArray serialdata);
    void decodeTrailIgn4(QByteArray serialdata);
    void decodeInjcorr1(QByteArray serialdata);
    void decodeInjcorr2(QByteArray serialdata);
    void decodeInjcorr3(QByteArray serialdata);
    void decodeInjcorr4(QByteArray serialdata);
    void decodeVersion(QByteArray serialdata);
    void decodeInit(QByteArray serialdata);
    void decodeBoostCont(QByteArray serialdata);
    void decodeInjOverlap(QByteArray serialdata);

/*private:
    Ui::MainWindow *ui;
    SerialSetting *wndwSerial;
    Serial *serial;

signals:
    void SIG_connectSerial(SerialSetting::Settings settings);
    void SIG_requestSerial(int requestID);
    void SIG_closeSerial();
*/
};

#endif // MAINWINDOW_H
