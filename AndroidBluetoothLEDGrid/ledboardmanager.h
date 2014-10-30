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

public slots:
    void findLedBoard();
    void connectToBoard(QString name, QString address);
    void sendLedSet(int row, int col, QColor color);

private slots:
    void foundDevice(QString dname, QString dmac, QStringList dservice);


private:
    ConnectionManager           mLedBoardConnection;
    FotonLEDMessageFactory      mMessageFactory;

};

#endif // LEDBOARDMANAGER_H
