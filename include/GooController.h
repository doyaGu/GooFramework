#pragma once

#include "KeyboardListener.h"
#include "MouseListener.h"
#include "InputEventHandler.h"

class GooController : public KeyboardListener, public MouseListener, public InputEventHandler {
public:
    virtual ~GooController();
    virtual void keyUp(wchar_t,Keyboard::Key,Keyboard::Modifiers);
    virtual void keyDown(wchar_t,Keyboard::Key,Keyboard::Modifiers);

    virtual void handleInputEvent(InputEvent *);

    virtual void mouseMove(Mouse *);
    virtual void mouseButtonDown(Mouse *,Mouse::Button,int);
    virtual void mouseButtonUp(Mouse *,Mouse::Button);
    virtual void mouseWheel(Mouse *,Vec2 const&);
    virtual void mouseEnter(Mouse *);
    virtual void mouseLeave(Mouse *);
    virtual void handleMoveEvent(InputEvent *);
    virtual void handleUpEvent(InputEvent *);
    virtual void handleDownEvent(InputEvent *);
    virtual void handleEnterEvent(InputEvent *);
    virtual void handleLeaveEvent(InputEvent *);
    virtual void handleWheelEvent(InputEvent *);
};
