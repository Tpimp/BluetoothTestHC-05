#include "connectionmanager.h"

ConnectionManager::ConnectionManager(QObject *parent) :
    QObject(parent), mTargetSocket(nullptr),mTargetDevice(nullptr)
{

}

void ConnectionManager::connectToDevice(QString pin)
{

}


void ConnectionManager::scanForDevices(QString filter_type)
{

}

void ConnectionManager::stopScanning()
{

}

void ConnectionManager::sendMessage(QByteArray message)
{

}

ConnectionManager::~ConnectionManager()
{

}


bool ConnectionManager::isConnected()
{
    return false;
}
