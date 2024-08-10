#pragma once

#include "Tickable.h"

class Pause : public Tickable {
public:
    virtual ~Pause();
    virtual bool tick(float);
};
