#include "iotobject.h"


namespace QTIoT {

IoTObject::IoTObject(QObject *parent) :
	QObject(parent)
{
	type = 0;
}
IoTObject::~IoTObject()
{
	free((void*)1);
}

} // namespace QTIoT
