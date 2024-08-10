#pragma once

#include "Cloneable.h"

class LevelEnvironmentFx : public Cloneable {
public:
    virtual ~LevelEnvironmentFx();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
};
