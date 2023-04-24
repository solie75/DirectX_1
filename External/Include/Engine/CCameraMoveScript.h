#pragma once
#include "CScript.h"
class CCameraMoveScript :
    public CScript
{
private:
    float m_fCameraSpeed;

public:
    virtual void ComponentTick() override;

    CLONE(CCameraMoveScript);

public:
    CCameraMoveScript();
    ~CCameraMoveScript();
};

