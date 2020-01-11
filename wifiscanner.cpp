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
    process->start("sudo /sbin/iwlist wlan0 scan");  // start the process
    process->waitForFinished();

}

void WifiScanner::checkWifiIP()
{
    qDebug()<< " CHECK IP ";
    QString prog = "sudo /sbin/iwconfig";
    QStringList arguments;
    arguments << "wlan0"<<"egrep 'SSID'";
    QProcess proc;
    qDebug() << "calling " << prog << arguments;
    proc.start(prog , arguments);
    proc.waitForFinished();
    QString output = proc.readAllStandardOutput();
    //m_dashBoard->setSerialStat("Rebooting");

}
void WifiScanner::findActiveWirelesses()
{
    m_dashboard->setSerialStat("Currently connected WIFI:");
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
    m_dashboard->setSerialStat("IP Adress:");
    QProcess proc2;
    proc2.start("sh", QStringList()<<"-c"<<"ifconfig wlan0 2>&1 | grep inet");
    proc2.waitForFinished();
    QString output2 = proc2.readAllStandardOutput();
    m_dashboard->setSerialStat(output2);


}

void WifiScanner::readData()
{
    QString line = process->readAllStandardOutput();        // read data from serial port
    outputline.append(line);
   // qDebug() << "Line :"<< line;
}

void WifiScanner::finalize(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "done :";
    int i =0;
    QStringList fields = outputline.split(QRegExp("[\n]"));
    //Parse List and delete all items without SSID in them
    //qDebug() << "elements :" << fields.count();
    foreach (const QString &str, fields) {
        if (str.contains("SSID"))
        {

            QString raw;
            raw = str;
           // qDebug()<< raw;
           // raw.replace("                    ESSID:\", "");
            raw.remove(QChar('"'), Qt::CaseInsensitive);
            //raw.remove(QChar('\'), Qt::CaseInsensitive);
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

