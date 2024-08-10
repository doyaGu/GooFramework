#pragma once

#include "PhysBoy.h"

class GooBall : public PhysBoy::Body {
public:
    virtual ~GooBall();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual const Vec2 &getPosition();
    virtual void setPosition(Vec2 const&);
    virtual void* addForce(Vec2 const&);
    virtual void* canStick(PhysBoy::Geom const*);
    virtual void* canStickTo(PhysBoy::Body *,PhysBoy::Geom const*);
    virtual void* stickToBody(PhysBoy::Body *,Vec2 const&,float,Vec2 const&);
    virtual void* unstick();
    virtual void* updatePosFromPhysics(float);
    virtual void* addedToWorld(PhysBoy::World *);
    virtual void* removedFromWorld();
    virtual void* tick(float);
    virtual void* isStatic();
    virtual void* handleStickyCollision(PhysBoy::Body *,PhysBoy::Geom const*,Vec2 const&,Vec2 const&);
    virtual void* handleNonStickyCollision(PhysBoy::Body *,PhysBoy::Geom const*,Vec2 const&,Vec2 const&);
    virtual void* isGhost(PhysBoy::Body *);
    virtual void* isGeom();
    virtual void* getKineticEnergy();
};
