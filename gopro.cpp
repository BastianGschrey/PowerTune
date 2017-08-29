/*
* Copyright (C) 2017 Bastian Gschrey & Markus Ippy
*
* GoPro Wifi remote based on the information provided by
* Based on the information provided by https://github.com/KonradIT/goprowifihack
* •Konrad Iturbe - main developer
* •dough29 - HERO2 research
* •EvilWombat - general and HERO3
* •3v1n0 - HERO4 research
* •Maelstrom Napalm - HERO4 research
* •fraannk - HERO4 research
*
* This software comes under the GPL (GNU Public License)
* You may freely copy,distribute etc. this as long as the source code
* is made available for FREE.
*
* No warranty is made or implied. You use this program at your own risk.
*/


#include "gopro.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QString Command; // GoPro Command URL


GoPro::GoPro(QObject *parent)
    : QObject(parent)
{

}
//Function for GoPro command forwarding

void GoPro::goProSettings(const int &goProSelect, const QString &goPropass)
{
    int Index = goProSelect;
    QString OPTION;
    QString PARAM1;
    QString PARAM2;
    QString PASSWORD = goPropass;
    QString ADRESS;



    //HERO

    if (Index == 0)
    {
    ADRESS = "http://10.5.5.9/gp/gpControl/command/shutter?p=";
    Command = QString (ADRESS) + QString (OPTION);
    }

    //HERO 2

    if (Index == 1)
    {
    ADRESS = "http://10.5.5.9/";
    PARAM1 = "bacpac";
    PARAM2 = "SH";
    Command = QString (ADRESS) + QString (PARAM1) +"/"+  QString (PARAM2) + "?t=" + QString (PASSWORD) + "&p=%" + "0" + QString (OPTION);
    }

    //HERO 3
    if (Index == 2)
    {
    ADRESS = "http://10.5.5.9/";
    PARAM1 = "camera";
    PARAM2 = "SH";
    Command = QString (ADRESS) +QString (PARAM1) +"/"+ QString (PARAM2) + "?t=" + QString (PASSWORD) + "&p=%" + "0" + QString (OPTION);
    }

    //HERO 4

    if (Index == 3)
    {
    PARAM1 = "camera";
    PARAM2 = "SH";
    Command = QString (ADRESS) +QString (PARAM1) +"/"+ QString (PARAM2) + "?t=" + QString (PASSWORD) + "&p=%" + QString (OPTION);
    }

    //qDebug() << "Gopro Index" <<Index;
    //qDebug() << "Gopro Command" <<Command;
}
void GoPro::goprorec(const QString &record)
{
    QString cmdstatus = record; // Status of GoPro command ,on off (0/1)
    //qDebug()<< "cmdstatus " << cmdstatus;


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    GoPro::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(QString (Command) + QString (cmdstatus))));
    //qDebug() << "sending HTTP request " <<QString (Command) + QString (cmdstatus);
}
 void GoPro::replyFinished(QNetworkReply *net_reply)
{
     QByteArray data = net_reply->readAll();
    //qDebug() << "reply finished" << data.toInt();
 }
