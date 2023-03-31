#pragma once

#include <Engine/CScript.h>
#include <Engine/CKeyMgr.h>
#include <Engine/CTimeMgr.h>

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

