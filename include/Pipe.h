#pragma once

#include "SceneObject.h"

class Pipe : public SceneObject {
public:
    virtual ~Pipe();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void setVisible(bool);
    virtual void handleRemove(Scene *);
};
