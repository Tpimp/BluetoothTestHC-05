#include "connectionmanager.h"
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>

ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent),
    mTargetSocket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol,this) ),
    mTargetDevice(new QBluetoothDeviceInfo())
{


}

void ConnectionManager::connectToDevice(QString pin)
{


}

void ConnectionManager::deviceDiscovered(QBluetoothDeviceInfo)
{


}

void ConnectionManager::scanForDevices(QString filter_type)
{
    if(!mDeviceDiscover)
        mDeviceDiscover = new QBluetoothDeviceDiscoveryAgent(this);
    else
    {
        mDeviceDiscover->stop();
    }
    connect(this, &ConnectionManager::deviceDiscovered,
            mDeviceDiscover,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered);
    connect(mDeviceDiscover, &QBluetoothDeviceDiscoveryAgent::finished,
            this,&ConnectionManager::stopScanning);
    mDeviceDiscover->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
    mDeviceDiscover->start();
}

void ConnectionManager::stopScanning()
{
    if(mDeviceDiscover)
    {
        mDeviceDiscover->stop();
        mDeviceDiscover->deleteLater();
        mDeviceDiscover = nullptr;
    }
}

void ConnectionManager::sendMessage(QByteArray message)
{
    if(mTargetSocket)
    {
        if(mTargetSocket->isWritable())
        {
            mTargetSocket->write(message);
        }
    }
}

ConnectionManager::~ConnectionManager()
{
    if(mDeviceDiscover)
    {
        mDeviceDiscover->stop();
    }
    delete mDeviceDiscover;
    delete mTargetDevice;
    if(mTargetSocket)
    {
        mTargetSocket->close();
    }
    delete mTargetSocket;

}


bool ConnectionManager::isConnected()
{
    if(!mTargetSocket)
        return false;

    return mTargetSocket->isOpen();
}
