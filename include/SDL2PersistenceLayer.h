#pragma once

#include "PersistenceLayer.h"

class SDL2PersistenceLayer : public PersistenceLayer {
public:
    virtual ~SDL2PersistenceLayer();
    virtual void* SDL2PersistenceLayer::putString(std::string const&,std::string const&,bool);
    virtual void* SDL2PersistenceLayer::getString(std::string const&);
    virtual void* SDL2PersistenceLayer::remove(std::string const&,bool);
    virtual void* SDL2PersistenceLayer::getKeyCount();
    virtual void* SDL2PersistenceLayer::getKey(int);
    virtual void* SDL2PersistenceLayer::persist();
    virtual void* SDL2PersistenceLayer::homeDir();
};
