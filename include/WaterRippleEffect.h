#pragma once

#include "Effect.h"

class WaterRippleEffect : public Effect {
public:
    virtual ~WaterRippleEffect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
    virtual void reset(bool);
};