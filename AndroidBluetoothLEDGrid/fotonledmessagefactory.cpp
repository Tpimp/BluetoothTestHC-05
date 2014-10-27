#include "fotonledmessagefactory.h"
#include <QString>
#include <QByteArray>

FotonLEDMessageFactory::FotonLEDMessageFactory()
{
}

void FotonLEDMessageFactory::createLEDSet(int led_num, FOTON_RGB LED_COLOR, QByteArray& buffer)
{

}

QString  FotonLEDMessageFactory::createLEDClear(int led_num,QByteArray& buffer)
{
    return QString();
}

QString  FotonLEDMessageFactory::createDrawLine(FOTON_LINE line, FOTON_RGB color,QByteArray& buffer)
{
    return QString();
}
