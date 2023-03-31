#pragma once
#include "CComponent.h"

#include "CMesh.h"
#include "CGraphicsShader.h"

class CMeshRender :
    public CComponent
{
private:
    CMesh* m_pMesh;
    CGraphicsShader* m_pShader;

public:
    void SetMesh(CMesh* _Mesh) { m_pMesh = _Mesh; }
    void SetShader(CGraphicsShader* _Shader) { m_pShader = _Shader; } 

    CMesh* GetMesh() { return m_pMesh; }
    CGraphicsShader* GetShader() { return m_pShader; }

public:
    virtual void ComponentFinaltick() override;

    void BeginRenderingMesh();

    CLONE(CMeshRender);

public:
    CMeshRender();
    ~CMeshRender();
};

