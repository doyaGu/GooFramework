#pragma once

#include "Defines.h"
#include "Cloneable.h"

class Positionable : public Cloneable {
public:
    virtual ~Positionable();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual const Vec2 &getPosition();
    virtual void setPosition(Vec2 const&);
    virtual void addPosition(Vec2 const&);
    virtual float getRotation();
    virtual void setRotation(float);

public:
    void* field_0;
    void* field_8;
    void* field_10;
    void* field_18;
    void* field_20;
    void* field_28;
};
