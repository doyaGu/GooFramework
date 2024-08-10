#pragma once

#include "SceneObject.h"

class ContinueButtonRope : public SceneObject {
public:
    virtual ~ContinueButtonRope();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void draw(Graphics *,Camera *);
};
