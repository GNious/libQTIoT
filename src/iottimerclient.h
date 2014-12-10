#ifndef QTIOT_IOTTIMERCLIENT_H
#define QTIOT_IOTTIMERCLIENT_H

#include "qtiot_global.h"
#include "qtiotconstants.h"

#include "iottimer.h"

namespace QTIoT {

class QTIOTSHARED_EXPORT IoTTimerClient : public IoTTimer
{
    //Q_OBJECT
public:
    explicit IoTTimerClient(/*QObject *parent = 0*/);

//signals:

//public slots:

};

} // namespace QTIoT

#endif // QTIOT_IOTTIMERCLIENT_H
