#include "lifxdiscoveryclient.h"

#include <iostream>
using namespace std;

namespace QTIoT {
namespace LIFX {

LIFXDiscoveryClient::LIFXDiscoveryClient():
    IoTDiscoveryClient()
{
    udpSocket = NULL;
}

bool LIFXDiscoveryClient::connectUDP()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind( LIFX_UDP_PORT, QAbstractSocket::ShareAddress );

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));

    return false;
}

bool LIFXDiscoveryClient::sendMessage(IoTObject *obj, void *msg)
{
    if(udpSocket == NULL)
        connectUDP();

    return false;
}

bool LIFXDiscoveryClient::discover()
{
    if(udpSocket == NULL)
        connectUDP();

    //QByteArray datagram; //= "Broadcast message " + QByteArray::number(messageNo);
    //QByteArray::
    //udpSocket->writeDatagram(datagram.data(), datagram.size(),
    //                         QHostAddress::Broadcast, LIFX_UDP_PORT);
    LIFXPacket *packet = new LIFXPacket( LIFX_GET_PAN_GATEWAY );

    //char *data = packet->toChar();

//    udpSocket->writeDatagram("123456789012345678901234567890123456", packet->header.size, QHostAddress::Broadcast, LIFX_UDP_PORT);
    udpSocket->writeDatagram((char*)&(packet->header), packet->header.size, QHostAddress::Broadcast, LIFX_UDP_PORT);
//    udpSocket->write(data);

    return false;
}

void LIFXDiscoveryClient::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        cout << "Received Datagram! " << sender.toString().toUtf8().constData() << ":" << senderPort << endl;

        processIncomingDatagram(datagram, sender, senderPort);
    }
}

