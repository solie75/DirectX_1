#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "ptr.h"
#include "CResourceMgr.h"
#include "CCameraMoveScript.h"
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

	// Main Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);
	pMainCam->AddComponent(new CCameraMoveScript);

	m_pCurLevel->AddGameObject(pMainCam, 0);
	

	// 첫번쩨 인덱스 레이어에 오브젝트 추가
	CGameObject* testGameObj = new CGameObject;
	testGameObj->AddComponent(new CMeshRender);
	testGameObj->AddComponent(new CTransform);
	testGameObj->AddComponent(new CPlayScript);

	Ptr<CMesh> testMesh = CResourceMgr::GetInst()->FindRes<CMesh>(L"CircleMesh");
	Ptr<CTexture> playerTexture = CResourceMgr::GetInst()->FindRes<CTexture>(L"PlayerTexture");
	Ptr<CMaterial> testMaterial = CResourceMgr::GetInst()->FindRes<CMaterial>(L"TestMaterial");

	testMaterial->SetTextureParam(TEX_0, playerTexture);

	testGameObj->GetTransform()->SetRelativePos(Vec3(0.f, 0.f, 50.f));
	testGameObj->GetTransform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

	testGameObj->GetMeshRender()->SetMesh(testMesh);
	testGameObj->GetMeshRender()->SetMaterial(testMaterial);

	m_pCurLevel->AddGameObject(testGameObj, 0);

	// 두번쩨 인덱스 레이어에 오브젝트 추가
	testGameObj = new CGameObject;
	testGameObj->SetName(L"Test Object");
	testGameObj->AddComponent(new CTransform);
	testGameObj->AddComponent(new CMeshRender);

	testMesh = CResourceMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
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
