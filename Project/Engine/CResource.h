#pragma once
#include "CEntity.h"

class CResource :
    public CEntity
{
private:
    const RESOURCE_TYPE m_Type;
    int m_iRefCount; // reference count  // 어디에 쓰이는가?
    
    wstring m_strKey;
    wstring m_strRelativePath;

private:
    void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
    void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath; }

    void AddRef() { ++m_iRefCount; }
    void ReleaseResource();

public:
    const wstring& GetKey() { return m_strKey; }
    const wstring& GetRelativePath() { return m_strRelativePath; }

public:
    // 리소스 바인딩
    virtual void UpdateResourceData() = 0;

    // 리소스는 Clone 을 구현하지 않는다.
    virtual CResource* Clone() { return nullptr; assert(nullptr); }

private:
    virtual int ResourceLoad(const wstring& _strFilePath) = 0;

public:
    virtual int ResourceSave(const wstring& _strFileReleativePath) = 0;

public:
    CResource(RESOURCE_TYPE _type);
    virtual ~CResource();

    friend class CResourceMgr;

    template<typename T> // ...? template 의 friend 선언이란...?
    friend class Ptr;
};

