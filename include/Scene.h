#pragma once

#include "Vec2.h"
#include "Cloneable.h"

class Scene : public Cloneable {
public:
    virtual ~Scene();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
};
