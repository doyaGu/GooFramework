#pragma on  

#include "Graphics.h"

class LoadingScreenRenderer {
public:
    virtual ~LoadingScreenRenderer();
    virtual void* draw(Graphics *);
    virtual void* update(float);
};
