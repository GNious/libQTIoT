#include "iotdiscoveryclient.h"

namespace QTIoT {

IoTDiscoveryClient::IoTDiscoveryClient(QObject *parent) :
    QObject(parent)
{
    discoveryTimer = NULL;
}

bool IoTDiscoveryClient::addGatewayClient(QString address, QTIoT::IoTGatewayClient *client)
{
    if(!gateways.contains(address))
    {
        gateways.insert(address, client);
        emit newGatewayClient(client);
        return true;
    }
    return false;
}
bool IoTDiscoveryClient::addIoTItem(QString address, QTIoT::IoTObject *item)
{
    if(!items.contains(address))
    {
        items.insert(address, item);
        emit newIoTItem(item);
        return true;
    }
    return false;
}

void IoTDiscoveryClient::IoTItemDiscovered(IoTObject * item)
{
    addIoTItem(item->getAddress(), item);  // <-- MUST figure out proper address

/*    if(!items.contains(address))
    {
        items.insert(address, item);
        emit newIoTItem(item);
        return true;
    }
    return false;*/
}
bool IoTDiscoveryClient::startDiscoveryTimer( int waitMs)
{
    if(discoveryTimer == NULL)
    {
        discoveryTimer = new QTimer(this);
        connect(discoveryTimer, SIGNAL(timeout()), this, SLOT(updateCaption()));
        discoveryTimer->start(waitMs);
        if(waitMs > 5000)
            discoveryTimer->setTimerType(Qt::VeryCoarseTimer);
        else
            discoveryTimer->setTimerType(Qt::CoarseTimer);
        return true;
    }
    else if(waitMs != discoveryTimer->interval())
    {
        discoveryTimer->setInterval(waitMs);
        if(waitMs > 5000)
            discoveryTimer->setTimerType(Qt::VeryCoarseTimer);
        else
            discoveryTimer->setTimerType(Qt::CoarseTimer);
        return true;
    }

    return false;
}
bool IoTDiscoveryClient::endDiscoveryTimer()
{
    if( discoveryTimer != NULL)
    {
        //if(discoveryTimer->isActive())
        delete discoveryTimer;
        discoveryTimer = NULL;
        return true;
    }

    return false;
}
void IoTDiscoveryClient::timingDiscovery()
{
    this->discover();
}
} // namespace QTIoT
