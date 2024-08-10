#pragma once

#include "Resource.h"

class FlashAnimRes : public Resource {
public:
    virtual ~FlashAnimRes();
    virtual void* getType();
    virtual void* postLoad();
    virtual void* init(bool);
    virtual void* destroy(bool);
};
