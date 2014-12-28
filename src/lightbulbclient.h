#ifndef QTIOT_LIGHTBULBCLIENT_H
#define QTIOT_LIGHTBULBCLIENT_H

#include "qtiot_global.h"
#include "qtiotconstants.h"

#include <QObject>
#include <QColor>

//#include "powerswitchclient.h"

namespace QTIoT {

class QTIOTSHARED_EXPORT IoTLightBulbClient //: public QObject //PowerSwitchClient //QObject
{
    //Q_ OBJECT

protected:
	int red, green, blue;
	QColor m_color;
    float brightness;
    int kelvin;
	int saturation;

	static int color255CheckI(int v){ return qMin(255, (qMax(0,v)));};


public:
    explicit IoTLightBulbClient();

//    virtual bool getPower() =0;
//    virtual bool setPower(bool state) =0;

    //Overload these to do actual stuff
	virtual void setColour(int red, int green, int blue){ setColour_NoUpdate(red, green, blue);}//=0;
    Q_INVOKABLE virtual void setColour(QColor color){ setColour_NoUpdate(color);}//=0;
	virtual void setBrightness(float brightnesspercent){ setBrightness_NoUpdate(brightnesspercent);}//=0;
    virtual void setTemperature(int kelvin){ setTemperature_NoUpdate(kelvin);}//=0;
	virtual void setColourAll(int red, int green, int blue, float brightnesspercent, int saturation, int kelvin);/*{ setColourAll_NoUpdate(red,green,blue,brightnesspercent,kelvin);}*///=0;
    virtual void setDimming(float dimpercent); /*{ brightness += dimpercent; if (brightness > 100) brightness = 100; if (brightness < 0) brightness = 0;  }*/ //=0;
    //Use these for internal updates
    virtual void setColour_NoUpdate(int red, int green, int blue); /*{ this->red = red; this->green = green; this->blue = blue;}*/ //=0;
    virtual void setColour_NoUpdate(QColor color); /*{ red = color.red(); green = color.green(); blue = color.blue(); brightness = color.lightness();}*/ //=0;
    virtual void setBrightness_NoUpdate(float brightnesspercent); /*{  brightness = brightnesspercent;}*/ //=0;
    virtual void setTemperature_NoUpdate(int kelvin); /*{ this->kelvin = kelvin;}*/ //=0;
    virtual void setSaturation(float saturation); /*{ QColor color = QColor::fromRgb(red, green, blue); QColor c2 = QColor::fromHslF(color.hslHueF(), saturation/100, color.lightnessF()); setColour_NoUpdate(c2);}*/  //=0;
	virtual void setColourAll_NoUpdate(int red, int green, int blue, float brightnesspercent, int saturation, int kelvin); /*{ this->red = red; this->green = green; this->blue = blue;brightness = brightnesspercent;this->kelvin = kelvin;}*///=0;
    //The read/get methods
    virtual QColor getColour(){ return m_color;};
    virtual int getTemperature(){ return this->kelvin;};
	virtual float getBrightness(){ return this->brightness;};
	virtual float getSaturation(){ return this->saturation;};

signals:
//public Q_SIGNALS:
    void    bulbRemoteChanged(QTIoT::IoTLightBulbClient*);
    void    bulbColorsChanged();

public slots:


};


} // namespace QTIoT

#endif // QTIOT_LIGHTBULBCLIENT_H
