#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "serial.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Serial>("com.powertune", 1, 0, "SerialObject");

    engine.rootContext()->setContextProperty("Serial", new Serial(&engine));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();

}

