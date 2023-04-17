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
	// ��ġ ���� ��� ���ۿ� ���� �� ���ε�
	CConstBuffer* pTransformBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pTransformBuffer->SetConstBufferData(&m_vRelativePos, sizeof(Vec3));
	pTransformBuffer->UpdateConstBufferData();
}

