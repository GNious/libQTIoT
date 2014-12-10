#include "iotobject.h"


namespace QTIoT {

IoTObject::IoTObject(QObject *parent) :
    QObject(parent)
{
    type = 0;
}

} // namespace QTIoT
