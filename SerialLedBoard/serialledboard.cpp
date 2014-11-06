#include "serialledboard.h"
#include <QColor>
#include <QDebug>

SerialLedBoard::SerialLedBoard(QObject *parent) :
    QObject(parent),mLedPort(this),mBytesRead(0)
{
    mBuffer[501] = '\0';
    quint32 baud(1382400);
    connect(&mLedPort, &QSerialPort::readyRead,
            this, &SerialLedBoard::parseIntoBuffer);
    QList<QSerialPortInfo> ports(QSerialPortInfo::availablePorts());
    foreach(const QSerialPortInfo & port, ports)
    {
      // qDebug() << "Name" << port.portName();
      // qDebug() << "Description" << port.description();
      // qDebug() << "S/N" << port.serialNumber();
     //  qDebug() << "Manufacturer" << port.manufacturer();
       if(port.description().contains("CC3200LP"))
       {
           mLedPort.setPortName(port.portName());
           mLedPort.setPort(port);
       }

    }
    mLedPort.setBaudRate(baud, QSerialPort::AllDirections);
    mLedPort.open(QIODevice::ReadWrite);


}

void SerialLedBoard::parseIntoBuffer()
{
    mBytesRead = mLedPort.read(mBuffer,500);
    int index = 0;
    quint8  Major_FUNC;
    quint8  Minor_FUNC;
    quint8  CTRL_DATA1;
    quint8  CTRL_DATA2;
    char  DATA[498];
    char  DATA_INDEX(0);
 //   qDebug() <<"Parsing incoming message" << mBuffer;
    while((index < mBytesRead) && (mBuffer[index] != '\0'))
    {
        switch(mBuffer[index])
        {
            case '#':
            {
             //   qDebug() << "Found Start Char";
                Major_FUNC = mBuffer[++index];
                CTRL_DATA1 = Major_FUNC;
                Minor_FUNC = mBuffer[++index];
                CTRL_DATA2 = Minor_FUNC;
                Major_FUNC ^= 0x1F;
                Major_FUNC = (Major_FUNC >> 5);
                Minor_FUNC ^= 0x1F;
                Minor_FUNC = (Minor_FUNC >> 5);
                CTRL_DATA1 &= 0x1F;
                CTRL_DATA2 &= 0x1F;
              //  qDebug() << "Major_FUNC " << Major_FUNC << "Minor_FUNC " << Minor_FUNC << \
              //              "CTRL1 " << CTRL_DATA1 << \
              //              "CTRL2 " << CTRL_DATA2;

                char next_byte = mBuffer[++index];
                while(next_byte != '$' && next_byte != '\0' && (index < mBytesRead))
                {
                    DATA[DATA_INDEX++] = next_byte;
                    next_byte = mBuffer[++index];
                }
                if(next_byte == '$')
                {
              //      qDebug() << "Parsed DATA " << DATA;
                    DATA[DATA_INDEX++] = '\0';
                    processMessage(Major_FUNC,Minor_FUNC,CTRL_DATA1,CTRL_DATA2,DATA);
                }
                break;
            }
            default:
            {
                index++;
                break;
            }
        }
    }
}


void SerialLedBoard::processMessage(char FUNC_MJR, char FUNC_MNR, char CTRL1, char CTRL2, char *data)
{
   // qDebug() << "Processing Message " <<
  //              "FUNC_MJR " << FUNC_MJR <<
   //             "FUNC_MNR " << FUNC_MNR <<
   //             "CTRL1 " << CTRL1 <<
   //             "CTRL2 " << CTRL2 <<
   //             "DATA " << data;
    switch(FUNC_MJR)
    {
        case LED_MJR:
        {
            QColor parsedColor;
            quint8 led_select(data[0]);

            if(led_select == 0)
            {
                parsedColor = QColor(0,0,0);
            }
            else if(led_select == 1)
            {
                quint8 blue(data[1]);
                parsedColor = QColor::fromRgb(0,0,blue);
            }
            else if(led_select == 2)
            {
                quint8 green(data[1]);
                parsedColor = QColor::fromRgb(0,green,0);
            }
            else if(led_select == 3)
            {
                quint8 green(data[1]);
                quint8 blue(data[2]);
                parsedColor = QColor::fromRgb(0,green,blue);
            }
            else if(led_select == 4)
            {
                quint8 red(data[1]);
                parsedColor = QColor::fromRgb(red,0,0);
            }
            else if(led_select == 5)
            {
                quint8 red(data[1]);
                quint8 blue(data[2]);
                parsedColor = QColor::fromRgb(red,0,blue);
            }
            else if(led_select == 6)
            {
                quint8 red(data[1]);
                quint8 green(data[2]);
                parsedColor = QColor::fromRgb(red,green,0);
            }
            else if(led_select == 7)
            {
                quint8 red(data[1]);
                quint8 green(data[2]);
                quint8 blue(data[3]);
                parsedColor = QColor::fromRgb(red,green,blue);
            }
            else
                qDebug() << "Invalid RGB descriptor";
            emit ledSet(CTRL1,CTRL2,parsedColor);
        }
    }
}

SerialLedBoard::~SerialLedBoard()
{

}
