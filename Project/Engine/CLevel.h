#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel
	: public CSingleton<CLevel>
{
private:
	CLayer* m_arrLayer[MAX_LAYER];

public:
	void LevelTick();
	void LevelFinaltick();
	void LevelRender();

public:
	void AddGameObject(CGameObject* _Object, int _iLayerIdx);

	CLONE(CLevel);
public:
	CLevel();
	~CLevel();
};

