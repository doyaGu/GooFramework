#pragma once

#include "SimpleParticleEffect.h"

class SuckEffect : public SimpleParticleEffect {
public:
    virtual ~SuckEffect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void* SuckEffect::createParticle();
};
