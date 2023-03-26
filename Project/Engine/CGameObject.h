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

    // GameObject 가 가지고 있는 특정 컴포넌트를 반환한다.
    CTransform* GetTransform() { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
    CMeshRender* GetMeshRender() { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }

    void GameObjectRender();
    CLONE(CGameObject)

public:
    CGameObject();
    ~CGameObject();
};

