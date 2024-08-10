#pragma once

#include "Storage.h"

class SDL2Storage : public Storage {
public:
    virtual ~SDL2Storage();
    virtual void* FileExists(char const*);
    virtual void* FileOpen(char const*,int,void **);
    virtual void* FileRead(void *,void *,int);
    virtual void* FileWrite(void *,void const*,int);
    virtual void* FileClose(void *);
    virtual void* FileFlush(void *);
    virtual void* FileGetSize(void *);
};
