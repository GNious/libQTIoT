#include "iotdiscoveryclient.h"

namespace QTIoT {

IoTDiscoveryClient::IoTDiscoveryClient(QObject *parent) :
    QObject(parent)
{
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


} // namespace QTIoT
