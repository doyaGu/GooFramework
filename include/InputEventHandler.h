#pragma once

class InputEvent;

class InputEventHandler {
public:
    virtual ~InputEventHandler();
    virtual void handleInputEvent(InputEvent *) = 0;
};