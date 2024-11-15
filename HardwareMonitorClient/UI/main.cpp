#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include <QQmlContext>
#include <QTranslator>

#include "NetEngine.h"
#include "Models/ModelManager.h"
#include "Logger/Logger.h"
#include "Controllers/LanguageChooser.h"
#include "Controllers/SensorLogDatabase.h"


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

    auto& logger = Logger::instance("ClientLogger", "Logs/log.txt");
    engine.rootContext()->setContextProperty("logger", &logger);

    LanguageChooser languageChooser(engine);
    engine.rootContext()->setContextProperty("languageChooser", &languageChooser);

    SensorLogDatabase sensorLogDatabase;
    ModelManager modelManager;
    auto& netEngine = NetEngine::instance();
    QObject::connect(&netEngine, &NetEngine::sensorTablesChanged, &modelManager, &ModelManager::onSensorTablesChanged);
    engine.rootContext()->setContextProperty("netEngine", &netEngine);
    engine.rootContext()->setContextProperty("sensorLogDatabase", &sensorLogDatabase);
    engine.rootContext()->setContextProperty("modelManager", &modelManager);

    engine.loadFromModule("UI", "Main");

    return app.exec();
}
