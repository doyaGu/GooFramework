#pragma once

#include <string>

#include "Messenger.h"

class MessageSource
{
public:
    MessageSource() {}
    virtual ~MessageSource() {}

    void sendMessage(std::string messageId, std::map<std::string, std::string> *params = NULL)
    {
        Messenger::instance()->sendMessage(messageId, this, params);
    }
};