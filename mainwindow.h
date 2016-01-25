#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <serialsetting.h>
#include <serial.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnSerialSettings_clicked();
    void on_btnConnect_clicked();




    void on_btnDisconnect_clicked();

private:
    Ui::MainWindow *ui;
    SerialSetting *wndwSerial;
    Serial *serial;
};

#endif // MAINWINDOW_H
