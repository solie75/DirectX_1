#include "pch.h"
#include "CMaterial.h"
#include "CDevice.h"
#include "CConstBuffer.h"

CMaterial::CMaterial()
	: CResource(RESOURCE_TYPE::MATERIAL)
	, m_MaterialConst{}
	, m_arrTexture{}
{
}

CMaterial::~CMaterial()
{
}


void CMaterial::SetScalarParam(SCALAR_PARAM _Param, void* _Src)
{
	switch (_Param)
	{
	case INT_0:
	case INT_1:
	case INT_2:
	case INT_3:
		m_MaterialConst.arrInt[_Param] = *((int*)_Src);
		break;

	case FLOAT_0:
	case FLOAT_1:
	case FLOAT_2:
	case FLOAT_3:
		m_MaterialConst.arrFloat[_Param - FLOAT_0] = *((float*)_Src);
		break;

	case VEC2_0:
	case VEC2_1:
	case VEC2_2:
	case VEC2_3:
		m_MaterialConst.arrV2[_Param - VEC2_0] = *((Vec2*)_Src);
		break;

	case VEC4_0:
	case VEC4_1:
	case VEC4_2:
	case VEC4_3:
		m_MaterialConst.arrV4[_Param - VEC4_0] = *((Vec4*)_Src);
		break;

	case MATRIX_0:
	case MATRIX_1:
	case MATRIX_2:
	case MATRIX_3:
		m_MaterialConst.arrMatrix[_Param - MATRIX_0] = *((Matrix*)_Src);
		break;
	}
}

void CMaterial::SetTextureParam(TEXTURE_PARAM _Param, const Ptr<CTexture>& _Texture)
{
	m_arrTexture[_Param] = _Texture;
}

void CMaterial::UpdateResourceData()
{
	if (nullptr == m_pShader)
	{
		return;
	}

	// Texture update
	for (UINT i = 0; i < TEX_END; ++i)
	{
		if (nullptr == m_arrTexture[i])
		{
			continue;
		}
		else
		{
			m_arrTexture[i]->UpdateTextureData(i,PIPELINE_STAGE::PS_PIXEL);
		}
	}

	// Constant Update
	CConstBuffer* pMaterialBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pMaterialBuffer->SetConstBufferData(&m_MaterialConst);
	pMaterialBuffer->UpdateConstBufferData();
}