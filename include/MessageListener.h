#pragma once

#include "Messenger.h"

class MessageSource;

class MessageListener
{
public:
    MessageListener() {}
    virtual ~MessageListener()
    {
        Messenger::instance()->removeListener(this);
    }

    virtual void handleMessage(const std::string &messageId, MessageSource *source, std::map<std::string, std::string> *params) = 0;
};