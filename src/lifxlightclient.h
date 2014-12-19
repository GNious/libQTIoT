#ifndef QTIOT_LIFX_LIFXLIGHTCLIENT_H
#define QTIOT_LIFX_LIFXLIGHTCLIENT_H

#include <QColor>

#include "lightbulbclient.h"
#include "powerswitchclient.h"
#include "iottimerclient.h"
#include "lifxpacket.h"
#include "lifxgatewayclient.h"

namespace QTIoT {
namespace LIFX {

class LIFXLightClient : public QTIoT::IoTObject,
                        public QTIoT::IoTLightBulbClient,
                        public QTIoT::IoTPowerSwitchClient,
                        public QTIoT::IoTTimerClient
{
    Q_OBJECT
    Q_PROPERTY(QString label READ getLabel WRITE setLabel )
    Q_PROPERTY(QColor colour READ getColour WRITE setColour NOTIFY bulbColorsChanged )
    Q_PROPERTY(qint16 temperature READ getTemperature WRITE setTemperature )
    Q_PROPERTY(float brightness READ getBrightness WRITE setDimming )
    Q_PROPERTY(bool power READ getPower WRITE setPower NOTIFY powerChanged)
    Q_PROPERTY(QDateTime time READ getTimeQDateTime WRITE setTime NOTIFY timeChanged)
//    Q_PROPERTY(QString label READ getLabel WRITE setLabel NOTIFY labelChanged)


private:
    float fadetime;
    QString label;
    int64_t    time; //since Epoc Jan 1st, 1970
    char m_addressraw[6];

    bool sendColour();
    bool sendTime();


public:
    explicit LIFXLightClient(QObject *parent = 0);
    LIFXLightClient( LIFXPacket *packet );

    bool setState(LIFXPacket *packet);
    //LIFX-specific set/get functions
    QString setLabel(QString newLabel);
    QString setLabel_NoUpdate(QString newLabel){ label = newLabel; return label;};
    QString getLabel(){return label;};

    //Overloaded or required by parent classes
    //1. IoT-PowerSwitch
   Q_INVOKABLE bool setPower(bool state);

    //2. IoT-Lightbulb
    void setColour(int red, int green, int blue);
    Q_INVOKABLE void setColour(QColor color);
    Q_INVOKABLE void setBrightness(float brightnesspercent);
    Q_INVOKABLE void setTemperature(int kelvin);
    Q_INVOKABLE void setColourAll(int red, int green, int blue, float brightnesspercent, int kelvin);
    Q_INVOKABLE void setDimming(float dimpercent);

    //3. IoT-Timer
    long setTime(long newTime);
    long setTime(QDateTime newTime);



    //LIFXGatewayClient *gatewayclient;
signals:
    //From IoTLightbulbClient
    void bulbRemoteChanged(IoTLightBulbClient *);
    void    bulbColorsChanged();
    //From IoTPowerSwitchClient
    void powerChanged(bool state);
    //From IoTTimerClient
    void timeChanged(QDateTime newTime);
public slots:

};

} // namespace LIFX
} // namespace QTIoT

#endif // QTIOT_LIFX_LIFXLIGHTCLIENT_H
