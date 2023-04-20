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
	CreateDefaultMaterial();
	LoadDefaultTexture();
}

void CResourceMgr::CreateDefaultMesh()
{
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;
	Vtx v;

	Ptr<CMesh> pMesh = nullptr;
	// RectMesh ����
	// 0 -- 1
	// |    |
	// 3 -- 2
	v.vPosition = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPosition = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPosition = Vec3(0.5f, -0.5f, 0.0f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	v.vPosition = Vec3(-0.5f, -0.5f, 0.0f);
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

	pMesh->CreateMesh(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size()); // vector�� data() �Լ��� �ش� ���� �� ������ �ּҸ� ��ȯ�Ѵ�.
	AddResource(L"RectMesh", pMesh);

	vecVtx.clear();
	vecIdx.clear();

	// ===========
	// Circle Mesh
	// ===========
	//      3 
	//   4     2
	//  5 --0-- 1	

	// ������
	float fRadius = 0.5f;

	// ����
	UINT Slice = 40; // ���� �����ϴ� �ﰢ���� ��
	float fTheta = XM_2PI / (float)Slice; // ���� �����ϴ� �ﰢ���� �� ���� ������ �ش��ϴ� ��

	// �߽���
	v.vPosition = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, .1f);
	v.vUV = Vec2(0.5f, 0.5f);
	vecVtx.push_back(v);

	// ���� ��ġ ����

	for (UINT i = 0; i < Slice; ++i)
	{
		v.vPosition = Vec3(fRadius * cosf(fTheta * (float)i), fRadius * sinf(fTheta * (float)i), 0.f);
		v.vUV = Vec2(v.vPosition.x + 0.5f, -v.vPosition.y + 0.5f);
		vecVtx.push_back(v);
	}

	// �ε��� ����
	for (UINT i = 0; i < Slice-1; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	// ������ �ﰢ��
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(Slice);

	pMesh = new CMesh;
	pMesh->CreateMesh(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddResource(L"CircleMesh", pMesh);
	vecVtx.clear();
	vecIdx.clear();
}

void CResourceMgr::CreateDefaultGraphicsShader()
{
	Ptr<CGraphicsShader> pShader = nullptr;

	// TestShader
	pShader = new CGraphicsShader;
	pShader->CreateVertexShader(L"shader\\test.fx", "VS_TEST");
	pShader->CreatePixelShader(L"shader\\test.fx", "PS_TEST");

	AddResource(L"TestShader", pShader);
}

void CResourceMgr::CreateDefaultMaterial()
{
	Ptr<CMaterial> pMaterial = nullptr;

	// Test Material
	pMaterial = new CMaterial;
	pMaterial->SetShader(FindRes<CGraphicsShader>(L"TestShader"));
	AddResource(L"TestMaterial",pMaterial);
}

void CResourceMgr::LoadDefaultTexture()
{
	Ptr<CTexture> pTexture = LoadResource<CTexture>(L"PlayerTexture", L"texture\\Fighter.bmp");

	// t0 ���ε�
	//((CTexture*)pTexture.GetResource())->UpdateTextureData(0);
}