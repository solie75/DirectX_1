#pragma once
#include "CEntity.h"
#include "CComponent.h"

class CGameObject :
    public CEntity
{
private : 
    CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];

public:
    void AddComponent(CComponent* _Component);

    CLONE(CGameObject)

public:
    CGameObject();
    ~CGameObject();
};

