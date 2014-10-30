#include "fotonledmessagefactory.h"
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QDataStream>


FotonLEDMessageFactory::FotonLEDMessageFactory()
{
}

// Fills the buffer with a 7 bit encoded LED Set Command
void FotonLEDMessageFactory::createLEDSet(int ROW, int COL, FOTON_COLOR RED,
                                          FOTON_COLOR GREEN,FOTON_COLOR BLUE,QByteArray& buffer)
{
    buffer.append(FOTON_START);

    //qDebug() << "CTRL Byte 1 " << ((LED_MJR << 5) | ROW );
    //qDebug() << "CTRL Byte 2 " << ((LED_SET_MNR << 5) | COL);

    buffer.append(LED_MJR << 5 | ROW );
    buffer.append(LED_SET_MNR << 5 | COL);
    buffer.append(RED);
    buffer.append(GREEN);
    buffer.append(BLUE);
    buffer.append(FOTON_TERMINAL);

   // qDebug() << buffer << " With a length of " << buffer.length();


}

void  FotonLEDMessageFactory::createLEDClear(int led_num,QByteArray& buffer)
{
}

void  FotonLEDMessageFactory::createDrawLine(FOTON_LINE line, FOTON_RGB color,QByteArray& buffer)
{
}
