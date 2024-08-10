#pragma once

#include "SceneObject.h"

class ItemLaser : public SceneObject {
public:
    virtual ~ItemLaser();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void draw(Graphics *,Camera *);
};
