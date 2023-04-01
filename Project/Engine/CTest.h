#pragma once

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "ptr.h"
#include "CGraphicsShader.h"
#include "CResourceMgr.h"
#include "CEngine.h"

void TestInit()
{
	CGameObject* g_Obj = nullptr;
	CGraphicsShader* g_pShader = nullptr;

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

	CEngine::GetInst()->SetGameObject(g_Obj);
	CEngine::GetInst()->SetGraphicsShader(g_pShader);
}

void TestTick()
{
	CEngine::GetInst()->GetGameObject()->GameObjectTick();
	CEngine::GetInst()->GetGameObject()->GameObjectFinaltick();
}

void TestRender()
{
	CEngine::GetInst()->GetGameObject()->GameObjectRender();
}

void TestRelease()
{
	delete CEngine::GetInst()->GetGameObject();
}