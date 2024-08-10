#pragma once

#include "Mouse.h"

class MouseListener
{
public:
    MouseListener() {}
    virtual ~MouseListener() {}

    virtual void mouseMove(Mouse *);
    virtual void mouseButtonDown(Mouse *, Mouse::Button, int);
    virtual void mouseButtonUp(Mouse *, Mouse::Button);
    virtual void mouseWheel(Mouse *, Vec2 const &);
    virtual void mouseEnter(Mouse *);
    virtual void mouseLeave(Mouse *);
};