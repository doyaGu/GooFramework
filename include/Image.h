#pragma once

#include "Resource.h"

class Image : public Resource {
public:
    virtual ~Image();
    virtual void* getType();
    virtual void* canReload();
    virtual void* init(bool);
    virtual void* destroy(bool);
};
