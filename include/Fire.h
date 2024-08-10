#pragma once

#include "SceneObject.h"

class Fire : public SceneObject {
public:
    virtual ~Fire();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
    virtual void handleAdd(Scene *);
    virtual void handleRemove(Scene *);
};
