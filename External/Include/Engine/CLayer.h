#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*> m_vecObject;

public:
    void LayerTick();
    void LayerFinaltick();
    void LayerRender();

public:
    void AddGameObject(CGameObject* _object) { m_vecObject.push_back(_object); }

    CLONE(CLayer)
public:
    CLayer();
    ~CLayer();
};

