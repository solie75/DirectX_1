#pragma once
#include "CResource.h"
class CMesh :
    public CResource
{
private:
    ComPtr<ID3D11Buffer> m_VB;
    D3D11_BUFFER_DESC m_tVBDesc;
    UINT m_VtxCount;

    ComPtr<ID3D11Buffer> m_IB;
    D3D11_BUFFER_DESC m_tIBDesc;
    UINT m_IdxCount;

    void* m_pVtxSys; // 정점을 자료형으로 하고 현재 정점의 개수를 요소의 수로하는 배열
    void* m_pIdxSys;

public:
    void CreateMesh(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount);
    void RenderMesh();

private:
    virtual void UpdateResourceData() override;

public:
    CMesh();
    ~CMesh();
};

