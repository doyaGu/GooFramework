#pragma once

#include "Effect.h"

class TrailEffect : public Effect {
public:
    virtual ~TrailEffect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
    virtual void reset(bool);
};
