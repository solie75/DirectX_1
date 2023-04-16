#include "pch.h"
#include "CMeshRender.h"
#include "CTransform.h"

CMeshRender::CMeshRender()
	:CComponent(COMPONENT_TYPE::MESHRENDERING)
{
}

CMeshRender::~CMeshRender()
{
}


void CMeshRender::ComponentFinaltick()
{
}

void CMeshRender::BeginRenderingMesh()
{
	if (nullptr == m_pMesh || nullptr == m_pMaterial)
	{
		return;
	}

	// Transform ¿¡ UpdateData ¿äÃ»
	GetOwner()->GetTransform()->UpdateTransformData();

	m_pMaterial->UpdateResourceData();
	m_pMesh->RenderMesh();
}

