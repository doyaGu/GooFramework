#pragma once

#include "SoundPlayer.h"
#include "Random.h"

class SDL2SoundPlayer : public SoundPlayer {
public:
    virtual ~SDL2SoundPlayer();
    virtual void* playSound(Sound *,float,bool,SoundBus::Enum,int,Vec2 const*,float,SoundHandle *);
    virtual void* playSoundChain(std::__1::vector<Sound *,std::__1::allocator<Sound *>> &,bool,SoundBus::Enum,int,Vec2 const*,SoundHandle *);
    virtual void* stopSound(Sound *,SoundHandle *);
    virtual void* stopAllSounds(bool,SoundBus::Enum);
    virtual void* setPosition(Sound *,Vec2 const&,SoundHandle *);
    virtual void* setListener(Vec2 const&,float);
    virtual void* setEnvironment(SoundEnvironment const&);
    virtual void* getEnvironment();
    virtual void* fadeBusToVolumeFactor(SoundBus::Enum,float,float);
    virtual void* setBusVolume(SoundBus::Enum,float);
    virtual void* getBusVolume(SoundBus::Enum);
    virtual void* setVolume(Sound *,float,SoundHandle *);
    virtual void* setMasterVolume(float);
    virtual void* getMasterVolume();
    virtual void* fadeIn(Sound *,float,bool,SoundBus::Enum,Vec2 const*,SoundHandle *);
    virtual void* fadeOut(Sound *,float,SoundHandle *);
    virtual void* update(float);
    virtual void* isPlaying(Sound *,SoundHandle *);
    virtual void* seekSeconds(Sound *,float,SoundHandle *);
    virtual void* getCurrentTime(Sound *,SoundHandle *);
    virtual void* setRelativeSpeed(Sound *,float,SoundHandle *);
    virtual void* getActiveSoundCount()/* const */;

public:
    float field_0;
    double field_8;
    Random random_;
    void *field_30;
    void *field_38;
    void *field_40;
    void *field_48;
    void *field_50;
    void *field_58;
    void *field_60;
    void *field_68;
    void *field_70;
    void *field_78;
    void *field_80;
    void *field_88;
    void *field_90;
    void *field_98;
    void *field_a0;
    void *field_a8;
    void *field_b0;
    void *field_b8;
    void *field_c0;
    void *field_c8;
    void *field_d0;
    void *field_d8;
    void *field_e0;
    void *field_e8;
    void *field_f0;
    void *field_f8;
};
