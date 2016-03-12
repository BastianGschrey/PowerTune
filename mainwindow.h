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

    typedef struct {
        unsigned short RPM;				//0
        unsigned short Intakepress;		//1
        unsigned short PressureV;		//2
        unsigned short ThrottleV;		//3
        unsigned short Primaryinp;		//4
        unsigned short Fuelc;			//5
        unsigned char Leadingign;		//6
        unsigned char Trailingign;		//7
        unsigned char Fueltemp;			//8
        unsigned char Moilp;			//9
        unsigned char Boosttp;			//10
        unsigned char Boostwg;			//11
        unsigned char Watertemp;		//12
        unsigned char Intaketemp;		//13
        unsigned char Knock;			//14
        unsigned char BatteryV;			//15
        unsigned short Speed;			//16
        unsigned short Iscvduty;		//17
        unsigned char O2volt;			//18
        unsigned char na1;				//19
        unsigned short Secinjpulse;		//20
        unsigned char na2;				//21
    } fc_adv_info_t;





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
