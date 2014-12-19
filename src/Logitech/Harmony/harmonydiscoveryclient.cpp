#include "harmonydiscoveryclient.h"

#include <iostream>

namespace QTIoT {
namespace Logitech {

HarmonyDiscoveryClient::HarmonyDiscoveryClient():
    IoTDiscoveryClient()
{
    std::cout << "creating Harmony Discovery Client object " << std::endl;

    udpSocket = NULL;
}

bool HarmonyDiscoveryClient::connectUDP()
{
    std::cout << "Connecting port " << HARMONY_LISTEN_PORT << std::endl;
    udpSocket = new QUdpSocket(this);
    udpSocket->bind( HARMONY_LISTEN_PORT, QAbstractSocket::ShareAddress );
    tcpSocket = new QTcpSocket(this);
    tcpSocket->bind( HARMONY_LISTEN_PORT, QAbstractSocket::ShareAddress );

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
    connect(tcpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));

    return false;
}

bool HarmonyDiscoveryClient::sendMessage(IoTObject *obj, void *msg)
{
    if(udpSocket == NULL)
        connectUDP();

    return false;
}

bool HarmonyDiscoveryClient::sendMessage(/*IoTObject *obj, void *msg*/)
{
    if(udpSocket == NULL)
        connectUDP();

    return false;
}

bool HarmonyDiscoveryClient::discover()
{
    if(udpSocket == NULL)
        connectUDP();

    QString discover_str = HARMONY_MDNS_NAME;
    discover_str += "\n";
    discover_str += QString::number(HARMONY_LISTEN_PORT);
    /*discover_str += "\n";
    discover_str += "192.168.1.5";//QHostAddress("192.168.1.5");
    discover_str += "\nstring";*/

    QByteArray byteArray = discover_str.toLatin1();//toUtf8();
    const char* cString = byteArray.constData();

    //LIFXPacket *packet = new LIFXPacket( LIFX_GET_PAN_GATEWAY );
    //udpSocket->writeDatagram((char*)&(packet->header), packet->header.size, QHostAddress::Broadcast, LIFX_UDP_PORT);
    QUdpSocket *udpSendSocket = new QUdpSocket(this);
    std::cout << "sending data-stream: "<< cString << std::endl;
    udpSendSocket->writeDatagram( (char*) cString, discover_str.length(), QHostAddress::Broadcast, HARMONY_DISCOVERY_PORT);
    //udpSocket->writeDatagram( (char*) cString, discover_str.length(), QHostAddress("192.168.1.255"), HARMONY_DISCOVERY_PORT);


    std::cout << " data-stream sent " << std::endl;

    return false;
}

void HarmonyDiscoveryClient::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        std::cout << "Received Datagram! " << sender.toString().toUtf8().constData() << ":" << senderPort << std::endl;

        processIncomingDatagram(datagram, sender, senderPort);
    }
    while (tcpSocket->canReadLine())
    {
        std::cout << tcpSocket->readLine().constData() << std::endl;
    }
}

void HarmonyDiscoveryClient::processIncomingDatagram(QByteArray datagram, QHostAddress sender, quint16 senderPort)
{
   // LIFXPacket *packet = new LIFXPacket(datagram);

    /*switch (packet->header.packet_type)
    {
        case xxx:
        cout << "xxx" << endl;
        break;
        default: return ;
        break;
    }*/

}



} // namespace Logitech
} // namespace QTIoT
