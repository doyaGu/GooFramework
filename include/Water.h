#pragma once

#include "SceneObject.h"
#include "PhysBoy.h"

class Water : public SceneObject, public PhysBoy::ForceFieldListener {
public:
    virtual ~Water();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
    virtual void handleAdd(Scene *);
    virtual void handleRemove(Scene *);
    virtual void handleBodyEnter(PhysBoy::ForceField *,PhysBoy::Body *);
    virtual void handleBodyExit(PhysBoy::ForceField *,PhysBoy::Body *);
};
