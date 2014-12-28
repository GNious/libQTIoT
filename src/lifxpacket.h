#ifndef QTIOT_LIFX_LIFXPACKET_H
#define QTIOT_LIFX_LIFXPACKET_H

#include <stdlib.h>
#include <QObject>

#include "lifxpayload.h"

namespace QTIoT {
namespace LIFX {

#pragma pack(push, 1)
typedef struct LIFXHeader
{
    //Adapted from https://github.com/magicmonkey/lifxjs/blob/master/Protocol.md
	quint16    size;           // LE
	quint16    protocol;
	quint32    reserved1;      // Always 0x0000
    char        target_mac_address[6];
	quint16    reserved2;      // Always 0x00
    char        site[6];        // MAC address of gateway PAN controller bulb
	quint16    reserved3;      // Always 0x00
	quint64    timestamp;
	quint16    packet_type;    // LE
	quint16    reserved4;
} LIFXHeader;
#pragma pack(pop)

class LIFXPacket : public QObject
{
    Q_OBJECT
public:
    explicit LIFXPacket(QObject *parent = 0);
    LIFXPacket(unsigned int packetType);
    LIFXPacket(QByteArray datagram);
    ~LIFXPacket();
    void init();

    LIFXHeader header;
    LIFXPayload *payload;
    void *payloaddata;
    unsigned int payloadsize;

    char *rawdata;

    char *toChar();
    bool setPacketType(unsigned int packetType);

signals:

public slots:

};

} // namespace LIFX
} // namespace QTIoT

#endif // QTIOT_LIFX_LIFXPACKET_H
