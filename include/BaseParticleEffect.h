#pragma once

#include "Effect.h"

class BaseParticleEffect : public Effect {
public:
    virtual ~BaseParticleEffect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);

    virtual void emit(int);
    virtual void* createParticle();
};
