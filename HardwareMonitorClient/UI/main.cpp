#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include <QQmlContext>

#include "NetEngine.h"
#include "Models/ModelManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Universal");

    QGuiApplication::setWindowIcon(QIcon(":/Resources/Images/icon.png"));
    QGuiApplication::setApplicationName("HardwareMonitorClient");
    QGuiApplication::setOrganizationName("BaranovCompany");

    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []()
        {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
    );

    ModelManager modelManager;
    NetEngine netEngine;

    QObject::connect(&netEngine, &NetEngine::sensorChanged, &modelManager, &ModelManager::onSensorChanged);

    engine.rootContext()->setContextProperty("netEngine", &netEngine);
    engine.rootContext()->setContextProperty("modelManager", &modelManager);

    engine.loadFromModule("UI", "Main");

    return app.exec();
}
