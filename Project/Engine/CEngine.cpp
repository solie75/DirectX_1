#include "pch.h"
#include "CEngine.h"
#include "CDevice.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResourceMgr.h"
#include "CTest.h"

CEngine::CEngine()
    : m_hWnd(nullptr)
    , m_vResolution(0.f, 0.f)
{
}

CEngine::~CEngine()
{
    TestRelease();
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
    CResourceMgr::GetInst()->ResourceMgrInit();

    TestInit();

    return S_OK;
}

void CEngine::EngineProgress()
{
    CEngineTick();
    CEngineRender();
}

void CEngine::CEngineTick()
{
    // Manager Tick
    CTimeMgr::GetInst()->TimeMgrTick();
    CKeyMgr::GetInst()->KeyMgrTick();
    TestTick();
}

void CEngine::CEngineRender()
{
    // ���� ����
    //float arrColor[4] = { 0.4f, 0.4f, 0.4f, 1.f };
    float arrColor[4] = { 0.f, 0.f, 0.f, 1.f };
    CDevice::GetInst()->ClearTarget(arrColor);
    
    // Manager render
    CTimeMgr::GetInst()->TimeMgrInit();

    TestRender();

    // ���� ����
    CDevice::GetInst()->Present();
}

