#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include "HardwareTree/HardwareTreeController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    HardwareTreeController hardwareTreeController;
    hardwareTreeController.makeHardwareThread();
  
    engine.rootContext()->setContextProperty("hardwareTreeController", &hardwareTreeController);
    engine.load(QUrl(QStringLiteral("qrc:/Qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
