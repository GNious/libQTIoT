#ifndef QTIOT_GLOBAL_H
#define QTIOT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTIOT_LIBRARY)
#  define QTIOTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTIOTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTIOT_GLOBAL_H
