#pragma once

#include "Resource.h"

class Sound : public Resource {
public:
    Sound(ResourceLoader *loader, const std::string &path) : Resource(loader, path) {}
    virtual ~Sound() {}
    virtual void* getType();
    virtual void postLoad();
    virtual bool init(bool);
    virtual void destroy(bool);
    virtual void* getLength();
    virtual void* setLastPlayed(double,int);
};