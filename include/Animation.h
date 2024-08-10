#pragma once

#include "Graphics.h"

class Animation {
public:
    virtual ~Animation();
    virtual void apply(float,float,Graphics *) = 0;
};