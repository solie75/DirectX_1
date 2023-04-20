#include "pch.h"
#include "CCamera.h"

#include "CDevice.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
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

	// 카메ㅏ 좌표를 원점으로 이동
	Vec3 vCamPos = 

	// Projection 행렬 계산


}

