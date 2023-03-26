#pragma once
#include "CEntity.h"
#include "CComponent.h"

class CTransform;
class CMeshRender;

class CGameObject :
    public CEntity
{
private : 
    CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];

public:
    void AddComponent(CComponent* _Component);

    // GameObject �� ������ �ִ� Ư�� ������Ʈ�� ��ȯ�Ѵ�.
    CTransform* GetTransform() { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
    CMeshRender* GetMeshRender() { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }

    void GameObjectRender();
    CLONE(CGameObject)

public:
    CGameObject();
    ~CGameObject();
};

