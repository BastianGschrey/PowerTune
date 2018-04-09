#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QFileSystemModel>
#include "connect.h"


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication app(argc, argv);
    app.setOrganizationName("Power-Tune");
    app.setOrganizationDomain("power-tune.org");
    app.setApplicationName("PowerTune");

    QQmlApplicationEngine engine;
    //
    QFileSystemModel model;
    model.setRootPath("/");
    engine.rootContext()->setContextProperty("my_model", &model);
    //
    qmlRegisterType<Connect>("com.powertune", 1, 0, "ConnectObject");
    engine.rootContext()->setContextProperty("Connect", new Connect(&engine));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();

}

