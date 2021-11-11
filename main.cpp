#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QFileSystemModel>
#include "connect.h"
#include "Extender.h"
#include "iomapdata.h"
#include "downloadmanager.h"
#include <cstdio>
    ioMapData mpd;

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication app(argc, argv);
    app.setOrganizationName("Power-Tune");
    app.setOrganizationDomain("power-tune.org");
    app.setApplicationName("PowerTune");

    QQmlApplicationEngine engine;
    //File system models to show drive letter and Path
    /*
    QFileSystemModel pathmodel;
    QString mPath = "/";
    pathmodel.setRootPath(mPath);
    pathmodel.setFilter(QDir::NoDotAndDotDot |QDir::AllDirs);

    QFileSystemModel filemodel;
    filemodel.setRootPath(mPath);
    filemodel.setFilter(QDir::NoDotAndDotDot |QDir::Files);
    engine.rootContext()->setContextProperty("my_model", &pathmodel);
    */
    qmlRegisterType<ioMapData>("IMD", 1, 0, "IMD");
    qmlRegisterType<DownloadManager>("DLM", 1, 0, "DLM");
    qmlRegisterType<Connect>("com.powertune", 1, 0, "ConnectObject");
    //engine.rootContext()->setContextProperty("geopath", QVariant::fromValue(mpd.loadMapData("Australia","Luddenham.txt")));
    engine.rootContext()->setContextProperty("IMD", new ioMapData(&engine));
    engine.rootContext()->setContextProperty("DLM", new DownloadManager(&engine));
    engine.rootContext()->setContextProperty("Connect", new Connect(&engine));
    //engine.rootContext()->setContextProperty("CANExtender", new Extender(&engine));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();

}

