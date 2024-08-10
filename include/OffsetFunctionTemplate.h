#pragma once

class OffsetFunctionTemplate {
public:
    virtual ~OffsetFunctionTemplate() = 0;
    virtual void* createInstance() = 0;
    virtual void* clone() = 0;
};
