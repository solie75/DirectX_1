#pragma once

#include <Engine/CKeyMgr.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CComponent.h>
#include <Engine/CScript.h>

class CPlayerScript :
    public CScript
{
private:

public:
    virtual void ComponentTick() override;

    CLONE(CPlayerScript);

public:
    CPlayerScript();
    ~CPlayerScript();
};

