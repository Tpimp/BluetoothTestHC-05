#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionManager(QObject *parent = 0);
    ~ConnectionManager();
    bool isConnected();
signals:
    void deviceConnected(QString device_name);
    void deviceDisconnected();
    void foundDevice(QString dname, QString dmac, QString dservice);
public slots:
    void scanForDevices(QString filter_type);
    void stopScanning();
    void sendMessage(QByteArray message);
    void connectToDevice(QString pin);


private:

    QBluetoothDeviceInfo*                mTargetDevice;
    QBluetoothSocket*                     mTargetSocket;
    QBluetoothDeviceDiscoveryAgent*      mDeviceDiscover;

};

#endif // CONNECTIONMANAGER_H
