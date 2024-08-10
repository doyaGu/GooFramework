#pragma once

#include "BaseParticleEffect.h"

class LiquidFireParticleEffect : public BaseParticleEffect {
public:
    virtual ~LiquidFireParticleEffect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void emit(int);
};