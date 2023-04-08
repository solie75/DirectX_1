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
    map<wstring, Ptr<CResource>> m_arrRes[(UINT)RESOURCE_TYPE::END]; // CreateDefaultMesh() �Լ��� ��ġ�� ���⿡ �⺻ �簢���� ����ִ�.

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
    // �����Ϸ��� Ű�� �̹� �����ϴ� ���
    assert(!(FindRes<T>(_strKey)));

    RESOURCE_TYPE type = GetResourceType<T>();
    m_arrRes[(UINT)type].insert(make_pair(_strKey, _Resource.GetResource()));
    _Resource->SetKey(_strKey); // �̰��� �ᱹ �޾ƿ� �Ű������� �����ϴ� �� �ƴѰ�> �ٽ� m_arrRes[] �� �����Ѱ��� �����;� �ϴ°� �ƴѰ�.
}

template<typename T>
inline Ptr<T> CResourceMgr::Load(const wstring& _strKey, const wstring& _strRelativePath)
{
    Ptr<CResource> pResource = FindRes<T>(_strKey).GetResource();

    // �ش� ��ο� �̹� ���ҽ��� �����Ѵٸ� ��ȯ
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

    // ���ø� �Լ� ���� �ٸ� ���ø� �Լ��� ����ϴ� ��
    // �ڽ��� �Լ��� �ٽ� ȣ���ϴ� �� �� ���ø����� �����Ѱ�
    // ������� ; �νĵ� ���� �ʴ´�.
}