#ifndef QTIOT_IOTOBJECT_H
#define QTIOT_IOTOBJECT_H

#include "qtiot_global.h"

#include <QObject>
#include <QString>

#include "iotgateway.h"

namespace QTIoT {

class IoTGatewayClient;

class QTIOTSHARED_EXPORT IoTObject : public QObject
{
    Q_OBJECT


    QString iotType;
    QString iotVendor;
    QString iotModel;

    QString address;
    IoTGateway  *gateway;

protected:
    quint64  type;

public:
    explicit IoTObject(QObject *parent = 0);

    QString getAddress(){ return address;};
    QString setAddress(QString newAddress){ address = newAddress; return address;};
    bool setGatewayClient(IoTGatewayClient *newGatewayclient){ gatewayclient = newGatewayclient; return true;};

    IoTGatewayClient  *gatewayclient;


signals:

public slots:

};


} // namespace QTIoT

#include "iotgatewayclient.h"
#endif // QTIOT_IOTOBJECT_H
