#pragma once
#include "CScript.h"
#include "CComponent.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

class CPlayScript :
    public CScript
{
private:
    float m_fSpeed;
public:
    virtual void ComponentTick() override;

    CLONE(CPlayScript);

    CPlayScript();
    ~CPlayScript();
};

