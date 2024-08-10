#pragma once

#include "Cloneable.h"
#include "SceneListener.h"
#include "PhysBoy.h"

class LevelModel : public PhysBoy::CollisionListener, public PhysBoy::WorldListener, public SceneListener, public Cloneable {
public:
    virtual ~LevelModel();
    virtual void handleCollision(PhysBoy::World *,PhysBoy::Body *,PhysBoy::Geom const*,PhysBoy::Body *,PhysBoy::Geom const*,Vec2 const&,Vec2 const&,float);
    virtual void handleSensorCollision(PhysBoy::World *,PhysBoy::Body *,PhysBoy::Body *,PhysBoy::Geom const*,Vec2 const&,Vec2 const&,float);
    virtual void handleCollisionsComplete(PhysBoy::World *);
    virtual void objectAdded(SceneObject *);
    virtual void objectRemoved(SceneObject *);
    virtual void handleBodyRemoved(PhysBoy::World *,PhysBoy::Body *);
    virtual void handleJointRemoved(PhysBoy::World *,PhysBoy::Joint *);
    virtual void handleBodyIntersection(PhysBoy::World *,PhysBoy::Body *,Vec2 const&,Vec2 const&,float);
    virtual void handleBodySubmerged(PhysBoy::World *,PhysBoy::Body *);
    virtual void handleLiquidParticleIntersection(PhysBoy::World *,PhysBoy::ParticleSystem *,int,Vec2 const&,Vec2 const&);
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
};
