#pragma once
#include "CResource.h"
#include <DirectXTex\DirectXTex.h>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex//DirectXTex_debug")
#else
#pragma comment(lib, "DirectXTex//DirectXTex")
#endif

class CTexture :
    public CResource
{
private:
    ComPtr<ID3D11Texture2D> m_Texture2D;
    ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
    D3D11_TEXTURE2D_DESC m_DESC;

    ScratchImage m_Image;

private:
    virtual int LoadResourceData(const wstring& _strFilePath) override;
public:
    virtual int SaveResourceData(const wstring& _strRelativePath) override;

private:
    virtual void UpdateResourceData() override;
public:
    void UpdateTextureData(int _iRegisterNum, int _PipelineStage);
public:
    CTexture();
    ~CTexture();
};

