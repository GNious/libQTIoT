#ifndef QTIOT_LOGITECH_HARMONYDISCOVERYCLIENT_H
#define QTIOT_LOGITECH_HARMONYDISCOVERYCLIENT_H

//#include <QTIoT::IoTDiscoveryClient>
#include "iotdiscoveryclient.h"

namespace QTIoT {
namespace Logitech {

#define HARMONY_DISCOVERY_PORT 5224
#define HARMONY_LISTEN_PORT 5445
#define HARMONY_MDNS_NAME "_logitech-reverse-bonjour._tcp.local."
/*#pragma pack(push, 1)
struct HARMONYDiscoveryPacket
{
    char[38]    mDNS_address;
    char[5]     port;
    char[16]    IP;
};
#pragma pack(pop)*/


class HarmonyDiscoveryClient : public QTIoT::IoTDiscoveryClient
{
    Q_OBJECT
private:
    void processIncomingDatagram(QByteArray datagram, QHostAddress sender, quint16 senderPort);


private slots:
    void readPendingDatagrams();

public:
    HarmonyDiscoveryClient();

    QUdpSocket *udpSocket;// = NULL;
    QTcpSocket *tcpSocket;

    bool connectUDP();
    bool sendMessage(IoTObject *obj, void *msg);
    bool sendMessage(/*LIFXPacket *packet*/);
    Q_INVOKABLE bool discover();

signals:
    //void newGatewayClient(LIFXGatewayClient *client);
    //void newIoTItem(LIFXLightClient *item);
    void newGatewayClient(IoTGatewayClient *client);
    void newIoTItem(IoTObject *item);
};

} // namespace Logitech
} // namespace QTIoT

#endif // QTIOT_LOGITECH_HARMONYDISCOVERYCLIENT_H
