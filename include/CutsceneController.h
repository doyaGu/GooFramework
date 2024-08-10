#pragma once

#include "ControllerBuddy.h"

class CutsceneController : public ControllerBuddy {
public:
    virtual ~CutsceneController();
    virtual void* handleMessage(std::string const&,MessageSource *,std::map<std::string,std::string> *);
    virtual void* update(float);
    virtual void* PlayerCursorMove(Mouse *,Vec2 const&);
    virtual void* PlayerCursorDown(Mouse *,Vec2 const&,Mouse::Button,int);
    virtual void* PlayerCursorUp(Mouse *,Vec2 const&,Mouse::Button,int);
    virtual void* PlayerKeyDown(wchar_t,Keyboard::Key,Keyboard::Modifiers);
    virtual void* PlayerKeyUp(wchar_t,Keyboard::Key,Keyboard::Modifiers);
};
