#pragma once
#include "CEntity.h"
#include "CGameObject.h"

//class CTransform;
//class CMeshRender;

class CComponent :
    public CEntity
{
private:
    CGameObject* m_pOwner;
    const COMPONENT_TYPE m_Type;

public:
    COMPONENT_TYPE GetType() { return m_Type; }
    CGameObject* GetOwner() { return m_pOwner; }

public:
    virtual void ComponentTick() {}
    // 다음의 두 함수 finaltick 과 clone 의 쓰임새에 대하여 알게 되면 기록해 둘 것
    virtual void ComponentFinaltick() = 0;
    virtual CComponent* Clone() = 0;

//public:
//    CTransform* GetTransform() { return m_pOwner->GetTransform(); }
//    CMeshRender* GetMeshRender() { return m_pOwner->GetMeshRender(); }

public:
    CComponent(COMPONENT_TYPE _Type);
    virtual ~CComponent();

    friend class CGameObject;
};

