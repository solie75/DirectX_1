#pragma once
#include "CEntity.h"
class CConstBuffer :
    public CEntity
{
private:
    ComPtr<ID3D11Buffer> m_CB;
    D3D11_BUFFER_DESC m_Desc;
    const UINT m_iRegisterNum;

    UINT m_iElementSize;
    UINT m_iElementCount;

public:
    void CreateConstBuffer(UINT _iElementSize, UINT _iElementCount);
    void SetConstBufferData(void* _pSrc, UINT _iSize = 0);
    void UpdateConstBufferData();

    ComPtr<ID3D11Buffer> GetConstBuffer() { return m_CB; }

    CLONE(CConstBuffer);

public:
    CConstBuffer(UINT _iRegisterNum);
    ~CConstBuffer();
};

