#include "pch.h"
#include "CPlayScript.h"
#include "CMeshRender.h"


CPlayScript::CPlayScript()
	: m_fSpeed(100.f)
{
}

CPlayScript::~CPlayScript()
{
}

void CPlayScript::ComponentTick()
{
	Vec3 vCurPos = GetOwner()->GetTransform()->GetRelativePos();

	if (KEY_PRESSED(KEY::UP))
	{
		for (int i = 0; i < 4; ++i)
		{
			vCurPos.y += DT * m_fSpeed;
		}
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		for (int i = 0; i < 4; ++i)
		{
			vCurPos.y -= DT * m_fSpeed;
		}
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		for (int i = 0; i < 4; ++i)
		{
			vCurPos.x -= DT * m_fSpeed;
		}
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		for (int i = 0; i < 4; ++i)
		{
			vCurPos.x += DT * m_fSpeed;
		}
	}

	if (KEY_TAB(KEY::_1))
	{
		int a = 0;
		GetOwner()->GetMeshRender()->GetMaterial()->SetScalarParam(INT_0, &a);
	}
	else if (KEY_TAB(KEY::_2))
	{
		int a = 1;
		GetOwner()->GetMeshRender()->GetMaterial()->SetScalarParam(INT_0, &a);
	}

	if (KEY_TAB(KEY::Z))
	{
		Vec3 vRot = GetOwner()->GetTransform()->GetRelativeRot();
		vRot.y += DT * XM_PI;
		GetOwner()->GetTransform()->SetRelativeRot(vRot);
		vCurPos.z += m_fSpeed * DT;
	}

	GetOwner()->GetTransform()->SetRelativePos(vCurPos);

}

