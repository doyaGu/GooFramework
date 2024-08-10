#pragma once

#include "SceneObject.h"

class PipeFrontAnimation : public SceneObject {
public:
    virtual ~PipeFrontAnimation();
    virtual Cloneable* clone(CloneableMap *);
    virtual void draw(Graphics *,Camera *);
};
