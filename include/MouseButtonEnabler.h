#pragma once

#include "Tickable.h"

class MouseButtonEnabler : public Tickable {
public:
    virtual ~MouseButtonEnabler();
    virtual bool tick(float);
    virtual void cancel();
};
