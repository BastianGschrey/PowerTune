#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickItem>
#include <serial.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //Serial *serial = new Serial();

    QQmlApplicationEngine engine;
    //Make MainWindow class available in QML.
    //engine.rootContext()->setContextProperty("mainWindow", &mainWindow);

    qmlRegisterType<Serial>("com.powertune", 1, 0, "SerialObject");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


return app.exec();

}

