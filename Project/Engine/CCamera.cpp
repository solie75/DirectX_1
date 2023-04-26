#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"
#include "CTransform.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_ProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC)
{
	Vec2 vRenderResolution = CDevice::GetInst()->GetRenderResolution();
	m_fAspectRatio = vRenderResolution.x / vRenderResolution.y;
}

CCamera::~CCamera()
{
}


void CCamera::ComponentFinaltick()
{
	// View ��� ���

	m_matView = XMMatrixIdentity();

	// ī�޶� ��ǥ�� �������� �̵�
	Vec3 vCamPos = GetOwner()->GetTransform()->GetRelativePos();
	Matrix matViewTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	// ī�޶� �ٶ󺸴� ������ Z ��� �����ϰ� ����� ȸ�� ����� �����Ų��.
	Matrix matViewRot = XMMatrixIdentity();

	Vec3 vX = GetOwner()->GetTransform()->GetRelativeDirection(DIRECTION_TYPE::X);
	Vec3 vY = GetOwner()->GetTransform()->GetRelativeDirection(DIRECTION_TYPE::Y);
	Vec3 vZ = GetOwner()->GetTransform()->GetRelativeDirection(DIRECTION_TYPE::Z);

	matViewRot._11 = vX.x; matViewRot._12 = vY.x; matViewRot._13 = vZ.x;
	matViewRot._21 = vX.y; matViewRot._22 = vY.y; matViewRot._23 = vZ.y;
	matViewRot._31 = vX.z; matViewRot._32 = vY.z; matVijewRot._33 = vZ.z;

	m_matView = matViewTrans * matViewRot;

	// Projection ��� ���
	m_matProjection = XMMatrixIdentity();

	if (PROJECTION_TYPE::ORTHOGRAPHIC == m_ProjectionType)
	{
		// ���� ����
		Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
		m_matProjection = XMMatrixOrthographicLH(vResolution.x, vResolution.y, 1.f, 10000.f);
	}
	else
	{
		// ���� ����
		m_matProjection = XMMatrixPerspectiveFovLH(XM_PI / 2.f, m_fAspectRatio, 1.f, 10000.f);
	}
	
	// ��� ������Ʈ
	g_transform.matView = m_matView;
	g_transform.matProjection = m_matProjection;

}

