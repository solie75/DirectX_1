#include "pch.h"
#include "CTransform.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
{
}

CTransform::~CTransform()
{
}


void CTransform::ComponentFinaltick()
{
	//UpdateTransformData();
}

void CTransform::UpdateTransformData()
{
	// 위치 값을 상수 버퍼에 전달 및 바인딩
	CConstBuffer* pTransformBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformBuffer->SetConstBufferData(&m_vRelativePos, sizeof(Vec3));
	pTransformBuffer->UpdateConstBufferData();
}

