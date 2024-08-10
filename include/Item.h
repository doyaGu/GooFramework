#pragma once

#include "SceneObject.h"
#include "LevelModel.h"
#include "PhysBoy.h"

class Item : public SceneObject {
public:
    virtual ~Item();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void setPosition(Vec2 const&);
    virtual void setRotation(float);
    virtual void update(float);
    virtual void setVisible(bool);
    virtual void setDepth(float);
    virtual void draw(Graphics *,Camera *);
    virtual void handleAdd(Scene *);
    virtual void handleRemove(Scene *);
    virtual bool contains(Vec2 const&,float);
    virtual void* setFromInfo(ItemInstanceInfo const&);
    virtual void* addedToLevel(LevelModel *);
    virtual void* removedFromLevel();
    virtual void* addSubobjectsToScene(Scene *);
    virtual void* destroyObjects(bool);
    virtual void* tick(float);
    virtual void* drawItem(Graphics *,Camera *);
    virtual void* drawItemUI(Graphics *,Camera *);
    virtual void* drawSelection(Graphics *,Camera *);
    virtual void* postUpdate(float);
    virtual void* updateAnimation(float);
    virtual void* updateObjectColors();
    virtual void* startDrag();
    virtual void* endDrag();
    virtual void* levelResized(Rect const&);
    virtual void* canSuckLiquid();
    virtual void* suckLiquid();
    virtual void* isLevelGoalMet();
    virtual void* setLiquidType(LiquidType::Enum);
    virtual void* setScale(Vec2 const&);
    virtual void* getBounds();
    virtual void* getEquivalentDepth0Bounds(bool);
    virtual void* getInfo(ItemInstanceInfo &);
    virtual void* updateObjectTransforms();
    virtual void* setAnimation(char const*,char const*);
    virtual void* renderToStableFluids(Graphics *,Camera *,Color &);
    virtual void* renderToLighting(Graphics *,Camera *);
    virtual void* prepareForPlay();
    virtual void* afterPrepareForPlay();
    virtual void* bodyContact(CollisionEvent const&);
    virtual void* liquidParticleContact(Vec2 const&,Vec2 const&,Vec2 const&,int);
    virtual void* handleBodyRemoved(PhysBoy::Body *);
    virtual void* handleJointRemoved(PhysBoy::Joint *);
    virtual void* handleBallRemoved(GooBall *);
    virtual void* handleStrandRemoved(GooStrand *);
    virtual void* handleItemRemoved(Item*);
    virtual void* handleConnection(Positionable *,bool);
    virtual void* drawAnimationWS(Graphics *,Camera *,Vec2 const&,Vec2 const&,float,float,Color const&);
    virtual void* drawAnimation(Graphics *,Camera *,Vec2 const&,Vec2 const&,float,float,Color const&);
    virtual void* tickCollisionSounds(float);
    virtual void* updateObjects();
    virtual void* createObjects(ItemInstanceInfo const&);
    virtual void* onUserVariableChanged(int);
    virtual void* onPreDrawObject(int,Graphics *,Camera *);
    virtual void* onPostDrawObject(int,Graphics *,Camera *);
};
