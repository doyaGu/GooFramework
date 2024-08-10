#pragma once

#include "SceneObject.h"

class SquiddySceneBuddy : public SceneObject {
public:
    virtual ~SquiddySceneBuddy();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void draw(Graphics *,Camera *);
};
