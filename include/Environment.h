#pragma once

#include <stdio.h>
#include <string>

class Game;
class Graphics;
class Image;
class Keyboard;
class Mouse;
class PersistenceLayer;
class Renderer;
class ResourceManager;
class Sound;
class SoundPlayer;
class TriStrip;
class Storage;

class Environment {
public:
    virtual void init(Game *,int,int,int,char const*,bool);
    virtual void destroy();
    virtual void startMainLoop();
    virtual void stopMainLoop();
    virtual bool isShuttingDown();
    virtual float getTime();
    virtual double getPreciseTime();
    virtual void sleep(int milliseconds);
    virtual Graphics* getGraphics();
    virtual void* getVSync();
    virtual TriStrip* createTriStrip(int);
    virtual void* getWindowSize();
    virtual void* setWindowSize(int,int);
    virtual void* setMinimumWindowSize(int,int);
    virtual void* windowResized();
    virtual void* getMouseCount();
    virtual void* getMouse(int);
    virtual void* getFirstMouse();
    virtual void* getKeyboardCount();
    virtual void* getKeyboard(int);
    virtual void* showSystemMouse(bool);
    virtual void* queryCurrentMouseInWindowPosition(int);
    virtual void* isTouchMode();
    virtual void* lockHardwareCursorPixelData(int,int,int,int);
    virtual void* unlockHardwareCursorPixelData();
    virtual void* getResourceManager();
    virtual void* getPersistenceLayer();
    virtual void* setLanguage(std::string const&);
    virtual void* getLanguage();
    virtual void* showError(std::string const&);
    virtual void* getHardwareId();
    virtual void* isFullScreen();
    virtual void* toggleFullScreen();
    virtual void* enableFullScreenToggle();
    virtual void* disableFullScreenToggle();
    virtual void* log(LogLevel::Enum,char const*,...);
    virtual void* setLogCallback(void (*)(LogLevel::Enum,char const*,void *),void *);
    virtual void* dumpEnvironmentInfo(char const*);
    virtual void* setLogFile(sFILE *);
    virtual void* getStorage();
    virtual void* getSafeZoneInset();
    virtual void* showWatermark();
    virtual void* getPanningAcceleration();
    virtual void* getPanningMargin();
    virtual void* getPanningMaxSpeed();
    virtual void* isPinchZoomEnabled();
    virtual void* isMainWindow();
    virtual void* getPreciseTime();
    virtual void* showSystemDialog(char const*,char const*);
    virtual void* beginProfilerEvent(char const*,unsigned int);
    virtual void* endProfilerEvent();
    virtual void* setConstant(int,float);
    virtual ~Environment();
};