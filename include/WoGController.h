#pragma once

#include "GooController.h"
#include "MessageListener.h"

class WoGController : public GooController, public MessageListener {
public:
    virtual ~WoGController();
    virtual void handleInputEvent(InputEvent *);
    virtual void mouseMove(Mouse *);
    virtual void mouseButtonDown(Mouse *,Mouse::Button,int);
    virtual void mouseButtonUp(Mouse *,Mouse::Button);
    virtual void mouseLeave(Mouse *);
    virtual void handleDownEvent(InputEvent *);
    virtual void handleMessage(std::string const&,MessageSource *,std::map<std::string,std::string> *);
};
