#pragma once

#include "Tickable.h"
#include "MouseListener.h"
#include "KeyboardListener.h"
#include "Graphics.h"

class MoviePlayer : public Tickable, public MouseListener, public KeyboardListener {
public:
    virtual ~MoviePlayer();
    virtual bool tick(float);
    virtual void cancel();

    virtual void mouseMove(Mouse *);
    virtual void mouseButtonDown(Mouse *,Mouse::Button,int);
    virtual void mouseButtonUp(Mouse *,Mouse::Button);
    virtual void mouseWheel(Mouse *,Vec2 const&);
    virtual void mouseEnter(Mouse *);
    virtual void mouseLeave(Mouse *);

    virtual void keyUp(wchar_t,Keyboard::Key,Keyboard::Modifiers);
    virtual void keyDown(wchar_t,Keyboard::Key,Keyboard::Modifiers);

    virtual void setIsLooping(bool);
    virtual void draw(Graphics *,float,float,float,float);
    virtual float getRelTime(float);
};

class MovieFlashPlayer : public MoviePlayer {
public:
    virtual ~MovieFlashPlayer();
    virtual bool tick(float);
    virtual void setIsLooping(bool);
    virtual void draw(Graphics *,float,float,float,float);
    virtual float getRelTime(float);
};