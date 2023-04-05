#include "pch.h"
#include "CMeshRender.h"
#include "CTransform.h"

CMeshRender::CMeshRender()
	:CComponent(COMPONENT_TYPE::MESHRENDERING)
	, m_pMesh(nullptr)
	, m_pShader(nullptr)
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
	if (nullptr == m_pMesh || nullptr == m_pShader)
	{
		return;
	}

	// Transform ¿¡ UpdateData ¿äÃ»
	GetOwner()->GetTransform()->UpdateTransformData();

	m_pShader->UpdateResourceData();
	m_pMesh->RenderMesh();
}

