#pragma once

class EffectTemplate {
public:
    virtual ~EffectTemplate();
    virtual EffectTemplate* createInstance(std::string const&,float) = 0;
};

class DummyEffectTemplate : public EffectTemplate {
public:
    virtual ~DummyEffectTemplate();
    virtual EffectTemplate* createInstance(std::string const&,float);
};

class AbstractParticleEffectTemplate : public EffectTemplate {
public:
    virtual ~AbstractParticleEffectTemplate();
    virtual EffectTemplate* createInstance(std::string const&,float);
};

class TrailEffectTemplate : public EffectTemplate {
public:
    virtual ~TrailEffectTemplate();
    virtual EffectTemplate* createInstance(std::string const&,float);
};

class SimpleParticleEffectTemplate : public AbstractParticleEffectTemplate {
public:
    virtual ~SimpleParticleEffectTemplate();
    virtual EffectTemplate* createInstance(std::string const&,float);
};

class LiquidFireParticleEffectTemplate : public AbstractParticleEffectTemplate {
public:
    virtual ~LiquidFireParticleEffectTemplate();
    virtual EffectTemplate* createInstance(std::string const&,float);
};

class AmbientParticleEffectTemplate : public AbstractParticleEffectTemplate {
public:
    virtual ~AmbientParticleEffectTemplate();
    virtual EffectTemplate* createInstance(std::string const&,float);
};