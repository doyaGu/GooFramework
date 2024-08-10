#pragma once

#include "Tickable.h"

class StateAdvancer : public Tickable {
public:
    virtual ~StateAdvancer();
    virtual bool tick(float);
    virtual void cancel();
};
