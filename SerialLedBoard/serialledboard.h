#ifndef SERIALLEDBOARD_H
#define SERIALLEDBOARD_H

#include <QObject>
#include <QColor>
#include <QSerialPort>
#include <QSerialPortInfo>

typedef  unsigned char FOTON_COORD;
typedef  unsigned char FOTON_COLOR;
typedef  unsigned int  FOTON_DISTANCE;

typedef  struct FOTON_RGB
{
    FOTON_COLOR Red;
    FOTON_COLOR Green;
    FOTON_COLOR Blue;
}FOTON_RGB;

static const char FOTON_START ='#';
static const char FOTON_TERMINAL ='$';

enum FUNCTIONS_MAJOR
{
    NONE = 0,
    LED_MJR,
    DRAW_MJR,
    TRANSFER_MJR,
    SYSTEM_MJR
};

enum LED_MINOR
{
    LED_CLEAR_MNR = 0,
    LED_SET_MNR,
    LED_READ_MNR
};


enum DRAW_MINOR
{
    LINE = 0,
    SQUARE,
    CIRCLE
};

typedef struct FOTON_LED_MESSAGE
{
    unsigned char FUNC_MJR : 3;
    unsigned char ROW      : 5;
    unsigned char FUNC_MNR : 3;
    unsigned char COL      : 5;
    unsigned char RED      : 8;
    unsigned char GREEN    : 8;
    unsigned char BLUE     : 8;
}FOTON_LED_MESSAGE; // Five Bytes

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



class SerialLedBoard : public QObject
{
    Q_OBJECT
public:
    explicit SerialLedBoard(QObject *parent = 0);

    ~SerialLedBoard();
signals:
    void ledSet(int row, int col, QColor ledcolor);
public slots:

private slots:
    void parseIntoBuffer();
    void processMessage(char FUNC_MJR, char FUNC_MNR,
                        char CTRL1, char CTRL2,
                        char* data);

private:
    QSerialPort    mLedPort;
    char           mBuffer[501];
    int            mBytesRead;

};

#endif // SERIALLEDBOARD_H
