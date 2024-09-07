#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "TreeViewController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TreeViewController treeViewController;
    treeViewController.makeHardwareThread();

    engine.rootContext()->setContextProperty("treeViewController", &treeViewController);

    engine.load(QUrl(QStringLiteral("qrc:/qml/hardwareMonitor/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
