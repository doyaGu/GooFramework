#pragma once

#include "Positionable.h"

namespace PhysBoy {
    class World : public Cloneable {
    public:
        virtual ~World();
        virtual Cloneable* clone(CloneableMap *);
        virtual void remap(CloneableMap &);
    };

    class ParticleSystem : public Cloneable {
    public:
        virtual ~ParticleSystem();
        virtual Cloneable* clone(CloneableMap *);
        virtual void remap(CloneableMap &);
    };

    class Geom;

    class Body : public Positionable {
    public:
        virtual void* addForce(Vec2 const&);
        virtual void* addForceAtPoint(Vec2 const&,Vec2 const&);
        virtual void* setAntiGravEnabled(bool);
        virtual void* canStick(PhysBoy::Geom const*);
        virtual void* canStickTo(PhysBoy::Body*,PhysBoy::Geom const*);
        virtual void* stickToBody(PhysBoy::Body*,Vec2 const&,float,Vec2 const&);
        virtual void* unstick();
        virtual void* updatePosFromPhysics(float);
        virtual void* addedToWorld(PhysBoy::World *);
        virtual void* postAddedToWorld(PhysBoy::World *);
        virtual void* removedFromWorld();
        virtual void* tick(float);
        virtual void* isStatic();
        virtual void* getUserObject();
        virtual void* handleStickyCollision(PhysBoy::Body*,PhysBoy::Geom const*,Vec2 const&,Vec2 const&);
        virtual void* handleNonStickyCollision(PhysBoy::Body*,PhysBoy::Geom const*,Vec2 const&,Vec2 const&);
        virtual void* isGhost(PhysBoy::Body*);
        virtual void* isGeom();
        virtual void* getKineticEnergy();
        virtual void* getKineticEnergyLin();
        virtual void* getKineticEnergyRot();
    };

    class Spring : public Body {
    public:
        virtual ~Spring();
        virtual Cloneable* clone(CloneableMap *);
        virtual void remap(CloneableMap &);

        virtual void* addedToWorld(PhysBoy::World *);
        virtual void* removedFromWorld();

        virtual void* getLength();
        virtual void* setNaturalLength(float);
        virtual void* getNaturalLength();
        virtual void* setExtensionConstant(float);
        virtual void* getExtensionConstant();
        virtual void* setCompressionConstant(float);
        virtual void* getCompressionConstant();
        virtual void* setIsActive(bool);
        virtual void* isActive();
    };

    class Joint : public Cloneable {
    public:
        virtual ~Joint();
        virtual void remap(CloneableMap &);
        virtual void* addedToWorld(PhysBoy::World *);
        virtual void* removedFromWorld();
        virtual void* createPhysJoint(PhysBoy::World *) = 0;
    };

    class JointHinge : public Joint {
    public:
        virtual ~JointHinge();
        virtual Cloneable* clone(CloneableMap *);
        virtual void* addedToWorld(PhysBoy::World *);
        virtual void* createPhysJoint(PhysBoy::World *);
    };

    class JointHingePin : public Joint {
    public:
        virtual ~JointHingePin();
        virtual Cloneable* clone(CloneableMap *);
        virtual void* addedToWorld(PhysBoy::World *);
        virtual void* createPhysJoint(PhysBoy::World *);
    };

    class JointMouse : public Joint {
    public:
        virtual ~JointMouse();
        virtual Cloneable* clone(CloneableMap *);
        virtual void* addedToWorld(PhysBoy::World *);
        virtual void* createPhysJoint(PhysBoy::World *);
    };

    class JointWeld : public Joint {
    public:
        virtual ~JointWeld();
        virtual Cloneable* clone(CloneableMap *);
        virtual void* addedToWorld(PhysBoy::World *);
        virtual void* createPhysJoint(PhysBoy::World *);
    };

    class JointSlider : public Joint {
    public:
        virtual ~JointSlider();
        virtual Cloneable* clone(CloneableMap *);
        virtual void* addedToWorld(PhysBoy::World *);
        virtual void* createPhysJoint(PhysBoy::World *);
    };

    class JointMotor : public Joint {
    public:
        virtual ~JointMotor();
        virtual Cloneable* clone(CloneableMap *);
        virtual void* addedToWorld(PhysBoy::World *);
        virtual void* removedFromWorld();
        virtual void* createPhysJoint(PhysBoy::World *);
        virtual void* setPosition(Vec2 const&);
    };

    class ForceField : public Cloneable {
    public:
        virtual ~ForceField();
        virtual void remap(CloneableMap &);
        virtual void* applyForceToParticleSystems(PackedArray<PhysBoy::ParticleSystem *> &,int);
        virtual void* getBoundary();
        virtual void* contains(Vec2 const&);
        virtual void* applyForceToBody(PhysBoy::Body *);
        virtual void* getForceForPosition(Vec2 const&,Vec2&);
        virtual void* getExtents();
        virtual void* applyForceToParticleSystems(PackedArray<PhysBoy::ParticleSystem *> &,int);
    };

    class LinearForceField : public ForceField {
    public:
        virtual ~LinearForceField();
        virtual Cloneable* clone(CloneableMap *);
        virtual void* getBoundary();
        virtual void* contains(Vec2 const&);
        virtual void* applyForceToBody(PhysBoy::Body *);
        virtual void* getForceForPosition(Vec2 const&,Vec2&);
        virtual void* getExtents();
    };

    class RadialForceField : public ForceField {
    public:
        virtual ~RadialForceField();
        virtual Cloneable* clone(CloneableMap *);
        virtual void* getBoundary();
        virtual void* contains(Vec2 const&);
        virtual void* applyForceToBody(PhysBoy::Body *);
        virtual void* getForceForPosition(Vec2 const&,Vec2&);
        virtual void* getExtents();
    };

    class WorldListener {
    public:
        virtual void handleBodyRemoved(PhysBoy::World *,PhysBoy::Body *);
        virtual void handleJointRemoved(PhysBoy::World *,PhysBoy::Joint *);
        virtual void handleBodyIntersection(PhysBoy::World *,PhysBoy::Body *,Vec2 const&,Vec2 const&,float);
        virtual void handleBodySubmerged(PhysBoy::World *,PhysBoy::Body *);
        virtual void handleLiquidParticleIntersection(PhysBoy::World *,PhysBoy::ParticleSystem *,int,Vec2 const&,Vec2 const&);
    };

    class CollisionListener {
    public:
        virtual ~CollisionListener();
        virtual void handleCollision(PhysBoy::World *,PhysBoy::Body *,PhysBoy::Geom const*,PhysBoy::Body *,PhysBoy::Geom const*,Vec2 const&,Vec2 const&,float);
        virtual void handleSensorCollision(PhysBoy::World *,PhysBoy::Body *,PhysBoy::Body *,PhysBoy::Geom const*,Vec2 const&,Vec2 const&,float);
        virtual void handleCollisionsComplete(PhysBoy::World *);
    };

    class ForceFieldListener {
    public:
        virtual void handleBodyEnter(PhysBoy::ForceField *,PhysBoy::Body *);
        virtual void handleBodyExit(PhysBoy::ForceField *,PhysBoy::Body *);
    };

    class CollisionManager : public b2ContactListener {
    public:
        virtual ~CollisionManager();
        virtual void BeginContact(b2Contact *);
        virtual void PreSolve(b2Contact *,b2Manifold const*);
        virtual void PostSolve(b2Contact *,b2ContactImpulse const*);
    };
}
