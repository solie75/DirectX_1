#include "pch.h"
#include "CTest.h"
#include "CPathMgr.h"


// Vertex Buffer
ComPtr<ID3D11Buffer> g_VB;

// Compiled Shader
ComPtr<ID3DBlob> g_VSBlob; // 컴파일 완료된 vertex shader binary 코드를 저장.
ComPtr<ID3DBlob> g_PSBlob; // 컴파일 완료된 pixel shader binary 코드를 저장.
ComPtr<ID3DBlob> g_ErrBlob; // 컴파일이 실패할 경우의 객체 <- 왜 실패하는 것에 대한 객체가 필요하지?

// shader
ComPtr<ID3D11VertexShader> g_VS; // Vertex shader 객체 g_VSBlob 으로 만든다.
ComPtr<ID3D11PixelShader> g_PS; // Pixel Shader 객체 g_PSBlob 으로 만든다.

// Input Layout
ComPtr<ID3D11InputLayout> g_Layout;

void TestInit()
{
	Vtx arrVts[3] = {};

	arrVts[0].vPosition = Vec3(0.f, 1.f, 0.5f);
	arrVts[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrVts[1].vPosition = Vec3(1.f, -1.f, 0.5f);
	arrVts[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrVts[2].vPosition = Vec3(-1.f, -1.f, 0.5f);
	arrVts[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);

	D3D11_BUFFER_DESC tBufferDesc = {};

	tBufferDesc.ByteWidth = sizeof(Vtx) * 3; // 버퍼의 용량의 크기
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // cpu 에 접근하는 방식
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // 버퍼의 용도 (버퍼는 형체가 확실하지 않은 단순 데이터 이지만 그 역할을 확실히 해주어야 한다.)
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // 정점의 위치를 바꾸고 싶다면 사용자가 버퍼의 내용을 바꿔야 하기 때문.
	tBufferDesc.MiscFlags = 0;
	tBufferDesc.StructureByteStride = 0;
	// -> CPUAccessFlags 와 Usage를 조합하여 사용자는 cpu에 접근해 버퍼를 조작한다.

	// Subresource 설정
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = arrVts;
	tSub.SysMemPitch = 0;
	tSub.SysMemSlicePitch = 0;

	// 버퍼 생성
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, g_VB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// shader 파일 경로
	wstring strShaderFile = CPathMgr::GetInst()->GetContentPath();
	strShaderFile += L"shader\\test.fx";


	// VertexShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "VS_TEST", "vs_5_0", 0, 0, g_VSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)g_ErrBlob->GetBufferPointer(), "Vertex Shader Compile Failed!", MB_OK);
	}


	// PixelShader Compile
	if (FAILED(D3DCompileFromFile(strShaderFile.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_TEST", "ps_5_0", 0, 0, g_PSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)g_ErrBlob->GetBufferPointer(), "Pixel Shader Compile Failed!", MB_OK);
	}
}

void TestTick()
{
}

void TestRender()
{
}

void TestRelease()
{
}

