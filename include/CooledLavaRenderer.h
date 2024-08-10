#pragma once

#include "SceneObject.h"

class CooledLavaRenderer : public SceneObject {
public:
    virtual ~CooledLavaRenderer();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
};
