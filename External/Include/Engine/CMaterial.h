#pragma once
#include "CResource.h"

#include "CGraphicsShader.h"

#include "ptr.h"

#include "CTexture.h"

class CMaterial :
    public CResource
{
private:
    Ptr<CGraphicsShader> m_pShader;

    tMaterialConst m_MaterialConst;

    Ptr<CTexture>   m_arrTexture[TEX_END];

public:
    void SetScalarParam(SCALAR_PARAM _Param, void* _Src);
    void SetTextureParam(TEXTURE_PARAM _Param, const Ptr<CTexture>& _Texture);
    void SetShader(Ptr<CGraphicsShader> _Shader) { m_pShader = _Shader; }

    virtual void UpdateResourceData() override;

private:
    virtual int LoadResourceData(const wstring& _strFilePath) { return S_OK; };

public:
    virtual int SaveResourceData(const wstring& _strFileReleativePath) { return S_OK; };

public:
    CMaterial();
    ~CMaterial();
};


