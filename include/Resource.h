#pragma once

#include <string>

class ResourceLoader;

class Resource
{
public:
    Resource(ResourceLoader *loader, const std::string &path);
    virtual ~Resource();
    virtual void *getType();
    virtual bool load();
    virtual void postLoad();
    virtual void reload();
    virtual void release();
    virtual size_t getMemorySize() /* const */;
    virtual bool canReload();
    virtual bool init(bool includeSounds) = 0;
    virtual void destroy(bool includeSounds) = 0;

protected:
    ResourceLoader *mLoader;
    std::string mPath;

private:
    int mRefCount;
};
