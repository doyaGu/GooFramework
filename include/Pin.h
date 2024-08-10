#pragma once

#include "SceneObject.h"

class LevelModel;

class Pin : public SceneObject {
public:
    virtual ~Pin();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void Pin::setPosition(Vec2 const&);
    virtual void Pin::update(float);
    virtual void Pin::draw(Graphics *,Camera *);
    virtual void Pin::handleAdd(Scene *);
    virtual void Pin::handleRemove(Scene *);
    virtual void Pin::addedToLevel(LevelModel *);
};
