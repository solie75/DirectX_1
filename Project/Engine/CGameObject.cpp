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
	// ���� ������Ʈ�� MeshRender ������Ʈ�� ������ ���� ������ render ���� �ʴ´�.
	if (nullptr == GetMeshRender())
	{
		return;
	}

	// Meshrender ������Ʈ�� ������ �ִ� ��� �ش� �޽��� �������Ѵ�.
	GetMeshRender()->RenderMesh();
}


void CGameObject::AddComponent(CComponent* _Component)
{
	// �̹� �����ϰ� �ִ� ������Ʈ�� ���
	assert(!m_arrCom[(UINT)_Component->GetType()]);

	_Component->m_pOwner = this;

	m_arrCom[(UINT)_Component->GetType()] = _Component;
}