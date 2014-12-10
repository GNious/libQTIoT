#ifndef IOTGATEWAY_H
#define IOTGATEWAY_H

#include "qtiot_global.h"

#include <QObject>

namespace QTIoT {

class QTIOTSHARED_EXPORT IoTGateway : public QObject
{
    Q_OBJECT
public:
    explicit IoTGateway(QObject *parent = 0);

signals:

public slots:

};
}

#endif // IOTGATEWAY_H
