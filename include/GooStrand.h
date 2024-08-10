#pragma once

#include "PhysBoy.h"

class GooStrand : public PhysBoy::Body {
public:
    virtual ~GooStrand();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual float getRotation();
    virtual void* addForce(Vec2 const&);
    virtual void* addedToWorld(PhysBoy::World *);
    virtual void* postAddedToWorld(PhysBoy::World *);
    virtual void* removedFromWorld();
    virtual void* addForce(float,float);
};
