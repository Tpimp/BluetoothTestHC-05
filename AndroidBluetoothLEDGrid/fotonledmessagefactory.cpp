#include "fotonledmessagefactory.h"
#include <QString>
#include <QByteArray>

FotonLEDMessageFactory::FotonLEDMessageFactory()
{
}

void FotonLEDMessageFactory::createLEDSet(int led_num, FOTON_RGB LED_COLOR, QByteArray& buffer)
{

}

void  FotonLEDMessageFactory::createLEDClear(int led_num,QByteArray& buffer)
{
}

void  FotonLEDMessageFactory::createDrawLine(FOTON_LINE line, FOTON_RGB color,QByteArray& buffer)
{
}
