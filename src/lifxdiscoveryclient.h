#ifndef QTIOT_LIFX_LIFXDISCOVERYCLIENT_H
#define QTIOT_LIFX_LIFXDISCOVERYCLIENT_H

#include <QUdpSocket>

#include "iotdiscoveryclient.h"
#include "lifxpacket.h"
#include "lifxgatewayclient.h"
#include "lifxlightclient.h"

namespace QTIoT {
namespace LIFX {

#define LIFX_UDP_PORT 56700


class LIFXDiscoveryClient : public IoTDiscoveryClient
{
    Q_OBJECT
private:
    void processIncomingDatagram(QByteArray datagram, QHostAddress sender, quint16 senderPort);


private slots:
    void readPendingDatagrams();
    //void timingDiscovery();

public:
	LIFXDiscoveryClient();
	~LIFXDiscoveryClient();

    QUdpSocket *udpSocket;// = NULL;

    bool connectUDP();
    bool sendMessage(IoTObject *obj, void *msg);
//    bool sendMessage(LIFXPacket *packet);
    Q_INVOKABLE bool discover();
    //Q_INVOKABLE bool startDiscoveryTimer(int waitMs = 10000);
    //Q_INVOKABLE bool endDiscoveryTimer();

signals:
    void newGatewayClient(LIFXGatewayClient *client);
    void newIoTItem(LIFXLightClient *item);


};




} // namespace LIFX
} // namespace QTIoT

#endif // QTIOT_LIFX_LIFXDISCOVERYCLIENT_H
