#pragma once

#include "Resource.h"

class Font : public Resource {
public:
    virtual ~Font();
    virtual void* getType();
    virtual void* init(bool);
    virtual void* destroy(bool);
};
