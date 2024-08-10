#pragma once

#include "Tickable.h"

class EmitStopper : public Tickable {
public:
    virtual ~EmitStopper();
    virtual bool tick(float);
    virtual void cancel();
};
