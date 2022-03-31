#ifndef WIFISCANNER_H
#define WIFISCANNER_H

#include <QTime>
#include <QTimer>
#include <QList>
#include <QInputDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QNetworkConfiguration>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>
#include <QProcess>


    class DashBoard;

class WifiScanner : public QObject
{
    Q_OBJECT

public:

    explicit WifiScanner(QObject *parent = 0);
    explicit WifiScanner(DashBoard *dashboard, QObject *parent = 0);
    int foundCount;
    QNetworkConfiguration netcfg;
    QStringList wifilist;
    QStringList WiFisList;
    QList<QNetworkConfiguration> netcfgList;
    Q_INVOKABLE void initializeWifiscanner();
    Q_INVOKABLE void setwifi(const QString &country,const QString &ssid1,const QString &psk1,const QString &ssid2,const QString &psk2);


public slots:
    void getconnectionStatus();

private:
    QStandardItemModel* listModel;
    QNetworkSession *session;
    DashBoard *m_dashboard;
    QProcess *process;

};

#endif // WIFISCANNER_H
