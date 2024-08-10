#pragma once

#include "SceneObject.h"

class UndoEffect : public SceneObject {
public:
    virtual ~UndoEffect();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
    virtual void cancel();
};
