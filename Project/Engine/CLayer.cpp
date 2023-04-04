#include "pch.h"
#include "CLayer.h"
#include "CGameObject.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	Safe_Del_Vec(m_vecObject);
}


void CLayer::LayerTick()
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->GameObjectTick();
	}
}

void CLayer::LayerFinaltick()
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->GameObjectFinaltick();
	}
}

void CLayer::LayerRender()
{
	for (size_t i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->GameObjectRender();
	}
}

