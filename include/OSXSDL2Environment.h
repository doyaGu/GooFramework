#pragma once

#include "SDL2Environment.h"

class OSXSDL2Environment : public SDL2Environment {
public:
    virtual void* windowResized();
    virtual void* queryCurrentMouseInWindowPosition(int);
    virtual void* isPinchZoomEnabled();
    virtual ~OSXSDL2Environment();
    virtual void setupPlatform();
    virtual void* getPreferredLanguage();
};