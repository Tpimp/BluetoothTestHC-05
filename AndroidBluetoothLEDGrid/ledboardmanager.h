#ifndef LEDBOARDMANAGER_H
#define LEDBOARDMANAGER_H

#include <QObject>
#include "connectionmanager.h"
#include "fotonledmessagefactory.h"
#include <QColor>
class QColor;
class LedBoardManager : public QObject
{
    Q_OBJECT
public:
    explicit LedBoardManager(QObject *parent = 0);

signals:
    void foundLedBoard(QString dname, QString dmac);
    void connectedToLedBoard();
    void finishedScanning();
public slots:

    void findLedBoard();
    void connectToBoard(QString name, QString address);
    void sendLedSet(int row, int col, QColor color);
    void requestDevicePair(QString name, QString address);

private slots:
    void foundDevice(QString dname, QString dmac, QStringList dservice);

    void devicePaired(QString name, QString address);



private:
    ConnectionManager           mLedBoardConnection;
    FotonLEDMessageFactory      mMessageFactory;

};

#endif // LEDBOARDMANAGER_H
