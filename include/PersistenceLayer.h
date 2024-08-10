#pragma once

#include <string>

class PersistenceLayer {
public:
    virtual ~PersistenceLayer();
    virtual void* putString(std::string const&,std::string const&,bool);
    virtual void* getString(std::string const&);
    virtual void* remove(std::string const&,bool);
    virtual void* getKeyCount();
    virtual void* getKey(int);
    virtual void* persist();
    virtual void* homeDir();
};