#ifndef FOTONLEDMESSAGEFACTORY_H
#define FOTONLEDMESSAGEFACTORY_H

class QString;
class QByteArray;

typedef  unsigned char FOTON_COORD;
typedef  unsigned char FOTON_COLOR;
typedef  unsigned int  FOTON_DISTANCE;

typedef  struct FOTON_RGB
{
    FOTON_COLOR Red;
    FOTON_COLOR Green;
    FOTON_COLOR Blue;
}FOTON_RGB;

#define FOTON_TERMINAL  '$'

typedef struct FOTON_LINE
{
    FOTON_COORD X1;
    FOTON_COORD Y1;
    FOTON_COORD X2;
    FOTON_COORD Y2;
}FOTON_LINE;

typedef struct FOTON_RECT
{
    FOTON_COORD X;
    FOTON_COORD Y;
    FOTON_DISTANCE Height;
    FOTON_DISTANCE Width;
}FOTON_RECT;



class FotonLEDMessageFactory
{
public:
    explicit FotonLEDMessageFactory();
    void     createLEDSet(int led_num, FOTON_RGB LED_COLOR, QByteArray& buffer);
    QString  createLEDClear(int led_num,QByteArray& buffer);
    QString  createDrawLine(FOTON_LINE line, FOTON_RGB color,QByteArray& buffer);

};

#endif // FOTONLEDMESSAGEFACTORY_H
