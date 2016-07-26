#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MainWindow mainWindow;

    QQmlApplicationEngine engine;
    //Make MainWindow class available in QML.
    engine.rootContext()->setContextProperty("mainWindow", &mainWindow);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}

