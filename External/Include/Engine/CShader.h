#pragma once
#include "CResource.h"
class CShader :
    public CResource
{
protected:
    // CShader �� ��� �޴� CGraphicsShader ���� ���̴� ������ �Լ� ��� �ش� �ɹ��� 
    // �����Ϸ� �ϹǷ� �ڽ� ��ü�� ���ؼ� ������ ����ϴ� protect �� m_ErrBlob �� �����Ѵ�.
    ComPtr<ID3DBlob> m_ErrBlob;

private:
    virtual int LoadResourceData(const wstring& _strFilePath) { return S_OK; }
public:
    virtual int SaveResourceData(const wstring& _strRelativePath) { return S_OK; }


public:
    CShader(RESOURCE_TYPE _eType);
    ~CShader();
};

