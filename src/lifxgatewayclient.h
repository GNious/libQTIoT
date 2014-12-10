#ifndef QTIOT_LIFX_LIFXGATEWAYCLIENT_H
#define QTIOT_LIFX_LIFXGATEWAYCLIENT_H

#include <QMap>
#include <QUdpSocket>

#include "iotgatewayclient.h"
#include "lifxpacket.h"

namespace QTIoT {
namespace LIFX {

class LIFXGatewayClient : public QTIoT::IoTGatewayClient
{
    Q_OBJECT
private:
    char site[6];
    QUdpSocket *udpSocket;

    QHostAddress hostaddress;
    quint16 hostport;


public:
    explicit LIFXGatewayClient(QObject *parent = 0);
    LIFXGatewayClient(LIFXPacket *packet, QHostAddress address, quint16 port);
    //LIFXGatewayClient(LIFXPacket *packet);

    bool SendPacket(LIFXPacket *packet);

signals:

public slots:

};

} // namespace LIFX
} // namespace QTIoT

#endif // QTIOT_LIFX_LIFXGATEWAYCLIENT_H
