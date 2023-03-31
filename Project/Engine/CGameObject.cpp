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
	// ���� ������Ʈ�� MeshRender ������Ʈ�� ������ ���� ������ render ���� �ʴ´�.
	if (nullptr == GetMeshRender())
	{
		return;
	}

	// Meshrender ������Ʈ�� ������ �ִ� ��� �ش� �޽��� �������Ѵ�.
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
		// �̹� �����ϰ� �ִ� ������Ʈ�� ���
		assert(!m_arrCom[(UINT)_Component->GetType()]);

		m_arrCom[(UINT)_Component->GetType()] = _Component;
	}
}