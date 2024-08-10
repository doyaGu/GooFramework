#pragma once

#include "MessageListener.h"

class ControllerBuddy : public MessageListener {
public:
    virtual ~ControllerBuddy();
    virtual void* handleMessage(std::string const&,MessageSource *,std::map<std::string,std::string> *);
    virtual void* update(float);
    virtual void* postUpdate(float);
    virtual void* handleInputEvent(InputEvent *);
    virtual void* PlayerCursorMove(Mouse *,Vec2 const&);
    virtual void* PlayerCursorDown(Mouse *,Vec2 const&,Mouse::Button,int);
    virtual void* PlayerCursorUp(Mouse *,Vec2 const&,Mouse::Button,int);
    virtual void* PlayerKeyDown(wchar_t,Keyboard::Key,Keyboard::Modifiers);
    virtual void* PlayerKeyUp(wchar_t,Keyboard::Key,Keyboard::Modifiers);
    virtual void* PlayerMouseWheel(Mouse *,Vec2 const&);
    virtual void* PlayerCursorEnter(Mouse *);
    virtual void* PlayerCursorLeave(Mouse *);
    virtual void* focusGained();
    virtual void* focusLost();
};