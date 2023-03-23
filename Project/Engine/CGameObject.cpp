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
	// 이미 보유하고 있는 컴포넌트의 경우
	assert(!m_arrCom[(UINT)_Component->GetType()]);

	_Component->m_pOwner = this;

	m_arrCom[(UINT)_Component->GetType()] = _Component;
}