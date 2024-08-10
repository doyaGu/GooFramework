#pragma once

#include "SceneObject.h"

class LiquidRenderer : public SceneObject {
public:
    virtual ~LiquidRenderer();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void draw(Graphics *,Camera *);
};
