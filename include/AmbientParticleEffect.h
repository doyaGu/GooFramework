#pragma once

#include "BaseParticleEffect.h"

class AmbientParticleEffect : public BaseParticleEffect {
public:
    virtual ~AmbientParticleEffect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void* createParticle();
};
