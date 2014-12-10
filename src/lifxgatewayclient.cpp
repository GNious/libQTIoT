#include "lifxgatewayclient.h"

#include <iostream>
using namespace std;

namespace QTIoT {
namespace LIFX {

LIFXGatewayClient::LIFXGatewayClient(QObject *parent) :
    QTIoT::IoTGatewayClient(parent)
{
}
LIFXGatewayClient::LIFXGatewayClient(LIFXPacket *packet, QHostAddress address, quint16 port)
{
    hostaddress = address;
    hostport = port;
    this->udpSocket = new QUdpSocket(this);

    memcpy(this->site, packet->header.site, 6);

    LIFXPacket *pollLights = new LIFXPacket(LIFX_GET_LIGHT_STATE);
    SendPacket(pollLights);

}


bool LIFXGatewayClient::SendPacket(LIFXPacket *packet)
{
    //udpSocket->writeDatagram((char*)&(packet->header), packet->header.size, hostaddress, hostport);
    memcpy(packet->header.site, this->site, 6);
    cout << "gateway prepped packet - ";
    udpSocket->writeDatagram(packet->toChar(), packet->header.size , hostaddress, hostport);
    cout<< "gateway sent packet!" << endl;

    return true;
}


} // namespace LIFX
} // namespace QTIoT
