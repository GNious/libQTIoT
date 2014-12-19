#ifndef QTIOT_LOGITECH_HARMONYGATEWAYCLIENT_H
#define QTIOT_LOGITECH_HARMONYGATEWAYCLIENT_H

#include <qtcpsocket.h>
#include <qhostaddress.h>

//#include <QTIoT::GatewayClient>
#include "iotgatewayclient.h"

namespace QTIoT {
namespace Logitech {

class HarmonyGatewayClient : public QTIoT::IoTGatewayClient
{
    Q_OBJECT
private:
    char site[6];
    QTcpSocket *tcpSocket;

    QHostAddress hostaddress;
    quint16 hostport;
public:
    explicit HarmonyGatewayClient(QObject *parent = 0);
    HarmonyGatewayClient(QHostAddress address, quint16 port);

signals:

public slots:

};

} // namespace Logitech
} // namespace QTIoT

#endif // QTIOT_LOGITECH_HARMONYGATEWAYCLIENT_H

#include <QMap>
#include <QUdpSocket>

#include "iotgatewayclient.h"
#include "lifxpacket.h"


