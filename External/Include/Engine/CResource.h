#pragma once
#include "CEntity.h"

class CResource :
    public CEntity
{
private:
    const RESOURCE_TYPE m_Type;
    UINT m_iRefCount; // reference count  // ��� ���̴°�?

public:
    CResource(RESOURCE_TYPE _type);
    virtual ~CResource();
};

