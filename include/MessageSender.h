#pragma once

#include "Tickable.h"

class MessageSender : public Tickable {
public:
    virtual ~MessageSender();
    virtual bool tick(float);
    virtual void cancel();
};
