#ifndef ADAPTRONICSELECT_H
#define ADAPTRONICSELECT_H
#include <QtSerialPort/QSerialPort>
#include <QObject>
#include <QModbusReply>
#include <QModbusClient>

#include <QModbusDataUnit>


class DashBoard;
class Serialport;
class QModbusClient;
class QModbusReply;

class AdaptronicSelect : public QObject
{
    Q_OBJECT

public:
    explicit AdaptronicSelect(QObject *parent = 0);
    explicit AdaptronicSelect(DashBoard *dashboard, QObject *parent = 0);
    ~AdaptronicSelect();

private:


public slots:
     void openConnection(const QString &portName);
     void closeConnection();
     void AdaptronicStartStream();
     void readyToRead();
     void decodeAdaptronic(QModbusDataUnit serialdata);

private:
     DashBoard *m_dashboard;
     QModbusReply *lastRequest;
     QModbusClient *modbusDevice;
     QModbusDataUnit readRequest() const;



signals:
    void sig_adaptronicReadFinished();

};


#endif // ADAPTRONICSELECT_H
