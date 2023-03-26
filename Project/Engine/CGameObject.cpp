#include "pch.h"
#include "CGameObject.h"
#include "CComponent.h"
#include "CMeshRender.h"

CGameObject::CGameObject()
	: m_arrCom{}
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
}

void CGameObject::GameObjectRender()
{
	// 게임 오브젝트가 MeshRender 컴포넌트를 가지고 있지 않으면 render 하지 않는다.
	if (nullptr == GetMeshRender())
	{
		return;
	}

	// Meshrender 컴포넌트를 가지고 있는 경우 해당 메쉬를 렌더링한다.
	GetMeshRender()->RenderMesh();
}


void CGameObject::AddComponent(CComponent* _Component)
{
	// 이미 보유하고 있는 컴포넌트의 경우
	assert(!m_arrCom[(UINT)_Component->GetType()]);

	_Component->m_pOwner = this;

	m_arrCom[(UINT)_Component->GetType()] = _Component;
}