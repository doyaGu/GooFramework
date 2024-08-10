#pragma once

#include "SceneObject.h"

class TimeBug : public SceneObject {
public:
    virtual ~TimeBug();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual void draw(Graphics *,Camera *);
    virtual void handleAdd(Scene *);
    virtual void handleRemove(Scene *);
    virtual bool contains(Vec2 const&,float);
    virtual void mouseEnter(Mouse *);
    virtual void mouseLeave(Mouse *);
    virtual void mouseDown(Mouse *,Vec2 const&,Mouse::Button);
    virtual void mouseUp(Mouse *,Vec2 const&,Mouse::Button);
};
