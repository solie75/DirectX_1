#pragma once
#include "CEntity.h"
#include "CGameObject.h"

//class CTransform;
//class CMeshRender;

#define GET_OTHER_COMPONENT(Type) Type* Type() {return m_pOwner->Type();}

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
    // ������ �� �Լ� finaltick �� clone �� ���ӻ��� ���Ͽ� �˰� �Ǹ� ����� �� ��
    virtual void ComponentFinaltick() = 0;
    virtual CComponent* Clone() = 0;

public:


public:
    CComponent(COMPONENT_TYPE _Type);
    virtual ~CComponent();

    friend class CGameObject;
};

