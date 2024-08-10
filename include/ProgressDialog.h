#pragma once

#include "SceneObject.h"

class ProgressDialog : public SceneObject {
public:
    virtual ~ProgressDialog();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
};
