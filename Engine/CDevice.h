#pragma once

#include "CSingleton.h"

class CDevice
    : public CSingleton<CDevice>
{
private:
    HWND m_hWnd;

    Vec2 m_vRenderResolution;

    ComPtr<ID3D11Device> m_Device;
    ComPtr<ID3D11DeviceContext> m_Context;
    ComPtr<IDXGISwapChain> m_SwapChain;
    ComPtr<ID3D11Texture2D> m_RTTex;
    ComPtr<ID3D11RenderTargetView> m_RTV;
    ComPtr<ID3D11Texture2D> m_DSTex;
    ComPtr<ID3D11DepthStencilView> m_DSV;

    D3D11_VIEWPORT m_ViewPort;

public:
    int DeviceInit(HWND _hWnd, UINT _renderWidth, UINT _renderHeight);
    void ClearTarget(float(&_color)[4]);
    void Present() { m_SwapChain->Present(0, 0); }

public:
    ID3D11Device* GetCDevice() { return m_Device.Get(); }
    ID3D11DeviceContext* GetCContext() { return m_Context.Get(); }

private:
    int CreateSwapChain();
    int CreateView();

public:
    CDevice();
    ~CDevice();
};

