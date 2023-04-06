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

	//CGameObject* testGameObj = nullptr;
	//CGraphicsShader* testShader = nullptr;

	CGameObject* testGameObj = new CGameObject;
	testGameObj->AddComponent(new CMeshRender);
	testGameObj->AddComponent(new CTransform);
	//testGameObj->AddComponent(new CPlayerScript);

	Ptr<CMesh> testMesh = CResourceMgr::GetInst()->FindRes<CMesh>(L"TestMesh");
	testGameObj->GetMeshRender()->SetMesh(testMesh);

	Ptr<CGraphicsShader> testShader = CResourceMgr::GetInst()->FindRes<CGraphicsShader>(L"TestShader");
	testGameObj->GetMeshRender()->SetShader(testShader);

	m_pCurLevel->AddGameObject(testGameObj, 0);

	// 두번쩨 인덱스 레이어에 오브젝트 추가

	testGameObj = new CGameObject;
	testGameObj->AddComponent(new CTransform);
	testGameObj->AddComponent(new CMeshRender);

	testGameObj->GetMeshRender()->SetMesh(testMesh);
	testGameObj->GetMeshRender()->SetShader(testShader);

	m_pCurLevel->AddGameObject(testGameObj, 1);

	//CEngine::GetInst()->SetGameObject(testGameObj);
	//CEngine::GetInst()->SetGraphicsShader(testShader);
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
