#include "pch.h"
#include "CEngine.h"
#include "CDevice.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CEngine::CEngine()
    : m_hWnd(nullptr)
{
}

CEngine::~CEngine()
{
}

int CEngine::EngineInit(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
    m_hWnd = _hWnd; // 메인 윈도우 핸들 <- 이걸 지역 변수로 하는 의미가 있나?
    m_vResolution = Vec2((float)_iWidth, (float)_iHeight);

    RECT rt = { 0, 0, (LONG)_iWidth, (LONG)_iHeight }; // 해상도에 맞는 작업 영역 크기 조정
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
    ShowWindow(m_hWnd, true);

    // Device 초기화
    if (FAILED(CDevice::GetInst()->DeviceInit(m_hWnd, _iWidth, _iHeight)))
    {
        MessageBox(nullptr, L"Device 초기화 실패", L"에러", MB_OK);
        return E_FAIL;
    }

    // Manager 초기화
    CPathMgr::GetInst()->PathMgrInit();
    CTimeMgr::GetInst()->TimeMgrInit();
    CKeyMgr::GetInst()->KeyMgrInit();

    return S_OK;
}

void CEngine::EngineProgress()
{
    CEngineTick();
    CEngineRender();
}

void CEngine::CEngineTick()
{
}

void CEngine::CEngineRender()
{
}

