#pragma once

#include "Tickable.h"

class Mover : public Tickable {
public:
    virtual ~Mover();
    virtual bool tick(float);
    virtual void cancel();
};