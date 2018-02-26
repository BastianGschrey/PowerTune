#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
class udpreceiver;
class QUdpSocket;
class DashBoard;

class udpreceiver : public QObject
{
    Q_OBJECT

public:
    explicit udpreceiver(QObject *parent = 0);
     explicit udpreceiver(DashBoard *dashboard, QObject *parent = 0);

private:
     DashBoard *m_dashboard;
     QUdpSocket *udpSocket = nullptr;
     int         m_units;
public slots:
     void processPendingDatagrams();
     void startreceiver();
     void closeConnection();
signals:


};


#endif // UDPRECEIVER_H
