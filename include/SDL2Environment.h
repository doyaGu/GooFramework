#pragma once

#include "Environment.h"
#include "SoundPlayer.h"

class SDL2Environment : public Environment {
public:
    virtual void* init(Game *,int,int,int,char const*,bool);
    virtual void* destroy();
    virtual void* startMainLoop();
    virtual void* stopMainLoop();
    virtual void* isShuttingDown();
    virtual void* getTime();
    virtual void* getPreciseTime();
    virtual void* sleep(int);
    virtual void* getGraphics();
    virtual void* getVSync();
    virtual void* createTriStrip(int);
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
    virtual void* dumpEnvironmentInfo(char const*);
    virtual void* setLogFile(__sFILE *);
    virtual void* getStorage();
    virtual void* getSafeZoneInset();
    virtual void* showWatermark();
    virtual void* getPanningAcceleration();
    virtual void* getPanningMargin();
    virtual void* getPanningMaxSpeed();
    virtual void* isMainWindow() /* const */;
    virtual void* getPreciseTime() /* const */;
    virtual void* showSystemDialog(char const*,char const*);
    virtual ~SDL2Environment();
    virtual SoundPlayer* getRealSoundPlayer();
    virtual void setupPlatform();
    virtual void postLoadConfig();
    virtual void postGraphics();
    virtual void* getPreferredLanguage();
    virtual void update(float);
    virtual void handleWindowResized();
    virtual void* pollInput();
    virtual void handleTouchEvent(SDL_Event const&);
    virtual void handleGameControllerEvent(SDL_Event const&);
};