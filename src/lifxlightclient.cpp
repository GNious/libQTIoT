#include <iostream>

#include "lifxlightclient.h"

namespace QTIoT {
namespace LIFX {

LIFXLightClient::LIFXLightClient(QObject *parent) :
    QTIoT::IoTObject(parent),
    QTIoT::IoTLightBulbClient(),
    QTIoT::IoTPowerSwitchClient(),
    QTIoT::IoTTimerClient()
{
}
LIFXLightClient::LIFXLightClient(LIFXPacket *packet, QObject *parent) :
    QTIoT::IoTObject(parent),
    QTIoT::IoTLightBulbClient(),
    QTIoT::IoTPowerSwitchClient(),
    QTIoT::IoTTimerClient()
{
    type |= QTIoTTypePowerSwitch + QTIoTTypeLightBulb + QTIoTTypeTimer;
    setAddress((new QByteArray(packet->header.target_mac_address, 6))->toHex());
    memcpy(m_addressraw, packet->header.target_mac_address, sizeof(packet->header.target_mac_address));

    LIFXLightStatusPayload *payload = (LIFXLightStatusPayload*)packet->payloaddata;
    setPower_NoUpdate(payload->power);
    setColour_NoUpdate( QColor::fromHsl(payload->hue/257, payload->saturation/257, payload->brightness/257) );
    setTemperature_NoUpdate(payload->kelvin);
    setBrightness_NoUpdate( payload->brightness / 655.35);
    setLabel_NoUpdate(payload->bulb_label);
	fadetime = 1;//100;

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
    memcpy(packet->header.target_mac_address, m_addressraw, sizeof(packet->header.target_mac_address));
    LIFXSetBulbLabelPayload *payload = (LIFXSetBulbLabelPayload*)packet->payloaddata;
    if(payload != NULL)
    {
        memcpy( payload->label, newLabel.toUtf8().constData(), newLabel.length());
        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
    }
	else
        std::cout << "failed to create LIFXPacket(LIFX_SET_BULB_LABEL)" << std::endl;

    return setLabel_NoUpdate(newLabel);
}

/*****************
** PowerSwitch  **
*****************/
bool LIFXLightClient::setPower(bool state)
{
    LIFXPacket *packet = new LIFXPacket(LIFX_SET_POWER_STATE);
    memcpy(packet->header.target_mac_address, m_addressraw, sizeof(packet->header.target_mac_address));
    LIFXSetPowerStatePayload *payload = (LIFXSetPowerStatePayload*)packet->payloaddata;
    if(payload != NULL)
    {
        payload->state = (LIFXPowerOnOff_t)state;
        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
    }
	else
        std::cout << "failed to create LIFXPacket(LIFX_SET_POWER_STATE)" << std::endl;

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
/*    LIFXPacket *packet = new LIFXPacket(LIFX_SET_DIM_ABSOLUTE);
    memcpy(packet->header.target_mac_address, m_addressraw, sizeof(packet->header.target_mac_address));
    LIFXSetDimAbsStatePayload *payload = (LIFXSetDimAbsStatePayload*)packet->payloaddata;
    if(payload != NULL)
    {
        payload->brightness = brightnesspercent * 655.35;
        payload->fade_time  = fadetime;

        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
    }
	else
        std::cout << "failed to create LIFXPacket(LIFX_SET_DIM_RELATIVE)" << std::endl;*/

	QTIoT::IoTLightBulbClient::setBrightness_NoUpdate(brightnesspercent);
	sendColour();
}
void LIFXLightClient::setSaturation(float saturation)
{
    QTIoT::IoTLightBulbClient::setSaturation(saturation);
    sendColour();
}
void LIFXLightClient::setTemperature(int kelvin)
{
	//QTIoT::IoTLightBulbClient::setTemperature_NoUpdate(kelvin);
	setColourAll(red, green, blue, brightness, 0, kelvin);
	//sendColour();
}
void LIFXLightClient::setColourAll(int red, int green, int blue, float brightnesspercent, int saturation, int kelvin)
{
    QTIoT::IoTLightBulbClient::setColourAll_NoUpdate( red, green, blue, brightnesspercent, saturation, kelvin);
    sendColour();
}
void LIFXLightClient::setDimming(float dimpercent)
{
    LIFXPacket *packet = new LIFXPacket(LIFX_SET_DIM_RELATIVE);
    memcpy(packet->header.target_mac_address, m_addressraw, sizeof(packet->header.target_mac_address));
    LIFXSetDimRelStatePayload *payload = (LIFXSetDimRelStatePayload*)packet->payloaddata;
    if(payload != NULL)
    {
        payload->brightness = dimpercent * 655.35;
        payload->fade_time  = fadetime;

        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
    }
	else
        std::cout << "failed to create LIFXPacket(LIFX_SET_DIM_RELATIVE)" << std::endl;

    QTIoT::IoTLightBulbClient::setDimming(dimpercent);
}
bool LIFXLightClient::sendColour()
{
    LIFXPacket *packet = new LIFXPacket(LIFX_SET_LIGHT_COLOR);
    memcpy(packet->header.target_mac_address, m_addressraw, sizeof(packet->header.target_mac_address));
    LIFXSetLightColorPayload *payload = (LIFXSetLightColorPayload*)packet->payloaddata;
    if(payload != NULL)
    {
		//QColor color = QColor::fromRgb(red, green, blue);
        //color.getHsl( *payload->hue, *payload->saturation, *payload->brightness);
		std::cout << "red " << red
				  << "- green " << green
				  << "- blue " << blue
				  << "- hue " << m_color.hslHue()
				  << "- sat " << this->saturation
				  << "- bri " << brightness
				  << "- kel " << kelvin
				  << std::endl;

        payload->stream     = 0;
		payload->hue        = static_cast<int>(m_color.hslHueF() * 65535);// color.hsvHue() *275;
		payload->saturation = static_cast<int>(saturation*256); // .hslSaturation()*257;
		payload->brightness = static_cast<int>(brightness * 655.35);//.lightness()*655.35);
        payload->kelvin     = kelvin;
		payload->fade_time  = fadetime;

/*		std::cout << "hue: " + (int)payload->hue <<
					 " sat: "+ (int)payload->saturation <<
					 " bri: "+ (int)payload->brightness <<
					 " tmp: "+ (int)payload->kelvin <<
					 " fad: "+ (int)payload->fade_time << std::endl;
*/
        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
        return true;
    }
    std::cout << "failed to create LIFXPacket(LIFX_SET_LIGHT_COLOR)" << std::endl;


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
    memcpy(packet->header.target_mac_address, m_addressraw, sizeof(packet->header.target_mac_address));
    LIFXSetTimeStatePayload *payload = (LIFXSetTimeStatePayload*)packet->payloaddata;
    if(payload != NULL)
    {
        payload->time = timesec;
        ((LIFXGatewayClient*)gatewayclient)->SendPacket(packet);
        return true;
    }

    return false;
}


/** Util **/

} // namespace LIFX
} // namespace QTIoT
