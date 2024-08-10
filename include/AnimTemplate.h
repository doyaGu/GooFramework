#pragma once

#include "Animation.h"

class AnimTemplate {
public:
    virtual ~AnimTemplate();
    virtual Animation* createAnim() = 0;
    virtual float initVariance() = 0;
};
