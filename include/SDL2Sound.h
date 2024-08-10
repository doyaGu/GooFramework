#pragma once

#include "Sound.h"

class SDL2Sound : public Sound {
public:
    virtual ~SDL2Sound();
    virtual void* postLoad();
    virtual void* init(bool);
    virtual void* destroy(bool);
    virtual void* getLength();
    virtual void* setLastPlayed(double,int);
};
