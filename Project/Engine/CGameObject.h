#pragma once
#include "CEntity.h"

class CComponent;
class CTransform;         
class CMeshRender;
class CScript;

class CGameObject :
    public CEntity
{
private: 
    CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];
    vector<CScript*> m_vecScript;

public:
    void AddComponent(CComponent* _Component);

    // GameObject �� ������ �ִ� Ư�� ������Ʈ�� ��ȯ�Ѵ�.
    CTransform* GetTransform() { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
    CMeshRender* GetMeshRender() { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDERING]; }

    void GameObjectRender();
    CLONE(CGameObject)

public:
    void GameObjectTick();
    void GameObjectFinaltick();

public:
    CGameObject();
    ~CGameObject();
};

