#include "pch.h"
#include "CGameObject.h"
#include "CComponent.h"
#include "CMeshRender.h"

#include "CScript.h"

CGameObject::CGameObject()
	: m_arrCom{}
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
}

void CGameObject::GameObjectTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
		{
			m_arrCom[i]->ComponentTick();
		}
	}

	for (UINT i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->ComponentTick();
	}
}

void CGameObject::GameObjectFinaltick()
{
}


void CGameObject::GameObjectRender()
{
	// 게임 오브젝트가 MeshRender 컴포넌트를 가지고 있지 않으면 render 하지 않는다.
	if (nullptr == GetMeshRender())
	{
		return;
	}

	// Meshrender 컴포넌트를 가지고 있는 경우 해당 메쉬를 렌더링한다.
	GetMeshRender()->BeginRenderingMesh();
}



void CGameObject::AddComponent(CComponent* _Component)
{
	_Component->m_pOwner = this;

	if (COMPONENT_TYPE::SCRIPT == _Component->GetType())
	{
		m_vecScript.push_back((CScript*)_Component);
	}
	else
	{
		// 이미 보유하고 있는 컴포넌트의 경우
		assert(!m_arrCom[(UINT)_Component->GetType()]);

		m_arrCom[(UINT)_Component->GetType()] = _Component;
	}
}