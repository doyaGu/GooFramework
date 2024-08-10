#pragma once

#include "Effect.h"

class ParticleEffectV2 : public Effect {
public:
    virtual ~ParticleEffectV2();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void setPosition(Vec2 const&);
    virtual void setRotation(float);
    virtual void update(float);
    virtual void setDepth(float);
    virtual void setContext(SceneObject::Context);
    virtual void draw(Graphics *,Camera *);
    virtual void handleAdd(Scene *);
    virtual void reset(bool);
    virtual void setScale(float);
    virtual void setEffectArea(EffectArea const&);
};
