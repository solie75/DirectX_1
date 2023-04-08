#include "pch.h"
#include "CTexture.h"
#include "CDevice.h"

CTexture::CTexture()
    : CResource(RESOURCE_TYPE::TEXTURE)
    , m_Texture2D(nullptr)
    , m_ShaderResourceView(nullptr)
    , m_DESC{}
{
}

CTexture::~CTexture()
{
}

int CTexture::ResourceLoad(const wstring& _strFilePath)
{
    wchar_t szExt[50] = L"";
    _wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 50);
    wstring strExt = szExt;

    HRESULT hr = S_OK;
    if (L".dds" == strExt || L".DDS" == strExt)
    {
        // dds, DDS
        hr = LoadFromDDSFile(_strFilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_Image);
    }
    else if (L".tga" == strExt || L".TGA" == strExt)
    {
        // tga, TGA
        hr = LoadFromTGAFile(_strFilePath.c_str(), nullptr, m_Image);
    }
    else
    {
        // png, jpg, jpeg, bmp
        hr = LoadFromWICFile(_strFilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_Image);
    }
    
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"리소스 로딩 실패", L"텍스쳐 로딩 실패", MB_OK);
        return E_FAIL;
    }

    hr = CreateShaderResourceView(
        DEVICE,
        m_Image.GetImages(),
        m_Image.GetImageCount(),
        m_Image.GetMetadata(),
        m_ShaderResourceView.GetAddressOf()
    );

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"ShaderResourceView 생성실패", L"텍스쳐 로딩 실패", MB_OK);
        return E_FAIL;
    }

    m_ShaderResourceView->GetResource((ID3D11Resource**)m_Texture2D.GetAddressOf());
    m_Texture2D->GetDesc(&m_DESC);

    return 0;
}

int CTexture::ResourceSave(const wstring& _strRelativePath)
{
    return 0;
}

void CTexture::UpdateResourceData()
{
}