void LIFXDiscoveryClient::processIncomingDatagram(QByteArray datagram, QHostAddress sender, quint16 senderPort)
{
    LIFXPacket *packet = new LIFXPacket(datagram);

    switch (packet->header.packet_type)
    {
        case LIFX_GET_PAN_GATEWAY:
        cout << "LIFX_GET_PAN_GATEWAY" << endl;
        break;
        case LIFX_PAN_GATEWAY:
            if(!gateways.contains(sender.toString()))
            {
                cout << "New gateway received" << endl;
                LIFXGatewayClient *gateway = new LIFXGatewayClient(packet, sender, senderPort);
                gateway->setAddress(sender.toString());
                gateway->setDiscoveryClient(this);
                addGatewayClient(sender.toString(), gateway);
                //gateways.insert(sender.toString(), gateway); //direct insert misses Emit
                cout << "current # of gateways: " << gateways.count() << endl;
                emit newGatewayClient(gateway);
            }
            else
                cout << "known gateway received" << endl;
            cout << "LIFX_PAN_GATEWAY" << endl;
        break;
        case LIFX_GET_LIGHT_STATE:
        cout << "LIFX_GET_LIGHT_STATE" << endl;
        break;
        case LIFX_SET_LIGHT_COLOR:
        cout << "LIFX_SET_LIGHT_COLOR" << endl;
        break;
        case LIFX_LIGHT_STATUS:
            if(gateways.contains(sender.toString()))
            {
                LIFXGatewayClient *gateway = (QTIoT::LIFX::LIFXGatewayClient*)gateways[sender.toString()];
                QString lightaddress = (new QByteArray(packet->header.target_mac_address, 6))->toHex();

                LIFXLightClient* light = (LIFXLightClient* )gateway->getItem(lightaddress);
                if(light != NULL)
                {
                    light->setState(packet);
                }
                else
                {
                    /*LIFXLightClient */light = new LIFXLightClient(packet);
                    gateway->addItem(light);
                    cout << "lights found for this gateway: " << gateway->items.count() << endl;
                    light->getTime();
                    //light->setPower( !light->getPower());
                    //light->setColour(012,123,234);
                    addIoTItem(lightaddress, light);
                    emit newIoTItem(light);
                }
            }
            cout << "LIFX_LIGHT_STATUS" << endl;
        break;
        case LIFX_GET_POWER_STATE:
            cout << "LIFX_GET_POWER_STATE" << endl;
        break;
        case LIFX_SET_POWER_STATE:
        cout << "LIFX_SET_POWER_STATE" << endl;
        break;
        case LIFX_POWER_STATE:
            if(gateways.contains(sender.toString()))
            {

                LIFXGatewayClient *gateway = (QTIoT::LIFX::LIFXGatewayClient*)gateways[sender.toString()];
                QString lightaddress = (new QByteArray(packet->header.target_mac_address, 6))->toHex();

                LIFXLightClient* light = (LIFXLightClient* )gateway->getItem(lightaddress);
                if(light != NULL)
                {
                    LIFXPowerStatePayload *payload = (LIFXPowerStatePayload*)packet->payloaddata;
                    light->setPower_NoUpdate(payload->state);
                }
            }
            else if(items.contains(packet->header.target_mac_address)) // This not really covered yet...
            {
            }

            cout << "LIFX_POWER_STATE" << endl;
        break;
        case LIFX_GET_TIME:
        cout << "LIFX_GET_TIME" << endl;
        break;
        case LIFX_SET_TIME:
        cout << "LIFX_SET_TIME" << endl;
        break;
        case LIFX_TIME_STATE:
            if(gateways.contains(sender.toString()))
            {
                LIFXGatewayClient *gateway = (QTIoT::LIFX::LIFXGatewayClient*)gateways[sender.toString()];
                QString lightaddress = (new QByteArray(packet->header.target_mac_address, 6))->toHex();
                LIFXLightClient* light = (LIFXLightClient* )gateway->getItem(lightaddress);

                LIFXTimeStatePayload *payload = (LIFXTimeStatePayload*)packet->payloaddata;
                light->setTime_NoUpdate(payload->time);

                //light->setPower_NoUpdate(payload.state);
            }
            else if(items.contains(packet->header.target_mac_address)) // This not really covered yet...
            {
            }
        cout << "LIFX_TIME_STATE" << endl;
        break;
        case LIFX_GET_BULB_LABEL:
        cout << "LIFX_GET_BULB_LABEL" << endl;
        break;
        case LIFX_SET_BULB_LABEL:
        cout << "LIFX_SET_BULB_LABEL" << endl;
        break;
        case LIFX_BULB_LABEL:
        cout << "LIFX_BULB_LABEL" << endl;
        break;
        case LIFX_GET_BULB_TAGS:                // Tags - undecided
        cout << "LIFX_GET_BULB_TAGS" << endl;
        break;
        case LIFX_SET_BULB_TAGS:
        cout << "LIFX_SET_BULB_TAGS" << endl;
        break;
        case LIFX_BULB_TAGS:
        cout << "LIFX_BULB_TAGS" << endl;
        break;
        case LIFX_GET_BULB_TAG_LABELS:
        cout << "LIFX_GET_BULB_TAG_LABELS" << endl;
        break;
        case LIFX_SET_BULB_TAG_LABEL:
        cout << "LIFX_SET_BULB_TAG_LABEL" << endl;
        break;
        case LIFX_BULB_TAG_LABEL:               // Tags - undecided //
        cout << "LIFX_BULB_TAG_LABEL" << endl;
        break;
        case LIFX_GET_VERSION:
        cout << "LIFX_GET_VERSION" << endl;
        break;
        case LIFX_VERSION_STATE:
        cout << "LIFX_VERSION_STATE" << endl;
        break;
        case LIFX_GET_INFO:
        cout << "LIFX_GET_INFO" << endl;
        break;
        case LIFX_INFO_STATE:
        cout << "LIFX_INFO_STATE" << endl;
        break;
        case LIFX_GET_WIFI_INFO:
        cout << "LIFX_GET_WIFI_INFO" << endl;
        break;
        case LIFX_WIFI_INFO:
        cout << "LIFX_WIFI_INFO" << endl;
        break;
        case LIFX_SET_DIM_ABSOLUTE:
        cout << "LIFX_SET_DIM_ABSOLUTE" << endl;
        break;
        case LIFX_SET_DIM_RELATIVE:
        cout << "LIFX_SET_DIM_RELATIVE" << endl;
        break;
        case LIFX_GET_ACCESS_POINTS:                 // Need to decide how to handle these.
        cout << "LIFX_GET_ACCESS_POINT" << endl;
        break;
        case LIFX_SET_ACCESS_POINT:
        cout << "LIFX_SET_ACCESS_POINT" << endl;
        break;
        case LIFX_ACCESS_POINT:
        cout << "LIFX_ACCESS_POINT" << endl;
        break;
//        case value:
//        break;
    default: return ;
        break;
    }

}

/*
 * void Server::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        processTheDatagram(datagram);
    }
}
*/
/*
    QByteArray datagram = "Broadcast message " + QByteArray::number(messageNo);
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 45454);
*/

} // namespace LIFX
} // namespace QTIoT
