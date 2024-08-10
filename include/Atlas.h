#pragma once

#include "Resource.h"

class Atlas : public Resource {
public:
    virtual ~Atlas();
    virtual void* Atlas::getType();
    virtual void* Atlas::getMemorySize() /* const */;
    virtual void* Atlas::init(bool);
    virtual void* Atlas::destroy(bool);
};
