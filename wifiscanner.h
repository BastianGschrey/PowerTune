#ifndef WIFISCANNER_H
#define WIFISCANNER_H

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
  //  Q_PROPERTY(QStringList m_wifilist READ m_wifilist)


public:

    explicit WifiScanner(QObject *parent = 0);
    explicit WifiScanner(DashBoard *dashboard, QObject *parent = 0);
    int foundCount;
    QNetworkConfiguration netcfg;
    QStringList wifilist;
    QList<QNetworkConfiguration> netcfgList;
    Q_INVOKABLE void initializeWifiscanner();
    Q_INVOKABLE void setwifi(const QString &country,const QString &ssid1,const QString &psk1,const QString &ssid2,const QString &psk2);
    Q_INVOKABLE void checkWifiIP();

public slots:
    void findActiveWirelesses();
    void readData();
    void finalize(int exitCode, QProcess::ExitStatus exitStatus);

private:
    QTimer *findTimer;
    QStandardItemModel* listModel;
    QNetworkSession *session;
    DashBoard *m_dashboard;
    QProcess *process;
};

#endif // WIFISCANNER_H
