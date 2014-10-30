#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "fotonledmessagefactory.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    FotonLEDMessageFactory msg_factory;
    QByteArray  buffer;
    msg_factory.createLEDSet(24,30,69,112,212,buffer);

    return app.exec();
}
