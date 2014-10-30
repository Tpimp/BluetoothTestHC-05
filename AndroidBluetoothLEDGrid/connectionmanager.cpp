#include "connectionmanager.h"
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>
ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent),
    mTargetSocket(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol,this) ),
    mTargetDevice(new QBluetoothDeviceInfo())
{


}

void ConnectionManager::connectToDevice(QString device_name, QString addr, QString pin)
{
    if(mTargetSocket)
    {
        mTargetSocket->close();
    }
    // Build Device Class Descriptor
    quint32 device_class(4);             // Bluetooth Rendering Service
    device_class = (device_class << 11);
    device_class |= (8 << 5);            // Toy Device (CLASS MAJOR)
    device_class |= (4 << 2);            // Toy Controller (CLASS MINOR)

    *mTargetDevice = QBluetoothDeviceInfo(QBluetoothAddress(addr),device_name,device_class );
    mTargetSocket->connectToService(mTargetDevice->address(),mTargetSocket->localPort());

}

void ConnectionManager::deviceDiscovered(QBluetoothDeviceInfo info)
{
    emit foundDevice(info.name(),info.address().toString(),
                     serviceEnumToStrList(info.serviceClasses()));

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


QStringList ConnectionManager::serviceEnumToStrList(QBluetoothDeviceInfo::ServiceClasses service)
{
    QStringList services;
    // Double guard statement
    if(service & QBluetoothDeviceInfo::NoService)
    {
        return services;
    }
    if(service & QBluetoothDeviceInfo::AllServices)
    {
        services.append("Positioning");
        services.append("Networking");
        services.append("Rendering");
        services.append("Capturing");
        services.append("Object Transfer");
        services.append("Telephony");
        services.append("Information");
        return services;
    }
    if(service & QBluetoothDeviceInfo::PositioningService)
        services.append("Positioning");
    if(service & QBluetoothDeviceInfo::NetworkingService)
        services.append("Networking");
    if(service & QBluetoothDeviceInfo::RenderingService)
        services.append("Rendering");
    if(service & QBluetoothDeviceInfo::CapturingService)
        services.append("Capturing");
    if(service & QBluetoothDeviceInfo::ObjectTransferService)
        services.append("Object Transfer");
    if(service & QBluetoothDeviceInfo::TelephonyService)
        services.append("Telephony");
    if(service & QBluetoothDeviceInfo::InformationService)
        services.append("Information");
    return services;
}
