#ifndef SERIALSETTING_H
#define SERIALSETTING_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QMetaType>




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

    void on_btnApply_clicked();

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();


private:
    Ui::SerialSetting *ui;
    Settings currentSettings;
    QIntValidator *intValidator;


};
Q_DECLARE_METATYPE(SerialSetting::Settings)

#endif // SERIALSETTING_H
