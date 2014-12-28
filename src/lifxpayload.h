#ifndef QTIOT_LIFX_LIFXPAYLOAD_H
#define QTIOT_LIFX_LIFXPAYLOAD_H

#include <QObject>

namespace QTIoT {
namespace LIFX {

class LIFXPayload
{
public:
    LIFXPayload();
    LIFXPayload(unsigned int packetType);

    void *payloadstruct;
    unsigned int payloadsize;


    bool setPacketType(unsigned int packetType);
};

/*#define LIFXNetworkUDP 1
#define LIFXNetworkTCP 2
typedef enum LIFXNetworkService : char {
    LIFXNetworkUDP,
    LIFXNetworkTCP
}LIFXNetworkService;*/
enum LIFXNetworkService_t
{
    LIFXNetworkUDP   = 1,
    LIFXNetworkTCP   = 2
};
enum  LIFXPowerOnOff_t
{
    LIFXOFF  = 0,
    LIFXON   = 1
};
enum LIFXNetworkWifiType_t
{
  SOFT_AP = 1, // i.e. act as an access point
  STATION = 2  // i.e. connect to an existing access point
};
enum LIFXNetworkSecurityProtocol_t //: byte
{
   OPEN           = 1,
   WEP_PSK        = 2, // Not officially supported
   WPA_TKIP_PSK   = 3,
   WPA_AES_PSK    = 4,
   WPA2_AES_PSK   = 5,
   WPA2_TKIP_PSK  = 6,
   WPA2_MIXED_PSK = 7
};

#pragma pack(push, 1)
typedef struct LIFXPANGatewayPayload
{
    LIFXNetworkService_t service;
	quint32 port;
} LIFXPANGatewayPayload;
typedef struct LIFXLightStatusPayload
{
	quint16 hue;          // LE
	quint16 saturation;   // LE
	quint16 brightness;   // LE
	quint16 kelvin;       // LE
	quint16 dim;          // LE?
	quint16 power;
    char bulb_label[32]; // UTF-8 encoded string
	quint64 tags;
} LIFXLightStatusPayload;
typedef struct LIFXSetPowerStatePayload
{
    LIFXPowerOnOff_t state;
} LIFXSetPowerStatePayload;
typedef struct LIFXPowerStatePayload
{
    LIFXPowerOnOff_t state;
} LIFXPowerStatePayload;
typedef struct LIFXSetLightColorPayload
{
    char        stream;     // Unknown, potential "streaming" mode toggle? Set to 0x00 for now.
	quint16    hue;        // LE NOTE: Wraps around at 0xff 0xff back to 0x00 0x00, which is a primary red colour
	quint16    saturation; // LE
	quint16    brightness; // LE
	quint16    kelvin;     // LE i.e. colour temperature (whites wheel in apps)
	quint32    fade_time;  // LE Length of fade action, in seconds
} LIFXSetLightColorPayload;
typedef struct LIFXSetTimeStatePayload
{
	quint64    time;
} LIFXSetTimeStatePayload;
typedef struct LIFXTimeStatePayload
{
	quint64    time;
} LIFXTimeStatePayload;
typedef struct LIFXSetDimAbsStatePayload
{
	qint16     brightness;
	quint32    fade_time;  // LE Length of fade action, in seconds
} LIFXSetDimAbsStatePayload;
typedef struct LIFXSetDimRelStatePayload
{
	qint16     brightness;
	quint32    fade_time;  // LE Length of fade action, in seconds
} LIFXSetDimRelStatePayload;
typedef struct LIFXSetBulbLabelPayload
{
    char        label[32]; // UTF-8 encoded string
} LIFXSetBulbLabelPayload;
typedef struct LIFXBulbLabelPayload
{
    char        label[32]; // UTF-8 encoded string
} LIFXBulbLabelPayload;


typedef struct LIFXSetTagsPayload
{
	quint64    tags;
} LIFXSetTagsPayload;
typedef struct LIFXTagsPayload
{
	quint64    tags;
} LIFXTagsPayload;
typedef struct LIFXGetTagLabelsPayload
{
	quint64    tags;
} LIFXGetTagLabelsPayload;
typedef struct LIFXSetTagLabelsPayload
{
	quint64    tags;
    char        label[32]; // UTF-8 encoded string
} LIFXSetTagLabelsPayload;
typedef struct LIFXTagLabelPayload
{
	quint64    tags;
    char        label[32]; // UTF-8 encoded string
} LIFXTagLabelPayload;


typedef struct LIFXVersionStatePayload
{
	quint32    vendor;
	quint32    product;
	quint32    version;
} LIFXVersionStatePayload;
typedef struct LIFXInfoStatePayload
{
	quint64    time;      // LE
	quint64    uptime;    // LE
	quint64    downtime;  // LE
} LIFXInfoStatePayload;


typedef struct LIFXWifiStatePayload
{
    float signal;   // LE
    int32_t tx;     // LE
    int32_t rx;     // LE
    short mcu_temperature;
} LIFXWifiStatePayload;



typedef struct LIFXSetAccessPointPayload
{
    LIFXNetworkWifiType_t interface;  // Byte
    char ssid[32];      // UTF-8 encoded string
    char password[64];  // UTF-8 encoded string
    LIFXNetworkSecurityProtocol_t security_protocol; // Byte
} LIFXSetAccessPointPayload;
typedef struct LIFXAccessPointPayload  //No Yet Modelled!!
{
    LIFXNetworkWifiType_t interface;  // Byte
    char ssid[32];                    // UTF-8 encoded string
    LIFXNetworkSecurityProtocol_t security_protocol; // Byte
	quint16 strength;
	quint16 channel;
} LIFXAccessPointPayload;
#pragma pack(pop)








/*
class LIFXPayload
{
public:
    LIFXPayload();
};


class GetPANGatewayPayload : public LIFXPayload
{
public:
    GetPANGatewayPayload();
};


class PANGatewayPayload : public LIFXPayload
{
public:
    PANGatewayPayload();
};

class GetLightStatePayload : public LIFXPayload

class SetLightColorPayload : public LIFXPayload

class LightStatusPayload : public LIFXPayload

class GetPowerStatePayload : public LIFXPayload)

class SetPowerStatePayload : public LIFXPayload)

class PowerStatePayload : public SetPowerStatePayload

class GetTimeStatePayload : public LIFXPayload

class SetTimeStatePayload : public LIFXPayload

class TimeStatePayload : public LIFXPayload

class GetBulbLabelPayload : public LIFXPayload

class SetBulbLabelPayload : public LIFXPayload

class BulbLabelPayload : public LIFXPayload

class GetVersionPayload : public LIFXPayload

class VersionStatePayload : public LIFXPayload

class GetInfoPayload : public LIFXPayload

class InfoStatePayload : public LIFXPayload

class InfoStatePayload : public LIFXPayload

#GET_WIFI_INFO = 0x10
class GetWifiInfoPayload : public LIFXPayload

#WIFI_INFO = 0x11
class WifiStatePayload : public LIFXPayload

#SET_DIM_ABSOLUTE = 0x68
class SetDimAbsStatePayload : public LIFXPayload


#SET_DIM_RELATIVE = 0x69
class SetDimRelStatePayload : public LIFXPayload
*/


#define LIFX_GET_PAN_GATEWAY    0x02
#define LIFX_PAN_GATEWAY        0x03
#define LIFX_GET_LIGHT_STATE    0x65
#define LIFX_SET_LIGHT_COLOR    0x66
#define LIFX_LIGHT_STATUS       0x6b
#define LIFX_GET_POWER_STATE    0x14
#define LIFX_SET_POWER_STATE    0x15
#define LIFX_POWER_STATE        0x16
#define LIFX_GET_TIME           0x04
#define LIFX_SET_TIME           0x05
#define LIFX_TIME_STATE         0x06
#define LIFX_GET_BULB_LABEL     0x17
#define LIFX_SET_BULB_LABEL     0x18
#define LIFX_BULB_LABEL         0x19
#define LIFX_GET_BULB_TAGS      0x1A
#define LIFX_SET_BULB_TAGS      0x1B
#define LIFX_BULB_TAGS          0x1C
#define LIFX_GET_BULB_TAG_LABELS 0x1D
#define LIFX_SET_BULB_TAG_LABEL 0x1E
#define LIFX_BULB_TAG_LABEL     0x1F
#define LIFX_GET_VERSION        0x20
#define LIFX_VERSION_STATE      0x21
#define LIFX_GET_INFO           0x22
#define LIFX_INFO_STATE         0x23
#define LIFX_GET_WIFI_INFO      0x10
#define LIFX_WIFI_INFO          0x11
#define LIFX_SET_DIM_ABSOLUTE   0x68
#define LIFX_SET_DIM_RELATIVE   0x69
#define LIFX_GET_ACCESS_POINTS  0x130
#define LIFX_SET_ACCESS_POINT   0x131
#define LIFX_ACCESS_POINT       0x132




} // namespace LIFX
} // namespace QTIoT

#endif // QTIOT_LIFX_LIFXPAYLOAD_H
