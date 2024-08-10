#pragma once

#include "Tickable.h"

class TextEffect : public Tickable {
public:
    virtual ~TextEffect();
    virtual bool tick(float);
    virtual void cancel();
};
