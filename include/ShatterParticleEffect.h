#pragma once

#include "BaseParticleEffect.h"

class ShatterParticleEffect : public BaseParticleEffect {
public:
    virtual ~ShatterParticleEffect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void emit(int);
};
