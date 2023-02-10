#include "pch.h"
#include "CTest.h"
#include "CPathMgr.h"




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

	tBufferDesc.ByteWidth = sizeof(Vtx) * 3; // ������ �뷮�� ũ��
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC; // cpu �� �����ϴ� ���
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // ������ �뵵 (���۴� ��ü�� Ȯ������ ���� �ܼ� ������ ������ �� ������ Ȯ���� ���־�� �Ѵ�.)
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // ������ ��ġ�� �ٲٰ� �ʹٸ� ����ڰ� ������ ������ �ٲ�� �ϱ� ����.
	tBufferDesc.MiscFlags = 0;
	tBufferDesc.StructureByteStride = 0;
	// -> CPUAccessFlags �� Usage�� �����Ͽ� ����ڴ� cpu�� ������ ���۸� �����Ѵ�.

	// Subresource ����
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = arrVts;
	tSub.SysMemPitch = 0;
	tSub.SysMemSlicePitch = 0;

	// ���� ����
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, g_VB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// shader ���� ���
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
		, "PS_Test", "ps_5_0", 0, 0, g_PSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
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

