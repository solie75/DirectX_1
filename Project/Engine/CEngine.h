#pragma once

#include "CGameObject.h"
#include "CGraphicsShader.h"

class CEngine :
    public CSingleton<CEngine>
{
private:
    HWND m_hWnd;
    Vec2 m_vResolution; // 윈도우 해상도
    CGameObject* g_Obj;
    CGraphicsShader* g_pShader;

public:
    Vec2 GetWindowResolution() { return m_vResolution; }
    HWND GetMainWnd() { return m_hWnd; }

    CGameObject* GetGameObject() { return g_Obj; }
    CGraphicsShader* GetGraphicsShader() { return g_pShader; }
    void SetGameObject(CGameObject* _Obj) {  g_Obj = _Obj; }
    void SetGraphicsShader(CGraphicsShader* _pShader) {  g_pShader = _pShader; }


public:
    int EngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight);
    void EngineProgress();

private:
    void CEngineTick();
    void CEngineRender();


public:
    CEngine();
    ~CEngine();
};

