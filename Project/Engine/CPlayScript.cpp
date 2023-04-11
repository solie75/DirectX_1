#include "pch.h"
#include "CPlayScript.h"


CPlayScript::CPlayScript()
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
			vCurPos.y += DT * 1.f;
		}
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		for (int i = 0; i < 4; ++i)
		{
			vCurPos.y -= DT * 1.f;
		}
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		for (int i = 0; i < 4; ++i)
		{
			vCurPos.x -= DT * 1.f;
		}
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		for (int i = 0; i < 4; ++i)
		{
			vCurPos.x += DT * 1.f;
		}
	}

	GetOwner()->GetTransform()->SetRelativePos(vCurPos);
}

