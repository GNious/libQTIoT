#ifndef IOTDISCOVERYCLIENT_H
#define IOTDISCOVERYCLIENT_H

#include "qtiot_global.h"

#include <QObject>
#include <QString>
#include <QMap>
#include <QByteArray>
#include <QtNetwork>

#include "iotgatewayclient.h"
#include "iotobject.h"

namespace QTIoT {

class QTIOTSHARED_EXPORT IoTDiscoveryClient : public QObject
{
    Q_OBJECT


public:
    explicit IoTDiscoveryClient(QObject *parent = 0);


    QMap<QString, QTIoT::IoTGatewayClient*> gateways;
    QMap<QString, QTIoT::IoTObject*> items;

    virtual bool connectUDP() =0;
    virtual bool sendMessage(IoTObject *obj, void *msg) =0;
    virtual bool discover() =0;
    Q_INVOKABLE virtual bool startDiscoveryTimer(int waitMs = 10000);// =0;
    Q_INVOKABLE virtual bool endDiscoveryTimer();// =0;

    QMap<QString, QTIoT::IoTObject*> getIoTItems() { return items;};
    QMap<QString, QTIoT::IoTGatewayClient*> getGateways() { return gateways;};

protected:
    QTimer *discoveryTimer;
    bool addGatewayClient(QString address, QTIoT::IoTGatewayClient *client);
    bool addIoTItem(QString address, QTIoT::IoTObject *item);

signals:
    void newGatewayClient(IoTGatewayClient *client);
    void newIoTItem(IoTObject *item);

public slots:

protected slots:
    void IoTItemDiscovered(IoTObject * item);
    void timingDiscovery();


};

} // namespace QTIoT


#endif // IOTDISCOVERYCLIENT_H
