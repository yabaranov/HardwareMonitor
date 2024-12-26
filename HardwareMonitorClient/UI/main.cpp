#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>
#include <QQmlContext>

#include "NetClient.h"
#include "Logger/Logger.h"
#include "Translation/LanguageChooser.h"
#include "SensorDatabase/SensorDatabase.h"
#include "Models/HardwarePageModel.h"

void registerObjectsInQmlContext(QQmlApplicationEngine* engine)
{
    auto& logger = Logger::instance("ClientLogger", "Logs/log.txt");
    engine->rootContext()->setContextProperty("logger", &logger);

    auto& languageChooser = LanguageChooser::instance(engine);
    engine->rootContext()->setContextProperty("languageChooser", &languageChooser);

    auto& netClient = NetClient::instance();
    engine->rootContext()->setContextProperty("netClient", &netClient);
}

void registerTypesInQml()
{
    qmlRegisterType<HardwarePageModel>("HardwarePageModel", 1, 0, "HardwarePageModel");
    qmlRegisterType<SensorDatabase>("SensorDatabase", 1, 0, "SensorDatabase");
}

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

    registerObjectsInQmlContext(&engine);
    registerTypesInQml();

    engine.loadFromModule("UI", "Main");

    return app.exec();
}
