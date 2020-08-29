#include "wifiscanner.h"
#include "dashboard.h"
#include "connect.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QProcess>
#include <QByteArrayMatcher>
#include <QByteArray>

QString outputline;
QStringList result;

WifiScanner::WifiScanner(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)
{
}


WifiScanner::WifiScanner(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}


void WifiScanner::initializeWifiscanner()
{

    process = new QProcess(this);  // create on the heap, so it doesn't go out of scope
    connect (process, SIGNAL(readyReadStandardOutput()), this, SLOT(readData()));  // connect process signals with your code
    connect(process, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(finalize(int , QProcess::ExitStatus)));

    result.clear();
    outputline.clear();
    //process->start("sudo /sbin/iw wlan0 scan | egrep 'SSID'");
    //ifconfig wlan0 | egrep 'inet 1'
    //process->start("ifconfig wlan0 | egrep 'inet 1'");  // start the process
    process->start("sudo /sbin/iwlist wlan0 scan");  // start the process
    process->waitForFinished();

}

void WifiScanner::checkWifiIP()
{
    //qDebug()<< " CHECK IP ";
    QString prog = "sudo /sbin/iwconfig";
    QStringList arguments;
    arguments << "wlan0"<<"egrep 'SSID'";
    QProcess proc;
   // qDebug() << "calling " << prog << arguments;
    proc.start(prog , arguments);
    proc.waitForFinished();
    QString output = proc.readAllStandardOutput();
    //m_dashBoard->setSerialStat("Rebooting");

}
void WifiScanner::findActiveWirelesses()
{
    //m_dashboard->setSerialStat("Currently connected WIFI:");
    /*
    QNetworkConfigurationManager ncm;
    netcfgList = ncm.allConfigurations();
    wifilist.clear();
    //WiFisList.clear();
    for (auto &x : netcfgList)
    {
        if (x.bearerType() == QNetworkConfiguration::BearerWLAN)
        {
            if(x.name() == "")
                wifilist << "Unknown(Other Network)";
            else
                wifilist << x.name();

            //  qDebug() << "Type" <<x.type();
            //  qDebug() << "Network found :"<<x.name();
            //  qDebug() << "State :"<<x.state();
        }
    }*/

    QProcess proc;
    proc.start("sh", QStringList()<<"-c"<<"iwconfig 2>&1 | grep ESSID");
    proc.waitForFinished();
    QString output = proc.readAllStandardOutput();
    m_dashboard->setSerialStat(output);
    //m_dashBoard->setSerialStat("Rebooting");
   // qDebug() << output ;
    m_dashboard->setSerialStat("WLAN IP Adress:");
    QProcess proc2;
    proc2.start("sh", QStringList()<<"-c"<<"ifconfig wlan0 2>&1 | egrep 'inet 1'");
    proc2.waitForFinished();
    QString output2 = proc2.readAllStandardOutput();
    m_dashboard->setSerialStat(output2);
    m_dashboard->setSerialStat("Ethernet IP Adress:");
    QProcess proc3;
    proc3.start("sh", QStringList()<<"-c"<<"ifconfig eth0 2>&1 | egrep 'inet 1'");
    proc3.waitForFinished();
    QString output3 = proc3.readAllStandardOutput();
    m_dashboard->setSerialStat(output3);


}

void WifiScanner::readData()
{
    QString line = process->readAllStandardOutput();        // read data from console
    outputline.append(line);
   // qDebug() << "Line :"<< line;
}

void WifiScanner::finalize(int exitCode, QProcess::ExitStatus exitStatus)
{
    //Clean up The line which contains the SSID to only show the SSID name
    //ESSID:"Marku\xE2\x80\x99s iPhone"==> "\xE2\x80\x99"suould be apostrophy

    int i =0;
    QStringList fields = outputline.split(QRegExp("[\n]"));
    //Parse List and delete all items without SSID in them
    //qDebug() << "elements :" << fields.count();
    foreach (const QString &str, fields) {
        if (str.contains("SSID"))
        {

            QString raw;
            raw = str;
            raw.remove(QChar('"'), Qt::CaseInsensitive);
            raw.replace("\xE2\x80\x99","'");
            raw.remove(0,26);
            result += raw;
        }
    }
    m_dashboard->setwifi(result);
}



void WifiScanner::setwifi(const QString &country,const QString &ssid1,const QString &psk1,const QString &ssid2,const QString &psk2)
{
    QFile file("/etc/wpa_supplicant/wpa_supplicant.conf");
    //QFile file("testme.txt" );
    file.remove(); //remove file if it exists to avoid appending of existing file
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream out(&file);

        out     << "ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev" << "\r\n"
                << "update_config=1" << "\r\n"
                << "country="+country << "\r\n"
                << "#Primary WIFI" << "\r\n"
                << "network={" << "\r\n"
                << "ssid=" << "\"" << ssid1 << "\"" << "\r\n"
                << "psk=" << "\"" << psk1  << "\"" << "\r\n"
                << "}" << "\r\n"
                   // << "#Secondary WIFI" << "\r\n"
                   // << "network={" << "\r\n"
                   // << "ssid="<< "\"" << ssid2 << "\"" << "\r\n"
                   // << "psk=" << "\"" << psk2 << "\"" << "\r\n"
                   // << "}" << "\r\n"
                << endl;
        file.close();
    }
}

