#pragma once

#include "Graphics.h"

class Particle {
public:
    virtual ~Particle();
    virtual void* update(float);
    virtual void* draw(Graphics *,Camera *,float);
    virtual void* clone();
    virtual void* getScale();
    virtual void* getAlpha();
    virtual void* getAngle();
};

class ShatterParticle : public Particle {
public:
    virtual ~ShatterParticle();
    virtual void* draw(Graphics *,Camera *,float);
    virtual void* clone();
};

class SuckEffectParticle : public Particle {
public:
    virtual ~SuckEffectParticle();
    virtual void* update(float);
    virtual void* clone();
    virtual void* getAlpha();
};
