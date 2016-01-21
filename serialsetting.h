#ifndef SERIALSETTING_H
#define SERIALSETTING_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>



namespace Ui {
class SerialSetting;
}


class QIntValidator;

class SerialSetting : public QWidget
{
    Q_OBJECT

public:
    struct  Settings {
            QString portName;
            qint32 baudRate;
    };

    Settings settings();



public:
    explicit SerialSetting(QWidget *parent = 0);
    ~SerialSetting();

private slots:
    void apply();

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private:
    Ui::SerialSetting *ui;
    Settings currentSettings;
    QIntValidator *intValidator;


};

#endif // SERIALSETTING_H
