#pragma once

#include "SceneObject.h"

class Camera : public SceneObject {
public:
    virtual ~Camera();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual const Vec2 &getPosition();
    virtual void setPosition(Vec2 const &);
    virtual void update(float);
};
