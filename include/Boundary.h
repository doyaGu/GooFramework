#pragma once

#include "Defines.h"

class Boundary {
public:
    virtual ~Boundary();
    virtual bool contains(Vec2 const& point);
    virtual bool contains(Vec2 const& point, float);
    virtual Boundary* clone();
    virtual void* top();
    virtual void* getExtents();
};


class DummyBoundary : public Boundary {

};

class CircleBoundary : public Boundary {

};

class HeightBoundary : public Boundary {

};