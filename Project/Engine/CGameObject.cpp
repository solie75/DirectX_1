#include "pch.h"
#include "CGameObject.h"
#include "CComponent.h"

CGameObject::CGameObject()
	: m_arrCom {}
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
}

void CGameObject::AddComponent(CComponent* _Component)
{
	// �̹� �����ϰ� �ִ� ������Ʈ�� ���
	assert(!m_arrCom[(UINT)_Component->GetType()]);

	_Component->m_pOwner = this;

	m_arrCom[(UINT)_Component->GetType()] = _Component;
}