#pragma once

#include "Positionable.h"
#include "Graphics.h"
#include "Scene.h"
#include "Camera.h"
#include "Mouse.h"

class SceneObject : public Positionable {
public:
    virtual ~SceneObject();
    virtual Cloneable* clone(CloneableMap *);
    virtual void remap(CloneableMap &);
    virtual void update(float);
    virtual bool isVisible();
    virtual void setVisible(bool);
    virtual void setDepth(float);
    virtual void setContext(SceneObject::Context);
    virtual void draw(Graphics *,Camera *);
    virtual void setTransient(bool);
    virtual bool isTransient();
    virtual void handleAdd(Scene *);
    virtual void handleRemove(Scene *);
    virtual bool contains(Vec2 const&,float);
    virtual void mouseEnter(Mouse *);
    virtual void mouseLeave(Mouse *);
    virtual void mouseMove(Mouse *,Vec2 const&);
    virtual void mouseDown(Mouse *,Vec2 const&,Mouse::Button);
    virtual void mouseUp(Mouse *,Vec2 const&,Mouse::Button);
    virtual void mouseWheel(Mouse *,Vec2 const&);

public:
    void* field_8;
    void* field_10;
    void* field_18;
    void* field_20;
    void* field_28;
    void* field_30;
    void* field_38;
    void* field_40;
    void* field_48;
    void* field_50;
    void* field_58;
    void* field_60;
    void* field_68;
    void* field_70;
    void* field_78;
    void* field_80;
    void* field_88;
    void* field_90;
    void* field_98;
};
