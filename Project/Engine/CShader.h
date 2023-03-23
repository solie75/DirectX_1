#pragma once
#include "CResource.h"
class CShader :
    public CResource
{
protected:
    ComPtr<ID3DBlob> m_ErrBlob;

public:
    CShader(RESOURCE_TYPE _eType);
    ~CShader();
};

