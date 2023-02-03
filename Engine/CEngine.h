#pragma once
#include "CSingleton.h"
class CEngine :
    public CSingleton<CEngine>
{
private:
    HWND m_hWnd;

    Vec2 m_vResolution;
};

