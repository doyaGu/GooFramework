#pragma once

#include "SceneObject.h"

class MultiPageDialog : public SceneObject {
public:
    virtual ~MultiPageDialog();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void setVisible(bool);
    virtual void setTransient(bool);
    virtual void handleAdd(Scene *);
    virtual void handleRemove(Scene *);
    virtual bool contains(Vec2 const&,float);
    virtual void mouseDown(Mouse *,Vec2 const&,Mouse::Button);
    virtual void tick(float);
};
