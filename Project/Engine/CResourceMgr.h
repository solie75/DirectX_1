#pragma once
#include "CSingleton.h"
#include "CResource.h"
#include "ptr.h"

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
};

template<typename T>
RESOURCE_TYPE GetResourceType()
{
    const type_info& mesh = typeid(CMesh);
    const type_info& graphicsShader = typeid(CGraphicsShader);

    if (typeid(T).hash_code == mesh.hash_code())
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

//template<typename T>
//inline Ptr<T> CResourceMgr::FindRes(const wstring& _strKey)
//{
//    if (typeid(T).hash_code() == typeid(CMesh).hash_code()) // ���ø��� T �� CMesh �� ���
//    {
//        map<wstring, Ptr<CResource>>::iterator iter = m_arrRes[(UINT)RESOURCE_TYPE::MESH].find(_strKey);
//        // iterator �� ����Ͽ� �־��� Key �� ������ m_arrRes ���� ��Ҹ� ã�´�. �̶� ã�� �� ������ end() �� ��ȯ�Ѵ�.
//        if (iter == m_arrRes[(UINT)RESOURCE_TYPE::MESH].end())
//        // �ᱹ ã�� ���� ���
//        {
//            return nullptr;
//        }
//
//        return (T*)iter->second.GetResource();
//        // �־��� key�� �ش��ϴ� ����� second�� Ptr<CReaource>�� ��ȯ�Ѵ�.
//    }
//
//    if (typeid(T).hash_code() == typeid(CGraphicsShader).hash_code())
//    {
//        map<wstring, Ptr<CResource>>::iterator iter = m_arrRes[(UINT)RESOURCE_TYPE::GRAPHICS_SHADER].find(_strKey);
//        if (iter == m_arrRes[(UINT)RESOURCE_TYPE::GRAPHICS_SHADER].end())
//        {
//            return nullptr;
//        }
//        return (T*)iter->second.GetResource();
//    }
//    
//    return nullptr;
//}


