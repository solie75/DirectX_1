#pragma once
#include "CEntity.h"

class CGameObject;

class CComponent :
    public CEntity
{
private:
    CGameObject* m_pOwner;
    const COMPONENT_TYPE m_Type;

public:
    COMPONENT_TYPE GetType() { return m_Type; }

public:
    // 다음의 두 함수 finaltick 과 clone 의 쓰임새에 대하여 알게 되면 기록해 둘 것
    virtual void finaltick() = 0;
    virtual CComponent* Clone() = 0;

public:
    CComponent(COMPONENT_TYPE _Type);
    virtual ~CComponent();

    friend class CGameObject;
};

