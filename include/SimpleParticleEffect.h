#pragma once

#include "BaseParticleEffect.h"

class SimpleParticleEffect : public BaseParticleEffect {
public:
    virtual ~SimpleParticleEffect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void emit(int);
    virtual void* createParticle();

};