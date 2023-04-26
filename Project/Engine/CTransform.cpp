#include "pch.h"
#include "CTransform.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_vRelativeScale(Vec3(1.f, 1.f, 1.f))
	, m_vRelativeDirection{
		Vec3(1.f, 0.f, 0.f),
		Vec3(0.f, 1.f, 0.f),
		Vec3(0.f, 0.f, 1.f)
	}
{
}

CTransform::~CTransform()
{
}


void CTransform::ComponentFinaltick()
{
	Matrix matScale = XMMatrixIdentity();
	matScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);

	Matrix matRot = XMMatrixIdentity();
	matRot = XMMatrixRotationX(m_vRelativeRot.x);
	matRot *= XMMatrixRotationY(m_vRelativeRot.y);
	matRot *= XMMatrixRotationZ(m_vRelativeRot.z);

	Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);

	m_matWorld = matScale * matRot * matTranslation;

	Vec3 vDefaultDirection[3] = {
	  Vec3(1.f, 0.f, 0.f)
	, Vec3(0.f, 1.f, 0.f)
	, Vec3(0.f, 0.f, 1.f)
	};

	for (int i = 0; i < 3; ++i)
	{
		m_vRelativeDirection[i] = XMVector3TransformNormal(vDefaultDirection[i], matRot);
	}

}

void CTransform::UpdateTransformData()
{
	// 위치 값을 상수 버퍼에 전달 및 바인딩
	CConstBuffer* pTransformBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	g_transform.matWorld = m_matWorld;
	pTransformBuffer->SetConstBufferData(&g_transform);
	pTransformBuffer->UpdateConstBufferData();
}

