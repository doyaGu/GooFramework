#pragma once

#include "AnimTemplate.h"
#include "SinAnim.h"

class SinAnimTemplate : public AnimTemplate {
public:
    virtual ~SinAnimTemplate();
    virtual SinAnim* createAnim();
    virtual float initVariance();
};
