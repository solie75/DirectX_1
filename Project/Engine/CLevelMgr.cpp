#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "ptr.h"
#include "CResourceMgr.h"
#include "CPlayScript.h"


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

	// 첫번쩨 인덱스 레이어에 오브젝트 추가
	CGameObject* testGameObj = new CGameObject;
	testGameObj->AddComponent(new CMeshRender);
	testGameObj->AddComponent(new CTransform);
	testGameObj->AddComponent(new CPlayScript);

	Ptr<CMesh> testMesh = CResourceMgr::GetInst()->FindRes<CMesh>(L"TestMesh");
	Ptr<CTexture> playerTexture = CResourceMgr::GetInst()->FindRes<CTexture>(L"PlayerTexture");
	Ptr<CMaterial> testMaterial = CResourceMgr::GetInst()->FindRes<CMaterial>(L"TestMaterial");

	testMaterial->SetTextureParam(TEX_0, playerTexture);

	testGameObj->GetMeshRender()->SetMesh(testMesh);
	testGameObj->GetMeshRender()->SetMaterial(testMaterial);

	m_pCurLevel->AddGameObject(testGameObj, 0);

	// 두번쩨 인덱스 레이어에 오브젝트 추가
	testGameObj = new CGameObject;
	testGameObj->SetName(L"Test Object");
	testGameObj->AddComponent(new CTransform);
	testGameObj->AddComponent(new CMeshRender);

	testGameObj->GetMeshRender()->SetMesh(testMesh);
	testGameObj->GetMeshRender()->SetMaterial(testMaterial);

	m_pCurLevel->AddGameObject(testGameObj, 1);
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
