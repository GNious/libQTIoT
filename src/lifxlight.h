#ifndef LIFXLIGHT_H
#define LIFXLIGHT_H

#include "lightbulb.h"

namespace QTIoT {
namespace LIFX {

class LIFXLight : public LightBulb
{
    Q_OBJECT
public:
    explicit LIFXLight(QObject *parent = 0);

signals:

public slots:

};

} // namespace LIFX
} // namespace QTIoT

#endif // LIFXLIGHT_H
