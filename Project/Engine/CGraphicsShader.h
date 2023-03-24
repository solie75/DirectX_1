#pragma once
#include "CShader.h"
class CGraphicsShader :
    public CShader
{
private:
    ComPtr<ID3DBlob> m_VSBlob; // vertex shader
    ComPtr<ID3DBlob> m_HSBlob; // hull shader
    ComPtr<ID3DBlob> m_DSBlob; // domain shader
    ComPtr<ID3DBlob> m_GSBlob; // geometry shader
    ComPtr<ID3DBlob> m_PSBlob; // pixel shader

    ComPtr<ID3D11VertexShader> m_VS;
    ComPtr<ID3D11HullShader> m_HS;
    ComPtr<ID3D11DomainShader> m_DS;
    ComPtr<ID3D11GeometryShader> m_GS;
    ComPtr<ID3D11PixelShader> m_PS;

    ComPtr<ID3D11InputLayout> m_Layout;
    D3D11_PRIMITIVE_TOPOLOGY m_eTopology;

public:
    void CreateVertexShader(const wstring& _strFileName, const string& _strFuncName); // 파일명과 함수명...?
    void CreatePixelShader(const wstring& _strFileName, const string& _strFuncName);
    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology) {m_eTopology = _Topology};

    virtual void UpdateData() override;

public:
    CGraphicsShader();
    ~CGraphicsShader();

};

