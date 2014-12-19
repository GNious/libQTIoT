#include "harmonygatewayclient.h"

namespace QTIoT {
namespace Logitech {

HarmonyGatewayClient::HarmonyGatewayClient(QObject *parent) :
    QTIoT::IoTGatewayClient(parent)
{
}


HarmonyGatewayClient::HarmonyGatewayClient( QHostAddress address, quint16 port)
{
    hostaddress = address;
    hostport = port;

}



} // namespace Logitech
} // namespace QTIoT



