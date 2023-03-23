#include "pch.h"
#include "CTest.h"
#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CGameObject.h"

#include "CTransform.h"
#include "CMeshRender.h"



// Buffer
ComPtr<ID3D11Buffer> g_VB;
ComPtr<ID3D11Buffer> g_IB; // index buffer
ComPtr<ID3D11Buffer> g_CB; // constant buffer

// Compiled Shader
ComPtr<ID3DBlob> g_VSBlob; // ������ �Ϸ�� vertex shader binary �ڵ带 ����.
ComPtr<ID3DBlob> g_PSBlob; // ������ �Ϸ�� pixel shader binary �ڵ带 ����.
ComPtr<ID3DBlob> g_ErrBlob; // �������� ������ ����� ��ü <- �� �����ϴ� �Ϳ� ���� ��ü�� �ʿ�����?

// shader
ComPtr<ID3D11VertexShader> g_VS; // Vertex shader ��ü g_VSBlob ���� �����.
ComPtr<ID3D11PixelShader> g_PS; // Pixel Shader ��ü g_PSBlob ���� �����.

// Input Layout
ComPtr<ID3D11InputLayout> g_Layout;

// vectex
Vtx g_arrVtx[4] = {}; // ������ �ڷ������� �ϴ� �迭 -> �ϳ��� �簢���� ���鿹���̱� ������ ũ�Ⱑ 4
UINT g_arrIdx[6] = {}; // �� �ε����� ũ�Ⱑ 6����?

Vec4 g_PlayerPos; // �÷��̾� ��ü�� ��ġ ����

CGameObject* g_Obj = nullptr;

void TestInit()
{
	// object ����

	g_Obj = new CGameObject;
	g_Obj->AddComponent(new CMeshRender);
	g_Obj->AddComponent(new CTransform);
	 
	 
	// ���� desc ����
	D3D11_BUFFER_DESC tBufferDesc = {};

	// constant buffer ����
	tBufferDesc.ByteWidth = sizeof(Vtx) * 4; // ������ �뷮�� ũ��
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

	// constant buffer ����
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, nullptr, g_CB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// 0 --- 1 
	// |  \  |
	// 3 --- 2
	g_arrVtx[0].vPosition = Vec3(-0.5f, 0.5f, 0.5f);
	g_arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	g_arrVtx[1].vPosition = Vec3(0.5f, 0.5f, 0.5f);
	g_arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	g_arrVtx[2].vPosition = Vec3(0.5f, -0.5f, 0.5f);
	g_arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	g_arrVtx[3].vPosition = Vec3(-0.5f, -0.5f, 0.5f);
	g_arrVtx[3].vColor = Vec4(0.f, 0.f, 0.f, 1.f);

	
	// ���� ���� desc
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT; // cpu �� �����ϴ� ���
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // ������ �뵵 (���۴� ��ü�� Ȯ������ ���� �ܼ� ������ ������ �� ������ Ȯ���� ���־�� �Ѵ�.)
	tBufferDesc.CPUAccessFlags = 0; // ������ ��ġ�� �ٲٰ� �ʹٸ� ����ڰ� ������ ������ �ٲ�� �ϱ� ����.
	tBufferDesc.MiscFlags = 0;
	tBufferDesc.StructureByteStride = 0;
	// -> CPUAccessFlags �� Usage�� �����Ͽ� ����ڴ� cpu�� ������ ���۸� �����Ѵ�.

	// Subresource ����
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = g_arrVtx;
	tSub.SysMemPitch = 0;
	tSub.SysMemSlicePitch = 0;

	// ���� ���� ����
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, g_VB.GetAddressOf())))
	{
		assert(nullptr);
	}

	// index buffer ����
	g_arrIdx[0] = 0;
	g_arrIdx[1] = 2;
	g_arrIdx[2] = 3;
	g_arrIdx[3] = 0;
	g_arrIdx[4] = 1;
	g_arrIdx[5] = 2;

	// �ε��� ���� desc
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	// ���� �Ұ���
	tBufferDesc.CPUAccessFlags = 0;
	tBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// ������ ũ��
	tBufferDesc.ByteWidth = sizeof(UINT) * 6;

	// �ε��� ���� subresource ����
	tSub.pSysMem = g_arrIdx;

	// �ε��� ���� ����
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, g_IB.GetAddressOf())))
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
		, "PS_TEST", "ps_5_0", 0, 0, g_PSBlob.GetAddressOf(), g_ErrBlob.GetAddressOf())))
	{
		MessageBoxA(nullptr, (const char*)g_ErrBlob->GetBufferPointer(), "Pixel Shader Compile Failed!", MB_OK);
	}


	// �����ϵ� ��ü�� ���̴��� �����Ѵ�.
	DEVICE->CreateVertexShader(g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), nullptr, g_VS.GetAddressOf());
	DEVICE->CreatePixelShader(g_PSBlob->GetBufferPointer(), g_PSBlob->GetBufferSize(), nullptr, g_PS.GetAddressOf());

	// Input Layer
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};

	// vPos
	LayoutDesc[0].SemanticName = "POSITION";
	LayoutDesc[0].SemanticIndex = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;

	// vColor
	LayoutDesc[1].SemanticName = "COLOR";
	LayoutDesc[1].SemanticIndex = 0;
	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;

	if (FAILED(DEVICE->CreateInputLayout(LayoutDesc, 2, g_VSBlob->GetBufferPointer(), g_VSBlob->GetBufferSize(), g_Layout.GetAddressOf())))
	{
		assert(nullptr);
	}

}

