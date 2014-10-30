#include "ledboardmanager.h"

LedBoardManager::LedBoardManager(QObject *parent) :
    QObject(parent)
{
}


void LedBoardManager::connectToBoard(QString name, QString address)
{
    mLedBoardConnection.connectToDevice(name,address,"1234");
}

void LedBoardManager::findLedBoard()
{
    mLedBoardConnection.scanForDevices("");
}

void LedBoardManager::foundDevice(QString dname, QString dmac, QStringList dservice)
{
    if(dname.contains("LedBoard"))
        foundLedBoard(dname,dmac);
}

void LedBoardManager::sendLedSet(int row, int col, QColor color)
{
    QByteArray message;
    mMessageFactory.createLEDSet(row,col, color.red(),color.green(),color.blue(), message);
    mLedBoardConnection.sendMessage(message);
}
