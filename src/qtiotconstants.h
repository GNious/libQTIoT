#ifndef QTIOTCONSTANTS_H
#define QTIOTCONSTANTS_H

//#define QTIoTTypePowerSwitch (1<<2)
//#define QTIoTTypeLightBulb  (1<<3)
//#define QTIoTTypeTimer      (1<<4)
enum QTIoTTypes
{
    QTIoTTypeMask  = 0x0000,
    QTIoTTypePowerSwitch = 1 << 0,
    QTIoTTypeLightBulb = 1 << 1,
    QTIoTTypeTimer = 1 << 8,
	QTIoTTypeMax = 1 << 64
};

#endif // QTIOTCONSTANTS_H
