#include "pch.h"
#include "CLevel.h"

#include "CLayer.h"

CLevel::CLevel()
	: m_arrLayer{}
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i] = new CLayer;
	}
}

CLevel::~CLevel()
{
	Safe_Del_Array(m_arrLayer);
}


void CLevel::LevelTick()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->LayerTick();
	}
}

void CLevel::LevelFinaltick()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->LayerFinaltick();
	}
}

void CLevel::LevelRender()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_arrLayer[i]->LayerRender();
	}
}

void CLevel::AddGameObject(CGameObject* _Object, int _iLayerIdx)
{
	m_arrLayer[_iLayerIdx]->AddGameObject(_Object);
}

