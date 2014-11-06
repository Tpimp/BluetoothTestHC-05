#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "serialledboard.h"
#include <QQmlContext>
#include <QScreen>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QScreen * pscreen(app.primaryScreen());
    QQmlApplicationEngine engine;
    SerialLedBoard  mboard;
    engine.rootContext()->setContextProperty("SerialLedBoard",&mboard);



    //QObject::connect(&sport, &QSerialPort::)
    int  screen_width;
    int  screen_height;
    bool show_expanded(true);
    QString display_mode("FullScreen");


    show_expanded = false; // Uncomment for FULLSCREEN

    if(!show_expanded)
    {
        screen_width = pscreen->size().width();
        screen_height = pscreen->size().height();
    }
    else
    {
        screen_width = pscreen->availableGeometry().width();
        screen_height = pscreen->availableGeometry().height();
        display_mode = "Maximized";
    }
    int temp_width(screen_width);
    if(screen_height > screen_width)
    {
        screen_width = screen_height;
        screen_height = temp_width;
    }
    engine.rootContext()->setContextProperty("ScreenWidth",screen_width);
    engine.rootContext()->setContextProperty("ScreenHeight",screen_height);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
