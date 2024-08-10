#pragma once

#include "Tickable.h"

class EffectLauncher : public Tickable {
public:
    virtual ~EffectLauncher();
    virtual bool tick(float);
    virtual void cancel();
};
