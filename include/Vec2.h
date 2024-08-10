#pragma once

#include <math.h>

class Vec2
{
public:
    Vec2(float x=0, float y=0) { this->x = x; this->y = y; }
    Vec2(const Vec2 &vec) { x=vec.x; y=vec.y; }
    virtual ~Vec2() {}

    Vec2 operator+(const Vec2 &v) const { return Vec2(x+v.x, y+v.y); }
    Vec2 operator-(const Vec2 &v) const { return Vec2(x-v.x, y-v.y); }
    Vec2 operator-() const { return Vec2(-x, -y); }
    Vec2 operator*(float t) const { return Vec2(t*x, t*y); }
    Vec2 operator/(float t) const { return Vec2(x/t, y/t); }
    void operator+=(const Vec2 &v) { x+=v.x; y+=v.y; }
    void operator-=(const Vec2 &v) { x-=v.x; y-=v.y; }
    void operator*=(float t) { x*=t; y*=t; }
    void operator/=(float t) { x/=t; y/=t; }

    void operator=(const Vec2 &v) { x=v.x; y=v.y; }

    bool operator==(const Vec2 &v) { return x==v.x && y==v.y; }
    bool operator!=(const Vec2 &v) { return x!=v.x || y!=v.y; }

    float dot(const Vec2 &v) const { return x*v.x + y*v.y; }
    float magnitude() const { return sqrtf(x*x + y*y); }
    float magnitudeSquared() const { return x*x+y*y; }

    Vec2 normalize() const { float aMag = magnitude(); return aMag!=0 ? (*this)/aMag : *this; }

    Vec2 perp() const { return Vec2(-y, x); }

public:
    float x;
    float y;
};