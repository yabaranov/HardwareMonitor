#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "HardwareTreeModel.h"
#include <QQmlContext>
#include "Controller.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<HardwareTreeModel>("hardwareTreeModel", 1, 0, "HardwareTreeModel");

    QQmlApplicationEngine engine;

    TreeViewController controller;
    controller.makeThread();

    engine.rootContext()->setContextProperty("controller", &controller);


    engine.load(QUrl(QStringLiteral("qrc:/qml/hardwareMonitor/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
