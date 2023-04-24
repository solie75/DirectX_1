#pragma once
#include "CComponent.h"

//#include "CLevelMgr.h"
//#include "CResourceMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CGameObject.h"
#include "CTransform.h"
//#include "CMeshRender.h"


class CScript :
    public CComponent
{
private:

public:
    virtual void ComponentFinaltick() final {};

    CLONE(CScript);

public:
    CScript();
    ~CScript();
};