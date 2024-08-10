#pragma once

#include "PhysBoy.h"

class DetachmentStrand : public PhysBoy::Spring {
public:
    virtual ~DetachmentStrand();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void* addedToWorld(PhysBoy::World *);
    virtual void* removedFromWorld();
    virtual void* tick(float);
    virtual void* getLength();
};
