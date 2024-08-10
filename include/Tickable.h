#pragma once

class Tickable
{
public:
    Tickable(bool deleteWhenDone = true) { mDeleteWhenDone = deleteWhenDone; }
    virtual ~Tickable() {}

    virtual bool tick() = 0;
    virtual void cancel() {}

    inline bool deleteWhenDone() { return mDeleteWhenDone; }

protected:
    bool mDeleteWhenDone;
};