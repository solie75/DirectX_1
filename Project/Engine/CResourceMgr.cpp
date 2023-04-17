#include "pch.h"
#include "CResourceMgr.h"

#include "CMesh.h"
#include "CGraphicsShader.h"

CResourceMgr::CResourceMgr()
{
}

CResourceMgr::~CResourceMgr()
{
}

void CResourceMgr::ResourceMgrInit()
{
	CreateDefaultMesh();
	CreateDefaultGraphicsShader();
	LoadDefaultTexture();
}

void CResourceMgr::CreateDefaultMesh()
{
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	Ptr<CMesh> pMesh = nullptr;
	// TestMesh 생성
	// 0 -- 1
	// |    |
	// 3 -- 2
	v.vPosition = Vec3(-0.5f, 0.5f, 0.5f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPosition = Vec3(0.5f, 0.5f, 0.5f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPosition = Vec3(0.5f, -0.5f, 0.5f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	v.vPosition = Vec3(-0.5f, -0.5f, 0.5f);
	v.vColor = Vec4(0.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);

	pMesh = new CMesh;
	//pMesh->SetKey(L"TestMesh");

	pMesh->CreateMesh(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size()); // vector의 data() 함수는 해당 벡터 형 변수의 주소를 반환한다.
	AddResource(L"TestMesh", pMesh); // <T> 를 따로 안지정해줘도 되는건가..?
	//m_arrRes[(UINT)RESOURCE_TYPE::MESH].insert(make_pair(pMesh->GetKey(), pMesh.GetResource()));
}

void CResourceMgr::CreateDefaultGraphicsShader()
{
	Ptr<CGraphicsShader> pShader = nullptr;
	
	// TestShader
	pShader = new CGraphicsShader;
	//pShader->SetKey(L"TestShader");
	pShader->CreateVertexShader(L"shader\\test.fx", "VS_TEST");
	pShader->CreatePixelShader(L"shader\\test.fx", "PS_TEST");

	AddResource(L"TestShader", pShader);
	//m_arrRes[(UINT)RESOURCE_TYPE::GRAPHICS_SHADER].insert(make_pair(pShader->GetKey(), pShader.GetResource()));
}

void CResourceMgr::CreateDefaultMaterial()
{
}

void CResourceMgr::LoadDefaultTexture()
{
	Ptr<CTexture> pTexture = LoadResource<CTexture>(L"PlayerTexture", L"texture\\Fighter.bmp");

	// t0 파인딩
	//((CTexture*)pTexture.GetResource())->UpdateTextureData(0);
}