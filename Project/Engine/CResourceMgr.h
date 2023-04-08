#pragma once
#include "CSingleton.h"
#include "CResource.h"
#include "ptr.h"

#include "CPathMgr.h"

#include "CMesh.h"
#include "CGraphicsShader.h"

class CResourceMgr :
    public CSingleton<CResourceMgr>
{
    SINGLE(CResourceMgr)
private:
    map<wstring, Ptr<CResource>> m_arrRes[(UINT)RESOURCE_TYPE::END]; // CreateDefaultMesh() 함수를 거치면 여기에 기본 사각형이 들어있다.

public:
    void ResourceMgrInit();

private:
    void CreateDefaultMesh();
    void CreateDefaultGraphicsShader();

public:
    template<typename T>
    Ptr<T> FindRes(const wstring& _strKey);

    template<typename T>
    void AddResource(const wstring& _strKey, Ptr<T>& _Resource);

    template<typename T>
    Ptr<T> Load(const wstring& _strKey, const wstring& _strRelativePath);
};

template<typename T>
RESOURCE_TYPE GetResourceType()
{
    const type_info& mesh = typeid(CMesh);
    const type_info& graphicsShader = typeid(CGraphicsShader);

    if (typeid(T).hash_code() == mesh.hash_code())
    {
        return RESOURCE_TYPE::MESH;
    }
    if (typeid(T).hash_code() == graphicsShader.hash_code())
    {
        return RESOURCE_TYPE::GRAPHICS_SHADER;
    }

    return RESOURCE_TYPE::END;
}


template<typename T>
inline Ptr<T> CResourceMgr::FindRes(const wstring& _strKey)
{
    RESOURCE_TYPE resType = GetResourceType<T>();

    map<wstring, Ptr<CResource>>::iterator iter = m_arrRes[(UINT)resType].find(_strKey);

    if (iter == m_arrRes[(UINT)resType].end())
    {
        return nullptr;
    }

    return (T*)iter->second.GetResource();
}

template<typename T>
inline void CResourceMgr::AddResource(const wstring& _strKey, Ptr<T>& _Resource)
{
    // 저장하려는 키가 이미 존재하는 경우
    assert(!(FindRes<T>(_strKey)));

    RESOURCE_TYPE type = GetResourceType<T>();
    m_arrRes[(UINT)type].insert(make_pair(_strKey, _Resource.GetResource()));
    _Resource->SetKey(_strKey); // 이것은 결국 받아온 매개변수에 저장하는 것 아닌가> 다시 m_arrRes[] 에 저장한것을 가져와야 하는것 아닌가.
}

template<typename T>
inline Ptr<T> CResourceMgr::Load(const wstring& _strKey, const wstring& _strRelativePath)
{
    Ptr<CResource> pResource = FindRes<T>(_strKey).GetResource();

    // 해당 경로에 이미 리소스가 존재한다면 반환
    if (nullptr != pResource)
    {
        return (T*)pResource.GetResource();
    }

    pResource = new T;
    pResource->SetKey(_strKey);
    pResource->SetRelativePath(_strRelativePath);
    
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    if (FAILED(pResource->Load(strFilePath))
    {
        assert(nullptr);
    }

    RESOURCE_TYPE type = GetResourceType<T>();
    m_arrRes[(UINT)type].insert(make_pair(_strKey, pResource));

    return (T*)pResource.GetResource();

    // 템플릿 함수 내에 다른 템플릿 함수를 사용하는 것
    // 자신의 함수를 다시 호출하는 것 이 템플릿에서 가능한가
    // 심지어는 ; 인식도 되지 않는다.
}