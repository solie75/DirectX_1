#include "pch.h"
#include "CMeshRender.h"
#include "CTransform.h"

CMeshRender::CMeshRender()
	:CComponent(COMPONENT_TYPE::MESHRENDER)
	, m_pMesh(nullptr)
	, m_pShader(nullptr)
{
}

CMeshRender::~CMeshRender()
{
}


void CMeshRender::finaltick()
{
}

void CMeshRender::RenderMesh()
{
	if (nullptr == m_pMesh || nullptr == m_pShader)
	{
		return;
	}

	m_pShader->UpdateResourceData();
	m_pMesh->RenderMesh();
}

