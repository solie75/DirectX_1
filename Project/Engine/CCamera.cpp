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
	// View ��� ���

	m_matView = XMMatrixIdentity();

	// ī�ޤ� ��ǥ�� �������� �̵�
	Vec3 vCamPos = 

	// Projection ��� ���


}

