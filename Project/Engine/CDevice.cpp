#include "pch.h"
#include "CDevice.h"
#include "CEngine.h"
#include "CConstBuffer.h"


CDevice::CDevice()
	: m_hWnd(nullptr)
	, m_ViewPort{}
	, m_ConstBuffer(nullptr)
{
}

CDevice::~CDevice()
{
}

int CDevice::DeviceInit(HWND _hWnd, UINT _renderWidth, UINT _renderHeight)
{
	m_hWnd = _hWnd;
	m_vRenderResolution = Vec2((float)_renderWidth, (float)_renderHeight);

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL eLevel1 = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, iFlag, nullptr, 0, D3D11_SDK_VERSION
		, m_Device.GetAddressOf(), &eLevel1, m_Context.GetAddressOf())))
	{
		MessageBox(nullptr, L"Device, Context 생성 실패", L"Device 초기화 에러", MB_OK);

		return E_FAIL;
	}

	if (FAILED(CreateSwapChain()))
	{
		MessageBox(nullptr, L"SwapChain 생성 실패", L"Device 초기화 에러", MB_OK);

		return E_FAIL;
	}

	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"View 생성 실패", L"Device 초기화 에러", MB_OK);

		return E_FAIL;
	}

	// 출력 타겟 설정
	m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());

	// ViewPort 설정
	m_ViewPort.TopLeftX = 0.f;
	m_ViewPort.TopLeftY = 0.f;

	Vec2 vWindowResol = CEngine::GetInst()->GetWindowResolution();
	m_ViewPort.Width = vWindowResol.x;
	m_ViewPort.Height = vWindowResol.y;
	m_ViewPort.MinDepth = 0.f;
	m_ViewPort.MaxDepth = 1.f;

	m_Context->RSSetViewports(1, &m_ViewPort);

	// 상수 버퍼 생성
	m_ConstBuffer = new CConstBuffer(0);
	m_ConstBuffer->CreateConstBuffer(sizeof(Vec4), 1);

	return S_OK;
}

int CDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC tSwapChainDesc = {};
	DXGI_MODE_DESC tModeDesc= {};

	tModeDesc.Width = (UINT)m_vRenderResolution.x;
	tModeDesc.Height = (UINT)m_vRenderResolution.y;
	tModeDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tModeDesc.RefreshRate.Denominator = 1;
	tModeDesc.RefreshRate.Numerator = 60;
	tModeDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	tModeDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	tSwapChainDesc.BufferDesc = tModeDesc;
	tSwapChainDesc.SampleDesc.Count = 1;
	tSwapChainDesc.SampleDesc.Quality = 0;
	tSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tSwapChainDesc.BufferCount = 1;
	tSwapChainDesc.OutputWindow = m_hWnd; // 메인 윈도우
	tSwapChainDesc.Windowed = true;
	tSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	tSwapChainDesc.Flags = 0;

	// 스왑체인 생성
	ComPtr<IDXGIDevice> pDXGIDevice;
	ComPtr<IDXGIAdapter> pAdaptor;
	ComPtr<IDXGIFactory> pFactory;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdaptor.GetAddressOf());
	pAdaptor->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());

	pFactory->CreateSwapChain(m_Device.Get(), &tSwapChainDesc, &m_SwapChain);

	return S_OK;
}

int CDevice::CreateView()
{
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RTTex.GetAddressOf());

	if (FAILED(m_Device->CreateRenderTargetView(m_RTTex.Get(), nullptr, m_RTV.GetAddressOf())))
	{
		return E_FAIL;
	}

	// DepthStencil 용도 텍스쳐 생성
	D3D11_TEXTURE2D_DESC tDesc = {};

	tDesc.Width = (UINT)m_vRenderResolution.x;
	tDesc.Height = (UINT)m_vRenderResolution.y;
	tDesc.MipLevels = 1; // 원본만 생성
	tDesc.ArraySize = 1;
	tDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	tDesc.Usage = D3D11_USAGE_DEFAULT;
	tDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tDesc.CPUAccessFlags = 0;

	if (FAILED(m_Device->CreateTexture2D(&tDesc, nullptr, m_DSTex.GetAddressOf())))
	{
		return E_FAIL;
	}

	if (FAILED(m_Device->CreateDepthStencilView(m_DSTex.Get(), nullptr, m_DSV.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::ClearTarget(float(&_color)[4])
{
	CONTEXT->ClearRenderTargetView(m_RTV.Get(), _color);
	CONTEXT->ClearDepthStencilView(m_DSV.Get(), D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.f, 0);
}

//void CDevice::CreateConstBuffer()
//{
//	m_ConstBuffer = new CConstBuffer(0);
//	m_ConstBuffer->CreateConstBuffer(sizeof(Vec4), 1);
//}


