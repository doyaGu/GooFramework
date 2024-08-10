#pragma once

class Graphics;

class Game {
public:
    virtual ~Game();
    virtual void preConfig();
    virtual void preInitLoad();
    virtual void preInitDraw(Graphics *);
    virtual void init();
    virtual void load();
    virtual void loadComplete();
    virtual void performUpdate(float);
    virtual void draw(Graphics *);
    virtual void windowResized(int,int,int,int);
    virtual void fullscreenToggled(bool);
    virtual void preShutdown();
    virtual void handleMouseAdded(int);
    virtual void handleMouseRemoved(int);
    virtual void focusLost();
    virtual void focusGained();
};