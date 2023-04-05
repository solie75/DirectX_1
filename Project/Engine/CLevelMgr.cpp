#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "ptr.h"
#include "CResourceMgr.h"


CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_pCurLevel)
	{
		delete m_pCurLevel;
	}
}

void CLevelMgr::LevelMgrInit()
{
	m_pCurLevel = new CLevel;

	CGameObject* g_Obj = nullptr;
	CGraphicsShader* g_pShader = nullptr;

	g_Obj = new CGameObject;
	g_Obj->AddComponent(new CMeshRender);
	g_Obj->AddComponent(new CTransform);
	//g_Obj->AddComponent(new CPlayerScript);

	Ptr<CMesh> TestMesh = CResourceMgr::GetInst()->FindRes<CMesh>(L"TestMesh");
	g_Obj->GetMeshRender()->SetMesh(TestMesh.GetResource());

	g_pShader = new CGraphicsShader;
	Ptr<CGraphicsShader> TestShader = CResourceMgr::GetInst()->FindRes<CGraphicsShader>(L"TestShader");
	g_Obj->GetMeshRender()->SetShader(TestShader.GetResource());

	m_pCurLevel->AddGameObject(g_Obj, 0);

	// 두번쩨 인덱스 레이어에 오브젝트 추가

	g_Obj = new CGameObject;
	g_Obj->AddComponent(new CTransform);
	g_Obj->AddComponent(new CMeshRender);

	g_Obj->GetMeshRender()->SetMesh(TestMesh.GetResource());
	g_Obj->GetMeshRender()->SetShader(TestShader.GetResource());

	m_pCurLevel->AddGameObject(g_Obj, 1);

	//CEngine::GetInst()->SetGameObject(g_Obj);
	//CEngine::GetInst()->SetGraphicsShader(g_pShader);
}

void CLevelMgr::LevelMgrTick()
{
	m_pCurLevel->LevelTick();
	m_pCurLevel->LevelFinaltick();
}

void CLevelMgr::LevelMgrRender()
{
	m_pCurLevel->LevelRender();
}
