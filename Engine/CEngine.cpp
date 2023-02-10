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
    m_hWnd = _hWnd; // ���� ������ �ڵ� <- �̰� ���� ������ �ϴ� �ǹ̰� �ֳ�?
    m_vResolution = Vec2((float)_iWidth, (float)_iHeight);

    RECT rt = { 0, 0, (LONG)_iWidth, (LONG)_iHeight }; // �ػ󵵿� �´� �۾� ���� ũ�� ����
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
    ShowWindow(m_hWnd, true);

    // Device �ʱ�ȭ
    if (FAILED(CDevice::GetInst()->DeviceInit(m_hWnd, _iWidth, _iHeight)))
    {
        MessageBox(nullptr, L"Device �ʱ�ȭ ����", L"����", MB_OK);
        return E_FAIL;
    }

    // Manager �ʱ�ȭ
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

