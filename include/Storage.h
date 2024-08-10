#pragma once

#include <string>
#include <vector>

typedef void *BoyFileHandle;

class Storage
{
public:
    enum StorageResult
    {
        STORAGE_OK = 0,
        STORAGE_FAIL = 1,
    };

    enum StorageModeFlags
    {
        STORAGE_MODE_READ = 0x0001,
        STORAGE_MODE_WRITE = 0x0002,
        STORAGE_MODE_MASK = 0x000F,

        STORAGE_MUST_EXIST = 0x0010,
        STORAGE_OPEN_ALWAYS = 0x0020,
        STORAGE_DISPO_MASK = 0x00F0,
    };

    Storage();
    virtual ~Storage();
    virtual StorageResult FileExists(const char *pFilePathUtf8) = 0;
    virtual StorageResult FileOpen(const char *pFilePathUtf8, int modeFlags, BoyFileHandle *pFileHandleOut) = 0;
    virtual StorageResult FileRead(BoyFileHandle fileHandle, void *pBuffer, int readSizeBytes) = 0;
    virtual StorageResult FileWrite(BoyFileHandle fileHandle, const void *pBuffer, int writeSizeBytes) = 0;
    virtual StorageResult FileClose(BoyFileHandle fileHandle) = 0;
    virtual StorageResult FileFlush(BoyFileHandle fileHandle) = 0;
    virtual int FileGetSize(BoyFileHandle openFileHandle) = 0;
    virtual void *FindFilesInPack(std::vector<std::string> &, char const *, char const *, int);

    // helpers
    StorageResult FileGetSize(const char *pFilePath, int *pSizeBytesOut);
};
