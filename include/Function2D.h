#pragma once

#include "Vec2.h"

class Function2D
{
public:
    Function2D() {}
    virtual ~Function2D() {}

    inline Vec2 eval(float t) { return Vec2(evalX(t), evalY(t)); }
    virtual float evalX(float t) = 0;
    virtual float evalY(float t) = 0;
    virtual bool canEval(float t) = 0;

    virtual Function2D *clone() = 0;
};

class SinFunction2D : public Function2D
{
public:
};
