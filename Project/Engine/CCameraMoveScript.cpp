#include "pch.h"
#include "CCameraMoveScript.h"

#include "CTransform.h"


CCameraMoveScript::CCameraMoveScript()
	: m_fCameraSpeed(1.f)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::ComponentTick()
{
	Vec3 vPos = GetOwner()->GetTransform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT * m_fCameraSpeed;
	}
	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * m_fCameraSpeed;
	}
	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * m_fCameraSpeed;
	}
	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * m_fCameraSpeed;
	}

	GetOwner()->GetTransform()->SetRelativePos(vPos);
}


