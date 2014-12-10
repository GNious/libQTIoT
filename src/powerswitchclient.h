#ifndef POWERSWITCHCLIENT_H
#define POWERSWITCHCLIENT_H

#include "qtiot_global.h"
#include "qtiotconstants.h"

#include <QObject>

//#include "iotobject.h"

namespace QTIoT {

class QTIOTSHARED_EXPORT IoTPowerSwitchClient //: public  IoTObject //QObject
{
protected:
    //Q_OBJECT
public:
    bool power;
    explicit IoTPowerSwitchClient(QObject *parent = 0);

    virtual bool getPower(){return power;}//=0;
    virtual bool setPower(bool state) {return setPower_NoUpdate(state);}//=0;
    virtual bool setPower_NoUpdate(bool state) {power = state; return power;};

signals:
    void powerChanged(bool state);

public slots:

};
}

#endif // POWERSWITCHCLIENT_H
