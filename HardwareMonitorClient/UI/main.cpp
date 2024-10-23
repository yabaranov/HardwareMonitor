#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>

#include "NetEngine.h"
#include "NetState.h"
#include "Models/ModelManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Universal");

    QGuiApplication::setWindowIcon(QIcon(":/Resources/Images/icon.png"));
    QGuiApplication::setApplicationName("HardwareMonitorClient");
    QGuiApplication::setOrganizationName("BaranovCompany");

    qmlRegisterSingletonType<NetEngine>("NetEngine", 1, 0, "NetEngine", [](QQmlEngine*, QJSEngine*) -> QObject* {
        return new NetEngine();
    });
    qmlRegisterSingletonType<NetState>("NetState", 1, 0, "NetState", [](QQmlEngine*, QJSEngine*) -> QObject* {
        return new NetState();
    });
    qmlRegisterSingletonType<ModelManager>("ModelManager", 1, 0, "ModelManager", [](QQmlEngine*, QJSEngine*) -> QObject* {
        return new ModelManager();
    });

    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []()
        {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
    );

    engine.loadFromModule("UI", "Main");

    return app.exec();
}
