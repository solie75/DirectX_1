#pragma once
#include "CSingleton.h"
#include "CResource.h"
#include "ptr.h"

#include "CPathMgr.h"

#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CTexture.h"
#include "CMaterial.h"

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
    void CreateDefaultMaterial();
    void LoadDefaultTexture();
    

public:
    template<typename T>
    Ptr<T> FindRes(const wstring& _strKey);

    template<typename T>
    void AddResource(const wstring& _strKey, Ptr<T>& _Resource);

    template<typename T>
    Ptr<T> LoadResource(const wstring& _strKey, const wstring& _strRelativePath);
};

template<typename T>
RESOURCE_TYPE GetResourceType()
{
    const type_info& mesh = typeid(CMesh);
    const type_info& graphicsShader = typeid(CGraphicsShader);
    const type_info& texture = typeid(CTexture);
    const type_info& material = typeid(CMaterial);

    if (typeid(T).hash_code() == mesh.hash_code())
    {
        return RESOURCE_TYPE::MESH;
    }
    if (typeid(T).hash_code() == graphicsShader.hash_code())
    {
        return RESOURCE_TYPE::GRAPHICS_SHADER;
    }
    if (typeid(T).hash_code() == texture.hash_code())
    {
        return RESOURCE_TYPE::TEXTURE;
    }
    if (typeid(T).hash_code() == material.hash_code())
    {
        return RESOURCE_TYPE::MATERIAL;
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
    assert(!FindRes<T>(_strKey).GetResource());

    RESOURCE_TYPE type = GetResourceType<T>();
    m_arrRes[(UINT)type].insert(make_pair(_strKey, _Resource.GetResource()));
    _Resource->SetKey(_strKey); // 이것은 결국 받아온 매개변수에 저장하는 것 아닌가> 다시 m_arrRes[] 에 저장한것을 가져와야 하는것 아닌가.
}

template<typename T>
inline Ptr<T> CResourceMgr::LoadResource(const wstring& _strKey, const wstring& _strRelativePath)
{
    Ptr<CResource> pResource = FindRes<T>(_strKey).GetResource();

    // 해당 경로에 리소스가 존재한다면 반환
    if (nullptr != pResource)
    {
        return (T*)pResource.GetResource();
    }

    // 해당 경로에 리소스가 존재하지 않는다면 리소스를 생성한다.
    pResource = new T;
    pResource->SetKey(_strKey); 
    pResource->SetRelativePath(_strRelativePath);
    
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    if (FAILED(pResource->LoadResourceData(strFilePath)))
        // pResource가 어떤 유형의 리소스인지 모르는 상황에서 
        // ResourceLoad 함수는 CMesh, CShader, CTexture 등 모두 가지고 있으니
        // 인식을 하지 못하는 것이다.
    {
        assert(nullptr);
    }

    RESOURCE_TYPE type = GetResourceType<T>();
    m_arrRes[(UINT)type].insert(make_pair(_strKey, pResource));

    return (T*)pResource.GetResource();

    // 템플릿 함수 내에 다른 템플릿 함수를 사용하는 것
    // 자신의 함수를 다시 호출하는 것 이 템플릿에서 가능한가
}