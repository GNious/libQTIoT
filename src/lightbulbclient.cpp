#include "lightbulbclient.h"

namespace QTIoT {

IoTLightBulbClient::IoTLightBulbClient() //:
{
}

void IoTLightBulbClient::setColourAll(int red, int green, int blue, float brightnesspercent, int saturation, int kelvin)
{
	setColourAll_NoUpdate(red, green, blue, brightnesspercent, saturation, kelvin);
}//=0;
void IoTLightBulbClient::setDimming(float dimpercent)
{
	brightness += dimpercent;
	if (brightness > 100)
		brightness = 100;
	if (brightness < 0)
		brightness = 0;
}//=0;
//Use these for internal updates
void IoTLightBulbClient::setColour_NoUpdate(int red, int green, int blue)
{
    this->setColourAll_NoUpdate(red, green, blue, brightness, saturation, kelvin );
	return;

	this->red = red;
	this->green = green;
	this->blue = blue;
}//=0;
void IoTLightBulbClient::setColour_NoUpdate(QColor color)
{
    //this->setColourAll_NoUpdate(color.red(), color.green(), color.blue(), color.lightness(), color.saturation(), kelvin );
    this->setColourAll_NoUpdate(color.red(), color.green(), color.blue(), this->brightness, this->saturation, kelvin );
    return;

	red = color.red();
	green = color.green();
	blue = color.blue();
	brightness = color.lightness();
}//=0;
void IoTLightBulbClient::setBrightness_NoUpdate(float brightnesspercent)
{
	this->setColourAll_NoUpdate(red, green, blue, brightnesspercent, saturation, kelvin );
	return;

	brightness = brightnesspercent;
}//=0;
void IoTLightBulbClient::setTemperature_NoUpdate(int kelvin)
{
	this->kelvin = kelvin;
}//=0;
void IoTLightBulbClient::setSaturation(float saturation)
{
	this->setColourAll_NoUpdate(red, green, blue, brightness, saturation, kelvin );
	return;

	QColor color = QColor::fromRgb(red, green, blue);
	QColor c2 = QColor::fromHslF(color.hslHueF(), saturation/100, color.lightnessF());
	setColour_NoUpdate(c2);
}//=0;
void IoTLightBulbClient::setColourAll_NoUpdate(int red, int green, int blue, float brightnesspercent, int saturation, int kelvin)
{
	this->red	= color255CheckI(red);
	this->green = color255CheckI(green);
	this->blue	= color255CheckI(blue);
	this->brightness = brightnesspercent;
	this->saturation = color255CheckI(saturation);
	this->kelvin = kelvin;
	QColor c = QColor::fromRgb( this->red, this->green, this->blue);
	this->m_color = QColor::fromHsl( c.hue(), this->saturation, 2.55*brightnesspercent);
}//=0;
//The read/get methods



} // namespace QTIoT
