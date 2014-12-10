#include "lifxpayload.h"



namespace QTIoT {
namespace LIFX {

LIFXPayload::LIFXPayload()
{
    this->payloadstruct = NULL;
    this->payloadsize = 0;
}

LIFXPayload::LIFXPayload(unsigned int packetType)
{
    LIFXPayload();
    setPacketType(packetType);
}

bool LIFXPayload::setPacketType(unsigned int packetType)
{
    //this->header->packet_type = packetType;

    switch (packetType)
    {
        case LIFX_GET_PAN_GATEWAY:
            if( this->payloadstruct != NULL)
                free(this->payloadstruct);
            this->payloadstruct = NULL;
            this->payloadsize = 0;
        break;
        case LIFX_PAN_GATEWAY:
            if( this->payloadstruct != NULL)
                free(this->payloadstruct);
            this->payloadsize = sizeof(LIFXPANGatewayPayload);
            this->payloadstruct = malloc(this->payloadsize);
        break;
        case LIFX_GET_LIGHT_STATE:
        break;
        case LIFX_SET_LIGHT_COLOR:
        break;
        case LIFX_LIGHT_STATUS:
        break;
        case LIFX_GET_POWER_STATE:
        break;
        case LIFX_SET_POWER_STATE:
        break;
        case LIFX_POWER_STATE:
        break;
        case LIFX_GET_TIME:
        break;
        case LIFX_SET_TIME:
        break;
        case LIFX_TIME_STATE:
        break;
        case LIFX_GET_BULB_LABEL:
        break;
        case LIFX_SET_BULB_LABEL:
        break;
        case LIFX_BULB_LABEL:
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
        break;
        case LIFX_SET_DIM_ABSOLUTE:
        break;
        case LIFX_SET_DIM_RELATIVE:
        break;
//        case value:
//        break;
    default: return false;
        break;
    }

    return false;
}


} // namespace LIFX
} // namespace QTIoT
