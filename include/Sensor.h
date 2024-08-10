#pragma once

#include "PhysBoy.h"

class Sensor : public PhysBoy::Body {
public:
    virtual ~Sensor();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void OnSensor(PhysBoy::Body *,PhysBoy::Geom const*,Vec2 const&,Vec2 const&,float);
};
