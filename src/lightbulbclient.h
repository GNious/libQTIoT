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
    float brightness;
    int kelvin;
public:
    explicit IoTLightBulbClient(QObject *parent = 0);

//    virtual bool getPower() =0;
//    virtual bool setPower(bool state) =0;

    //Overload these to do actual stuff
    virtual void setColour(int red, int green, int blue){ setColour_NoUpdate(red, green, blue);}//=0;
    Q_INVOKABLE virtual void setColour(QColor color){ setColour_NoUpdate(color);}//=0;
    virtual void setBrightness(float brightnesspercent){ setBrightness_NoUpdate(brightnesspercent);}//=0;
    virtual void setTemperature(int kelvin){ setTemperature_NoUpdate(kelvin);}//=0;
    virtual void setColourAll(int red, int green, int blue, float brightnesspercent, int kelvin){ setColourAll_NoUpdate(red,green,blue,brightnesspercent,kelvin);}//=0;
    virtual void setDimming(float dimpercent){ brightness += dimpercent; if (brightness > 100) brightness = 100; if (brightness < 0) brightness = 0;  }//=0;
    //Use these for internal updates
    virtual void setColour_NoUpdate(int red, int green, int blue) { this->red = red; this->green = green; this->blue = blue;}//=0;
    virtual void setColour_NoUpdate(QColor color){ red = color.red(); green = color.green(); blue = color.blue(); brightness = color.lightness();}//=0;
    virtual void setBrightness_NoUpdate(float brightnesspercent){  brightness = brightnesspercent;}//=0;
    virtual void setTemperature_NoUpdate(int kelvin){ this->kelvin = kelvin;}//=0;
    virtual void setColourAll_NoUpdate(int red, int green, int blue, float brightnesspercent, int kelvin) { this->red = red; this->green = green; this->blue = blue;brightness = brightnesspercent;this->kelvin = kelvin;}//=0;
    //The read/get methods
    virtual QColor getColour(){ return QColor::fromRgb(red, green, blue);};
    virtual int getTemperature(){ return this->kelvin;};
    virtual float getBrightness(){ return this->brightness;};

signals:
//public Q_SIGNALS:
    void    bulbRemoteChanged(QTIoT::IoTLightBulbClient*);
    void    bulbColorsChanged();

public slots:


};

} // namespace QTIoT

#endif // QTIOT_LIGHTBULBCLIENT_H
