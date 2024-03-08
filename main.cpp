#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "semanhasht.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Semanhasht/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    auto semanhasht = new Semanhasht();
    engine.rootContext()->setContextProperty ("semanhasht" , semanhasht);

    engine.load(url);

    return app.exec();
}
