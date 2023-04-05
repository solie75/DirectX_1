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
    map<wstring, Ptr<CResource>> m_arrRes[(UINT)RESOURCE_TYPE::END]; // CreateDefaultMesh() 함수를 거치면 여기에 기본 사각형이 들어있다.

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
//    if (typeid(T).hash_code() == typeid(CMesh).hash_code()) // 템플릿의 T 가 CMesh 인 경우
//    {
//        map<wstring, Ptr<CResource>>::iterator iter = m_arrRes[(UINT)RESOURCE_TYPE::MESH].find(_strKey);
//        // iterator 를 사용하여 주어진 Key 를 가지고 m_arrRes 상의 요소를 찾는다. 이때 찾는 게 없으면 end() 를 반환한다.
//        if (iter == m_arrRes[(UINT)RESOURCE_TYPE::MESH].end())
//        // 결국 찾지 못한 경우
//        {
//            return nullptr;
//        }
//
//        return (T*)iter->second.GetResource();
//        // 주어진 key에 해당하는 요소의 second인 Ptr<CReaource>를 반환한다.
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


