#ifndef QTIOT_IOTGATEWAYCLIENT_H
#define QTIOT_IOTGATEWAYCLIENT_H

#include "qtiot_global.h"


#include <QObject>
#include <QString>
#include <QMap>
#include "iotobject.h"
//#include "iotdiscoveryclient.h"

namespace QTIoT {

class IoTDiscoveryClient;

class QTIOTSHARED_EXPORT IoTGatewayClient : public QObject
{
    Q_OBJECT
public:
    explicit IoTGatewayClient(QObject *parent = 0);

    QString address;
    QMap<QString, QTIoT::IoTObject*> items;

    IoTDiscoveryClient *discoveryclient;


    bool addItem(IoTObject *item) {items.insert(item->getAddress(), item); item->setGatewayClient(this); emit newObject(item); return true;};
    QString getAddress(){ return address;};
    QString setAddress(QString newAddress){ address = newAddress; return address;};
    bool setDiscoveryClient(IoTDiscoveryClient *client){ discoveryclient = client; return true;};
    QMap<QString, QTIoT::IoTObject*> getIoTItems() { return items;};
    QTIoT::IoTObject* getItem(QString address);
signals:
    void newObject(IoTObject *item);

public slots:

};

} // namespace QTIoT

#endif // QTIOT_IOTGATEWAYCLIENT_H
