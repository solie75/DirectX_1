#include "pch.h"
#include "CTest.h"
#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResourceMgr.h"

#include "CMesh.h"
#include "ptr.h"

#include "CGameObject.h"

#include "CTransform.h"
#include "CMeshRender.h"
#include "CScript.h"

CGameObject* g_Obj = nullptr;
CGraphicsShader* g_pShader = nullptr;

void TestInit()
{
	// object »ý¼º
	g_Obj = new CGameObject;
	g_Obj->AddComponent(new CMeshRender);
	g_Obj->AddComponent(new CTransform);
	//g_Obj->AddComponent(new CPlayerScript);

	Ptr<CMesh> RectMesh = CResourceMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
	g_Obj->GetMeshRender()->SetMesh(RectMesh.GetResource());

	g_pShader = new CGraphicsShader;
	g_pShader->CreateVertexShader(L"shader\\test.fx", "VS_TEST");
	g_pShader->CreatePixelShader(L"shader\\test.fx", "PS_TEST");
	g_Obj->GetMeshRender()->SetShader(g_pShader);
}

void TestTick()
{
	g_Obj->GameObjectTick();
	g_Obj->GameObjectFinaltick();

}

void TestRender()
{
	g_Obj->GameObjectRender();
}

void TestRelease()
{
	delete g_Obj;
}
