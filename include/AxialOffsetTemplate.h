#pragma once

#include "OffsetFunctionTemplate.h"

class AxialOffsetTemplate : public OffsetFunctionTemplate {
public:
    virtual ~AxialOffsetTemplate();
    virtual void* createInstance();
    virtual void* clone();
};
