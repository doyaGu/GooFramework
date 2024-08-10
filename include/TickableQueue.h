#pragma once

#include <queue>

#include "Tickable.h"

class TickableQueue : public Tickable
{
public:
    TickableQueue(bool deleteWhenDone = true);
    virtual ~TickableQueue();

    virtual bool tick();
    virtual void cancel();

    void add(Tickable *tickable);
    bool isEmpty();

private:
    Tickable *mCurrent;
    std::queue<Tickable *> mQueue;
};