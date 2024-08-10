#pragma once

class SoundPlayer {
public:
    virtual ~SoundPlayer();
    virtual void* playSound(Sound *,float,bool,SoundBus::Enum,int,Vec2 const*,float,SoundHandle *);
    virtual void* playSoundChain(VectorSoundPtr&,bool,SoundBus::Enum,int,Vec2 const*,SoundHandle *);
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
    virtual void* pauseAllSounds(bool);
    virtual void* getActiveSoundCount() /* const */;
};

class NullSoundPlayer : public SoundPlayer {
public:

};