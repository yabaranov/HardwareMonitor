#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "NetEngine.h"
#include "NetState.h"
#include "ModelManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<NetEngine>("NetEngine", 1, 0, "NetEngine", [](QQmlEngine*, QJSEngine*) -> QObject* {
        return new NetEngine();
    });
    qmlRegisterType<NetState>("NetState", 1, 0, "NetState");
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
