#pragma once

#include "Keyboard.h"

class KeyboardListener {
public:
    virtual void keyUp(wchar_t,Keyboard::Key,Keyboard::Modifiers);
    virtual void keyDown(wchar_t,Keyboard::Key,Keyboard::Modifiers);
};