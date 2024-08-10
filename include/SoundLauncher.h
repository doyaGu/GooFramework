#pragma once

#include "Tickable.h"

class SoundLauncher : public Tickable {
public:
    virtual ~SoundLauncher();
    virtual bool tick(float);
    virtual void cancel();
};
