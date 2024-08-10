#pragma once

#include "SceneObject.h"

class PipeBack : public SceneObject {
public:
    virtual ~PipeBack();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void draw(Graphics *,Camera *);
};
