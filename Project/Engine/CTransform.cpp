#include "pch.h"
#include "CTransform.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
{
}

CTransform::~CTransform()
{
}


void CTransform::finaltick()
{
}

void CTransform::UpdateTransformData()
{
	// 위치 값을 상수 버퍼에 저장
}

