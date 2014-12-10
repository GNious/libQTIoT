#include "lifxpacket.h"

namespace QTIoT {
namespace LIFX {

LIFXPacket::LIFXPacket(QObject *parent) :
    QObject(parent)
{
}
LIFXPacket::LIFXPacket(unsigned int packetType)
{
    this->init();
    setPacketType(packetType);
}
LIFXPacket::LIFXPacket(QByteArray datagram)
{
    this->init();
    memcpy((void*)(&this->header), datagram.data(), sizeof(LIFXHeader));
    setPacketType(header.packet_type);
    if(payloadsize > 0)
        memcpy(payloaddata, datagram.data()+sizeof(LIFXHeader)  , payloadsize);

}
LIFXPacket::~LIFXPacket()
{
    if(payloaddata != NULL)
        free(payloaddata);
    payloaddata = NULL;
}
void LIFXPacket::init()
{
    memset((void*)&(this->header), 0, sizeof(LIFXHeader));
    this->header.size = sizeof(LIFXHeader);
    this->header.protocol = 0x3400;
/*    this->header.reserved1 = 0x0000;
    memset(this->header.target_mac_address, 0, 6);
    this->header.reserved2 = 0x0000;
    memset(this->header.site, 0, 6);
    this->header.reserved3 = 0x0000;
    this->header.timestamp = 0;
    this->header.packet_type = 0;
    this->header.reserved4 = 0x0000;

/*    if payload is None:
        self.payload = LIFXPayload()
    else:
        self.payload = payload*/
    //this->payload = new LIFXPayload();
    this->payloaddata = NULL;
    this->payloadsize = 0;
    this->rawdata = NULL;
}


bool LIFXPacket::setPacketType(unsigned int packetType)
{
    this->header.packet_type = packetType;
    payloadsize = 0;

    switch (packetType)
    {
        case LIFX_GET_PAN_GATEWAY:
        break;
        case LIFX_PAN_GATEWAY:
            payloadsize = sizeof(LIFXPANGatewayPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_GET_LIGHT_STATE:
        break;
        case LIFX_SET_LIGHT_COLOR:
            payloadsize = sizeof(LIFXSetLightColorPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_LIGHT_STATUS:
            payloadsize = sizeof(LIFXLightStatusPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_GET_POWER_STATE:
        break;
        case LIFX_SET_POWER_STATE:
            payloadsize = sizeof(LIFXSetPowerStatePayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_POWER_STATE:
            payloadsize = sizeof(LIFXPowerStatePayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_GET_TIME:
        break;
        case LIFX_SET_TIME:
            payloadsize = sizeof(LIFXSetTimeStatePayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_TIME_STATE:
            payloadsize = sizeof(LIFXTimeStatePayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_GET_BULB_LABEL:
        break;
        case LIFX_SET_BULB_LABEL:
            payloadsize = sizeof(LIFXSetBulbLabelPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_BULB_LABEL:
            payloadsize = sizeof(LIFXBulbLabelPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_GET_BULB_TAGS:
        break;
        case LIFX_SET_BULB_TAGS:
            payloadsize = sizeof(LIFXSetTagsPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_BULB_TAGS:
            payloadsize = sizeof(LIFXTagsPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_GET_BULB_TAG_LABELS:
            payloadsize = sizeof(LIFXGetTagLabelsPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_SET_BULB_TAG_LABEL:
            payloadsize = sizeof(LIFXSetTagLabelsPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_BULB_TAG_LABEL:
            payloadsize = sizeof(LIFXTagLabelPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_GET_VERSION:
        break;
        case LIFX_VERSION_STATE:
        break;
        case LIFX_GET_INFO:
        break;
        case LIFX_INFO_STATE:
        break;
        case LIFX_GET_WIFI_INFO:
        break;
        case LIFX_WIFI_INFO:
            payloadsize = sizeof(LIFXWifiStatePayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_SET_DIM_ABSOLUTE:
            payloadsize = sizeof(LIFXSetDimAbsStatePayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_SET_DIM_RELATIVE:
            payloadsize = sizeof(LIFXSetDimRelStatePayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_GET_ACCESS_POINTS:
        break;
        case LIFX_SET_ACCESS_POINT:
            payloadsize = sizeof(LIFXSetAccessPointPayload);
            payloaddata = calloc(1, payloadsize );
        break;
        case LIFX_ACCESS_POINT:
            payloadsize = sizeof(LIFXAccessPointPayload);
            payloaddata = calloc(1, payloadsize );
//        case value:
//        break;
    default: return false;
        break;
    }

    header.size = sizeof(LIFXHeader) + payloadsize;

    return true;
}

char *LIFXPacket::toChar()
{
//    if(this->rawdata == NULL)
//        this->rawdata = (char*)malloc( sizeof(LIFXHeader) + this->payload->payloadsize);

    unsigned int headersize = sizeof(LIFXHeader);
    unsigned int rawdatasize = headersize + this->payloadsize;
    //this->rawdata = NULL;
    if(this->rawdata == NULL)
        this->rawdata = (char*)calloc(1, rawdatasize);  //sizeof(LIFXHeader) + this->payloadsize
    else
        this->rawdata = (char*)realloc(this->rawdata, rawdatasize); //sizeof(LIFXHeader) + this->payloadsize

    if(this->rawdata == NULL)
        return NULL;

    memcpy(this->rawdata, &this->header, sizeof(LIFXHeader));
    if(this->payloadsize > 0)
        memcpy((this->rawdata+sizeof(LIFXHeader)), this->payloaddata, this->payloadsize);

    return this->rawdata;

    //return NULL;
}

} // namespace LIFX
} // namespace QTIoT
