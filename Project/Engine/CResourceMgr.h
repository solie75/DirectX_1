#pragma once
#include "CSingleton.h"
#include "CResource.h"
#include "ptr.h"

class CMesh;

class CResourceMgr :
    public CSingleton<CResourceMgr>
{
private:
    map<wstring, Ptr<CResource>> m_arrRes[(UINT)RESOURCE_TYPE::END];

public:
    void CResourceMgrInit();

private:
    void CreateDefaultMesh();
    void CreateDefaultGraphicsShader();

public:
    template<typename T>
    Ptr<T> FindResource(const wstring& _strKey);

public:
    CResourceMgr();
    ~CResourceMgr();
};

template<typename T>
inline Ptr<T> CResourceMgr::FindResource(const wstring& _strKey)
{
    if (typeid(T).hash_code() == typeid(CMesh).hash_code())
    {
        map<wstring, Ptr<CResource>::iterator iter = m_arrRes[(UINT)RESOURCE_TYPE::MESH].find(_strKey);
        if (iter == m_arrRes[(UINT)RESOURCE_TYPE::MESH].end())
        {
            return nullptr;
        }
        return (T*)iter->second.Get();
    }
    
    return nullptr;
}

