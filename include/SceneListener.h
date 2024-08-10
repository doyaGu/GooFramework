#pragma once

#include "SceneObject.h"

class SceneListener {
public:
    virtual void objectAdded(SceneObject *);
    virtual void objectRemoved(SceneObject *);
};