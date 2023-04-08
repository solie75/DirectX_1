#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    ComPtr<ID3D11Texture2D> m_Texture2D;
    ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
    D3D11_TEXTURE2D_DESC m_DESC;

    //ScratchImage m_Image;
};

