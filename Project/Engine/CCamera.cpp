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
	// View 행렬 계산

	m_matView = XMMatrixIdentity();

	// 카메라 좌표를 원점으로 이동
	Vec3 vCamPos = GetOwner()->GetTransform()->GetRelativePos();
	Matrix matViewTrans = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	// 카메라가 바라보는 방향을 Z 축과 평행하게 만드는 회전 행렬을 적용시킨다.
	Matrix matViewRot = XMMatrixIdentity();

	Vec3 vX = GetOwner()->GetTransform()->GetRelativeDirection(DIRECTION_TYPE::X);
	Vec3 vY = GetOwner()->GetTransform()->GetRelativeDirection(DIRECTION_TYPE::Y);
	Vec3 vZ = GetOwner()->GetTransform()->GetRelativeDirection(DIRECTION_TYPE::Z);

	matViewRot._11 = vX.x; matViewRot._12 = vY.x; matViewRot._13 = vZ.x;
	matViewRot._21 = vX.y; matViewRot._22 = vY.y; matViewRot._23 = vZ.y;
	matViewRot._31 = vX.z; matViewRot._32 = vY.z; matVijewRot._33 = vZ.z;

	m_matView = matViewTrans * matViewRot;

	// Projection 행렬 계산
	m_matProjection = XMMatrixIdentity();

	if (PROJECTION_TYPE::ORTHOGRAPHIC == m_ProjectionType)
	{
		// 직교 투영
		Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
		m_matProjection = XMMatrixOrthographicLH(vResolution.x, vResolution.y, 1.f, 10000.f);
	}
	else
	{
		// 원근 투영
		m_matProjection = XMMatrixPerspectiveFovLH(XM_PI / 2.f, m_fAspectRatio, 1.f, 10000.f);
	}
	
	// 행렬 업데이트
	g_transform.matView = m_matView;
	g_transform.matProjection = m_matProjection;

}

