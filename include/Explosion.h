#pragma once

#include "Sensor.h"

class Explosion : public Sensor {
public:
    virtual ~Explosion();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void* tick(float);
    virtual void OnSensor(PhysBoy::Body *,PhysBoy::Geom const*,Vec2 const&,Vec2 const&,float);
};
