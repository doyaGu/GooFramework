#pragma once

#include "SceneObject.h"

class UploadProgressDialog : public SceneObject {
public:
    virtual ~UploadProgressDialog();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
};
