#ifndef LIGHTBULB_H
#define LIGHTBULB_H

#include "qtiot_global.h"

#include <QObject>

#include "iotobject.h"

namespace QTIoT {

class QTIOTSHARED_EXPORT LightBulb : public IoTObject //QObject
{
    Q_OBJECT
public:
    explicit LightBulb(QObject *parent = 0);

signals:

public slots:

};

}

#endif // LIGHTBULB_H
