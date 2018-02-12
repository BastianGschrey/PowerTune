#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include "serial.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication app(argc, argv);
    app.setOrganizationName("Power-Tune");
    app.setOrganizationDomain("power-tune.org");
    app.setApplicationName("PowerTune");


    QQmlApplicationEngine engine;


    qmlRegisterType<Serial>("com.powertune", 1, 0, "SerialObject");
    engine.rootContext()->setContextProperty("Serial", new Serial(&engine));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();

}

