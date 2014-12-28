#ifndef IOTTIMER_H
#define IOTTIMER_H

#include "qtiot_global.h"
#include "qtiotconstants.h"

#include <QDateTime>
//#include <QTimeZone>

namespace QTIoT {


class QTIOTSHARED_EXPORT IoTTimer
{
public:
    IoTTimer();

    virtual long setTime(long newTime) { return setTime_NoUpdate(newTime); };
    virtual long setTime(QDateTime newTime) { return setTime_NoUpdate(newTime.toTime_t());};
    virtual long setTime_NoUpdate(long newTime) {timesec = newTime;  time = QDateTime::fromTime_t(newTime); return timesec;};
    virtual long getTime() {return timesec;};
    virtual QDateTime getTimeQDateTime() {return time;};


protected:
    qint64 timesec; //time since Epoch
    QDateTime time;

/*signals:
    void timeChanged(QDateTime newTime);*/

};

}

#endif // IOTTIMER_H
