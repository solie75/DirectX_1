#include "pch.h"
#include "CTest.h"
#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMesh.h"
#include "CGameObject.h"

#include "CTransform.h"
#include "CMeshRender.h"
#include "CScript.h"

//#include<Script/CPlayerScript.h>


// Buffer
//ComPtr<ID3D11Buffer> g_VB;
//ComPtr<ID3D11Buffer> g_IB; // index buffer
ComPtr<ID3D11Buffer> g_CB; // constant buffer

Vec4 g_PlayerPos; // �÷��̾� ��ü�� ��ġ ����
CGameObject* g_Obj = nullptr;

CMesh* g_pRectMesh = nullptr; // �簢�� mesh
CGraphicsShader* g_pShader = nullptr;

void TestInit()
{
	// Rectangle Mesh ����

	vector<Vtx> vecVtx; // ���� �����͸� ������ ����
	vector<UINT> vecIdx;
	Vtx v;

	v.vPosition = Vec3(-0.5f, 0.5f, 0.5f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPosition = Vec3(0.5f, 0.5f, 0.5f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPosition = Vec3(0.5f, -0.5f, 0.5f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	vecVtx.push_back(v);

	v.vPosition = Vec3(-0.5f, -0.5f, 0.5f);
	v.vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	// Mesh ���� (���� Rectangle Mesh �� ������ ���� �׷��� ����� �����Ѵ�.)
	g_pRectMesh = new CMesh;
	g_pRectMesh->CreateMesh(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());

	// shader ����
	g_pShader = new CGraphicsShader;
	g_pShader->CreateVertexShader(L"shader\\test.fx", "VS_TEST");
	g_pShader->CreatePixelShader(L"shader\\test.fx", "PS_TEST");


	// object ����

	g_Obj = new CGameObject;
	g_Obj->AddComponent(new CMeshRender);
	g_Obj->AddComponent(new CTransform);
	//g_Obj->AddComponent(new CPlayerScript);

	g_Obj->GetMeshRender()->SetMesh(g_pRectMesh);
	g_Obj->GetMeshRender()->SetShader(g_pShader);


	// ���� desc ����
	D3D11_BUFFER_DESC tBufferDesc = {};

	// constant buffer ����
	tBufferDesc.ByteWidth = sizeof(Vec4); // ������ �뷮�� ũ��
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

	// constant buffer ����
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, nullptr, g_CB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void TestTick()
{
	g_Obj->GameObjectTick();
	
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
	//// Input Assembler
	//UINT iStride = sizeof(Vtx); // ���۰� �޸� �� ���޾� ���� �Ѵ�. �̶� ������ ũ�⸦ ������ �� ���۸� ���޾� �ִ� �޸� �󿡼� ������ �� �־�� �Ѵ�. �̶� ���Ǵ� ������ ũ��
	//UINT iOffset = 0; // �ϳ��� ���� ���� �ȿ��� �������� �����ϰ� ���� ������ �ּҸ� ���Ѵ�. -> ���� ���۸� ó������ ���� �� ������ �� ��� 0 ���� �ϸ� �ȴ�.

	//// ������ ������ ������ ������ ���۵Ǹ� IASetVertexBuffer �� ������ g_VB �� IA stage �� ���� �� �� ���ε� �ȴ�.
	//// �̴� IASetVertexBuffer ȣ���� ������ ������ ������ ���� �߿� IA �� ���Ѵٴ� ���� �ƴϴ�. ���� IA stage �� ���� vertex buffer �� g_VB ��� ���� �˸��µ��� ��ģ��.
	//CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &iStride, &iOffset);
	//CONTEXT->IASetIndexBuffer(g_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
	//CONTEXT->IASetInputLayout(g_Layout.Get());

	//// �������� �������� ��� ������ ���Ѵ�. �̶� TRIANGLELIST �̹Ƿ� ������ ������ ��� �ﰢ���� ����ڴٴ� �ǹ��̴�.
	//CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//CONTEXT->VSSetConstantBuffers(0, 1, g_CB.GetAddressOf());
	//CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	//CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);
	////CONTEXT->Draw(3, 0); // ������ rendering pipeline �� ���۽�Ű�� �Լ�
	//CONTEXT->DrawIndexed(6, 0, 0);

	g_Obj->GameObjectRender();
}

void TestRelease()
{
	delete g_Obj;
}
