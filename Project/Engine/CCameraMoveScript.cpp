#include "pch.h"
#include "CCameraMoveScript.h"

#include "CTransform.h"
#include "CCamera.h"

CCameraMoveScript::CCameraMoveScript()
	: m_fCameraSpeed(1.f)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::ComponentTick()
{
	if (PROJECTION_TYPE::ORTHOGRAPHIC == GetOwner()->GetCamera()->GetProjectionType())
	{
		Camera2DMove();
	}
	else
	{
		Camera3DMove();
	}
}

void CCameraMoveScript::Camera2DMove()
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

void CCameraMoveScript::Camera3DMove()
{
	Vec3 vPos = GetOwner()->GetTransform()->GetRelativePos();
	Vec3 vRot = GetOwner()->GetTransform()->GetRelativeRot();

	Vec3 vFront = GetOwner()->GetTransform()->GetRelativeDirection(DIRECTION_TYPE::Z);
	Vec3 vUp = GetOwner()->GetTransform()->GetRelativeDirection(DIRECTION_TYPE::Y);
	Vec3 vRight = GetOwner()->GetTransform()->GetRelativeDirection(DIRECTION_TYPE::X);

	float fSpeed = m_fCameraSpeed;

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		fSpeed *= 5.f;
	}
	if (KEY_PRESSED(KEY::W))
	{
		vPos += DT * vFront * fSpeed;
	}
	if (KEY_PRESSED(KEY::S))
	{
		vPos -= DT * vFront * fSpeed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos -= DT * vRight * fSpeed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos += DT * vRight * fSpeed;
	}
}





