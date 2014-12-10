#include "iotgatewayclient.h"

namespace QTIoT {

IoTGatewayClient::IoTGatewayClient(QObject *parent) :
    QObject(parent)
{
}
QTIoT::IoTObject* IoTGatewayClient::getItem(QString address)
{
    if(items.contains(address))
    {
        return items[address];
    }
    return NULL;
}

} // namespace QTIoT
