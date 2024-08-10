#pragma once

#include "Tickable.h"
#include "MessageListener.h"

class MessageWaiter : public Tickable, public MessageListener {
public:
    virtual ~MessageWaiter();
    virtual bool tick(float);
    virtual void cancel();
    virtual void handleMessage(std::string const&,MessageSource *,std::map<std::string,std::string> *);
};
