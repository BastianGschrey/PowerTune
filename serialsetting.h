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
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };




public:
    explicit SerialSetting(QWidget *parent = 0);
    ~SerialSetting();

private slots:

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
