#pragma once

#include "SceneObject.h"

class FlamethrowerFlame : public SceneObject {
public:
    virtual ~FlamethrowerFlame();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
    virtual void handleAdd(Scene *);
};
