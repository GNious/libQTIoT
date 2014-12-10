#include "lifxlightclient.h"

namespace QTIoT {
namespace LIFX {

LIFXLightClient::LIFXLightClient(QObject *parent) :
    QTIoT::IoTLightBulbClient(parent)
{
}
LIFXLightClient::LIFXLightClient(LIFXPacket *packet) :
    QTIoT::IoTLightBulbClient(),
    QTIoT::IoTPowerSwitchClient(),
    QTIoT::IoTTimerClient()
{
    type |= QTIoTTypePowerSwitch + QTIoTTypeLightBulb + QTIoTTypeTimer;
    setAddress((new QByteArray(packet->header.target_mac_address, 6))->toHex());

    LIFXLightStatusPayload *payload = (LIFXLightStatusPayload*)packet->payloaddata;
    setPower_NoUpdate(payload->power);
    setColour_NoUpdate( QColor::fromHsl(payload->hue/257, payload->saturation/257, payload->brightness/257) );
    setTemperature_NoUpdate(payload->kelvin);
    setBrightness_NoUpdate( payload->brightness / 655.35);
    setLabel_NoUpdate(payload->bulb_label);
    fadetime = 100;

}
bool LIFXLightClient::setState(LIFXPacket *packet)
{

    QString address = (new QByteArray(packet->header.target_mac_address, 6))->toHex();

    if(address == getAddress())
    {
        switch (packet->header.packet_type)
        {
            case LIFX_LIGHT_STATUS:
                LIFXLightStatusPayload *payload = (LIFXLightStatusPayload*)packet->payloaddata;
                setPower_NoUpdate(payload->power);
                setColour_NoUpdate( QColor::fromHsl(payload->hue/257, payload->saturation/257, payload->brightness/655.35) );
                setTemperature_NoUpdate(payload->kelvin);
                setBrightness_NoUpdate( payload->brightness / 655.35);
                setLabel_NoUpdate(payload->bulb_label);
                emit bulbRemoteChanged(this);
                return true;
            break;
        }
    }
    return false;
}
QString LIFXLightClient::setLabel(QString newLabel)
{
    LIFXPacket *packet = new LIFXPacket(LIFX_SET_BULB_LABEL);
    LIFXSetBulbLabelPayload *payload = (LIFXSetBulbLabelPayload*)packet->payloaddata;
    if(payload != NULL)
    {
        memcpy( payload->label, newLabel.toUtf8().constData(), newLabel.length());
        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
    }

    return setLabel_NoUpdate(newLabel);
}

/*****************
** PowerSwitch  **
*****************/
bool LIFXLightClient::setPower(bool state)
{
    LIFXPacket *packet = new LIFXPacket(LIFX_SET_POWER_STATE);
    LIFXSetPowerStatePayload *payload = (LIFXSetPowerStatePayload*)packet->payloaddata;
    if(payload != NULL)
    {
        payload->state = (LIFXPowerOnOff_t)state;
        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
    }

    QTIoT::IoTPowerSwitchClient::setPower_NoUpdate(state);
    return state;
}
/*****************
** Lightbulb    **
*****************/
void LIFXLightClient::setColour(int red, int green, int blue)
{
    QTIoT::IoTLightBulbClient::setColour_NoUpdate(red, green, blue);
    sendColour();
}
void LIFXLightClient::setColour(QColor color)
{
    QTIoT::IoTLightBulbClient::setColour_NoUpdate(color);
    sendColour();
}
void LIFXLightClient::setBrightness(float brightnesspercent)
{
    LIFXPacket *packet = new LIFXPacket(LIFX_SET_DIM_ABSOLUTE);
    LIFXSetDimAbsStatePayload *payload = (LIFXSetDimAbsStatePayload*)packet->payloaddata;
    if(payload != NULL)
    {
        payload->brightness = brightnesspercent * 655.35;
        payload->fade_time  = fadetime;

        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
    }
    QTIoT::IoTLightBulbClient::setBrightness_NoUpdate(brightnesspercent);
    //sendColour();
}
void LIFXLightClient::setTemperature(int kelvin)
{
    QTIoT::IoTLightBulbClient::setTemperature_NoUpdate(kelvin);
    sendColour();
}
void LIFXLightClient::setColourAll(int red, int green, int blue, float brightnesspercent, int kelvin)
{
    QTIoT::IoTLightBulbClient::setColourAll_NoUpdate( red, green, blue, brightnesspercent, kelvin);
}
void LIFXLightClient::setDimming(float dimpercent)
{
    LIFXPacket *packet = new LIFXPacket(LIFX_SET_DIM_RELATIVE);
    LIFXSetDimRelStatePayload *payload = (LIFXSetDimRelStatePayload*)packet->payloaddata;
    if(payload != NULL)
    {
        payload->brightness = dimpercent * 655.35;
        payload->fade_time  = fadetime;

        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
    }
    QTIoT::IoTLightBulbClient::setDimming(dimpercent);
}
bool LIFXLightClient::sendColour()
{
    LIFXPacket *packet = new LIFXPacket(LIFX_SET_LIGHT_COLOR);
    LIFXSetLightColorPayload *payload = (LIFXSetLightColorPayload*)packet->payloaddata;
    if(payload != NULL)
    {
        QColor color = QColor::fromRgb(red, green, blue);
        //color.getHsl( *payload->hue, *payload->saturation, *payload->brightness);

        payload->stream     = 0;
        payload->hue        = color.hslHue() *275;
        payload->saturation = color.hslSaturation()*257;
        payload->brightness = color.lightness()*655.35;
        payload->kelvin     = kelvin;
        payload->fade_time  = fadetime;

        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
        return true;
    }

    return false;
}
/*****************
** Timer        **
*****************/
long LIFXLightClient::setTime(long newTime)
{
    QTIoT::IoTTimer::setTime_NoUpdate(newTime);
    sendTime();
    return timesec;
}
long LIFXLightClient::setTime(QDateTime newTime)
{
    QTIoT::IoTTimer::setTime_NoUpdate(newTime.toTime_t());
    sendTime();
    return timesec;
}
bool LIFXLightClient::sendTime()
{
    LIFXPacket *packet = new LIFXPacket(LIFX_SET_TIME);
    LIFXSetTimeStatePayload *payload = (LIFXSetTimeStatePayload*)packet->payloaddata;
    if(payload != NULL)
    {
        payload->time = timesec;
        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
        return true;
    }

    return false;
}

} // namespace LIFX
} // namespace QTIoT
