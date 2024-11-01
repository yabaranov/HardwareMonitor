#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include <QQmlContext>
#include <QTranslator>

#include "NetEngine.h"
#include "Models/ModelManager.h"
#include "Logger/Logger.h"
#include "DataMappers/LanguageChooser.h"

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

    LanguageChooser languageChooser(engine);
    engine.rootContext()->setContextProperty("languageChooser", &languageChooser);

    auto& logger = Logger::instance("ClientLogger", "Logs/log.txt");
    engine.rootContext()->setContextProperty("logger", &logger);

    ModelManager modelManager;
    auto& netEngine = NetEngine::instance();
    QObject::connect(&netEngine, &NetEngine::sensorChanged, &modelManager, &ModelManager::onSensorChanged);      
    engine.rootContext()->setContextProperty("netEngine", &netEngine);
    engine.rootContext()->setContextProperty("modelManager", &modelManager);

    engine.loadFromModule("UI", "Main");

    return app.exec();
}
