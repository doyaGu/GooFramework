#pragma once

#include "SceneObject.h"

class GooBallSceneBuddy : public SceneObject {
public:
    virtual ~GooBallSceneBuddy();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void draw(Graphics *,Camera *);
};