//typedef struct D3D11_INPUT_ELEMENT_DESC
//{
//	LPCSTR SemanticName;
//	UINT SemanticIndex;
//	DXGI_FORMAT Format;
//	UINT InputSlot;
//	UINT AlignedByteOffset;
//	D3D11_INPUT_CLASSIFICATION InputSlotClass;
//	UINT InstanceDataStepRate;
//} 	D3D11_INPUT_ELEMENT_DESC;

void TestTick()
{
	if (KEY_PRESSED(KEY::UP))
	{
		for (int i = 0; i < 4; ++i)
		{
			//g_arrVtx[i].vPosition.y += DT * 0.1f;
			g_PlayerPos.y += DT * 0.1f;
		}
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_PlayerPos.y -= DT * 0.1f;
		}
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_PlayerPos.x += DT * 0.1f;
		}
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		for (int i = 0; i < 4; ++i)
		{
			g_PlayerPos.x -= DT * 0.1f;
		}
	}
	
	// vertex buffer ���� map unmap
	//D3D11_MAPPED_SUBRESOURCE tSubRes = {};
	//CONTEXT->Map(g_VB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSubRes);
	//memcpy(tSubRes.pData, g_arrVtx, sizeof(Vtx) * 4);
	//CONTEXT->Unmap(g_VB.Get(), 0);

	// constant buffer ���� map unmap
	// g_PlayerPos ==> g_CB
	D3D11_MAPPED_SUBRESOURCE tSubRes = {};
	if (!FAILED(CONTEXT->Map(g_CB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSubRes)))
	{
		memcpy(tSubRes.pData, &g_PlayerPos, sizeof(Vec4));
		CONTEXT->Unmap(g_CB.Get(), 0);
	}
}

void TestRender()
{
	// Input Assembler
	UINT iStride = sizeof(Vtx); // ���۰� �޸� �� ���޾� ���� �Ѵ�. �̶� ������ ũ�⸦ ������ �� ���۸� ���޾� �ִ� �޸� �󿡼� ������ �� �־�� �Ѵ�. �̶� ���Ǵ� ������ ũ��
	UINT iOffset = 0; // �ϳ��� ���� ���� �ȿ��� �������� �����ϰ� ���� ������ �ּҸ� ���Ѵ�. -> ���� ���۸� ó������ ���� �� ������ �� ��� 0 ���� �ϸ� �ȴ�.

	// ������ ������ ������ ������ ���۵Ǹ� IASetVertexBuffer �� ������ g_VB �� IA stage �� ���� �� �� ���ε� �ȴ�.
	// �̴� IASetVertexBuffer ȣ���� ������ ������ ������ ���� �߿� IA �� ���Ѵٴ� ���� �ƴϴ�. ���� IA stage �� ���� vertex buffer �� g_VB ��� ���� �˸��µ��� ��ģ��.
	CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(g_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
	CONTEXT->IASetInputLayout(g_Layout.Get());

	// �������� �������� ��� ������ ���Ѵ�. �̶� TRIANGLELIST �̹Ƿ� ������ ������ ��� �ﰢ���� ����ڴٴ� �ǹ��̴�.
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	CONTEXT->VSSetConstantBuffers(0, 1, g_CB.GetAddressOf());
	CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);
	//CONTEXT->Draw(3, 0); // ������ rendering pipeline �� ���۽�Ű�� �Լ�
	CONTEXT->DrawIndexed(6, 0, 0);

}

void TestRelease()
{
	delete g_Obj;
}
