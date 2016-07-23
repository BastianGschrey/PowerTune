#ifndef SERIALSETTING_H
#define SERIALSETTING_H

#include <QAbstractListModel>
#include <QtSerialPort/QSerialPort>



namespace Ui {
class SerialSetting;
}


class QIntValidator;

class SerialSetting : public QAbstractListModel
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
    Settings currentSettings;
    QIntValidator *intValidator;


};

#endif // SERIALSETTING_H
