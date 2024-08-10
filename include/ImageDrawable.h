#pragma once

#include "Graphics.h"
#include "SceneObject.h"

class ImageDrawable {
public:
    virtual ~ImageDrawable();
    virtual void* update(float);
    virtual void* draw(Graphics *,Camera *,SceneObject *,bool);
    virtual void* clone();
};
