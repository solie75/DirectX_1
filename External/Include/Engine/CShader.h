#pragma once
#include "CResource.h"
class CShader :
    public CResource
{
protected:
    // CShader 를 상속 받는 CGraphicsShader 에서 쉐이더 컴파일 함수 등에서 해당 맴버에 
    // 접근하려 하므로 자식 개체에 한해서 접근을 허용하는 protect 로 m_ErrBlob 을 지정한다.
    ComPtr<ID3DBlob> m_ErrBlob;

public:
    CShader(RESOURCE_TYPE _eType);
    ~CShader();
};

