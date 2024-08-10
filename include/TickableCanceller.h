#pragma once

#include "Tickable.h"
#include "MouseListener.h"

class TickableCanceller : public Tickable, public MouseListener {
public:
    virtual ~TickableCanceller();
    virtual bool tick(float);
    virtual void cancel();
    virtual void mouseMove(Mouse *);
    virtual void mouseWheel(Mouse *,Vec2 const&);
    virtual void mouseEnter(Mouse *);
    virtual void mouseLeave(Mouse *);
    virtual void mouseButtonDown(Mouse *,Mouse::Button,int);
    virtual void mouseButtonUp(Mouse *,Mouse::Button);
};
