#pragma once

class CConstBuffer;

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

    //CConstBuffer* m_arrConstBuffer[(UINT)CB_TYPE];
    CConstBuffer* m_ConstBuffer;

public:
    int DeviceInit(HWND _hWnd, UINT _renderWidth, UINT _renderHeight);
    void ClearTarget(float(&_color)[4]);
    void Present() { m_SwapChain->Present(0, 0); }
    //void CreateConstBuffer();
    CConstBuffer* GetConstBuffer() { return m_ConstBuffer; }

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

