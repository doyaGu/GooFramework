#pragma once

#include "SceneObject.h"

class Effect : public SceneObject {
public:
    virtual ~Effect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
    virtual void reset(bool);
    virtual void setScale(float);
    virtual void setEffectArea(EffectArea const&);
};
