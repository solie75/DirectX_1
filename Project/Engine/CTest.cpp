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

Vec4 g_PlayerPos; // 플레이어 객체의 위치 정보
CGameObject* g_Obj = nullptr;

CMesh* g_pRectMesh = nullptr; // 사각형 mesh
CGraphicsShader* g_pShader = nullptr;

void TestInit()
{
	// Rectangle Mesh 생성

	vector<Vtx> vecVtx; // 정점 데이터를 가지는 벡터
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

	// Mesh 생성 (위의 Rectangle Mesh 를 가지고 실제 그려질 대상을 생성한다.)
	g_pRectMesh = new CMesh;
	g_pRectMesh->CreateMesh(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());

	// shader 생성
	g_pShader = new CGraphicsShader;
	g_pShader->CreateVertexShader(L"shader\\test.fx", "VS_TEST");
	g_pShader->CreatePixelShader(L"shader\\test.fx", "PS_TEST");


	// object 생성

	g_Obj = new CGameObject;
	g_Obj->AddComponent(new CMeshRender);
	g_Obj->AddComponent(new CTransform);
	//g_Obj->AddComponent(new CPlayerScript);

	g_Obj->GetMeshRender()->SetMesh(g_pRectMesh);
	g_Obj->GetMeshRender()->SetShader(g_pShader);


	// 버퍼 desc 선언
	D3D11_BUFFER_DESC tBufferDesc = {};

	// constant buffer 선언
	tBufferDesc.ByteWidth = sizeof(Vec4); // 버퍼의 용량의 크기
	tBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

	// constant buffer 생성
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, nullptr, g_CB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void TestTick()
{
	g_Obj->GameObjectTick();
	
	// vertex buffer 기준 map unmap
	//D3D11_MAPPED_SUBRESOURCE tSubRes = {};
	//CONTEXT->Map(g_VB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSubRes);
	//memcpy(tSubRes.pData, g_arrVtx, sizeof(Vtx) * 4);
	//CONTEXT->Unmap(g_VB.Get(), 0);

	// constant buffer 기준 map unmap
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
	//UINT iStride = sizeof(Vtx); // 버퍼가 메모리 상에 연달아 존재 한다. 이때 버퍼의 크기를 가지고 각 버퍼를 연달아 있는 메모리 상에서 구분할 수 있어야 한다. 이때 사용되는 버퍼의 크기
	//UINT iOffset = 0; // 하나의 정점 버퍼 안에서 렌더링을 시작하고 싶은 정점의 주소를 말한다. -> 정범 버퍼를 처음부터 전부 다 렌더링 할 경우 0 으로 하면 된다.

	//// 렌더링 파이프 랑인의 과정이 시작되면 IASetVertexBuffer 로 지정한 g_VB 가 IA stage 가 시작 될 때 바인딩 된다.
	//// 이는 IASetVertexBuffer 호출이 렌더링 파이프 라인의 과정 중에 IA 에 속한다는 것이 아니다. 단지 IA stage 에 사용될 vertex buffer 가 g_VB 라는 것을 알리는데에 그친다.
	//CONTEXT->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &iStride, &iOffset);
	//CONTEXT->IASetIndexBuffer(g_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
	//CONTEXT->IASetInputLayout(g_Layout.Get());

	//// 정점들을 기준으로 몇개씩 묶을지 정한다. 이때 TRIANGLELIST 이므로 세개의 정점을 묶어서 삼각형을 만들겠다는 의미이다.
	//CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//CONTEXT->VSSetConstantBuffers(0, 1, g_CB.GetAddressOf());
	//CONTEXT->VSSetShader(g_VS.Get(), nullptr, 0);
	//CONTEXT->PSSetShader(g_PS.Get(), nullptr, 0);
	////CONTEXT->Draw(3, 0); // 실제로 rendering pipeline 을 시작시키는 함수
	//CONTEXT->DrawIndexed(6, 0, 0);

	g_Obj->GameObjectRender();
}

void TestRelease()
{
	delete g_Obj;
}
