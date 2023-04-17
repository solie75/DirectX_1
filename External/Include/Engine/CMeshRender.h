#pragma once
#include "CComponent.h"

#include "CMesh.h"
#include "CMaterial.h"
#include "ptr.h"

class CMeshRender :
    public CComponent
{
private:
    Ptr<CMesh> m_pMesh;
    Ptr<CMaterial> m_pMaterial;

public:
    void SetMesh(Ptr<CMesh> _Mesh) { m_pMesh = _Mesh; }
    void SetMaterial(Ptr<CMaterial> _Material) { m_pMaterial = _Material; }

    Ptr<CMesh> GetMesh() { return m_pMesh; }
    Ptr<CMaterial> GetMaterial() { return m_pMaterial; }

public:
    virtual void ComponentFinaltick() override;

    void BeginRenderingMesh();

    CLONE(CMeshRender);

public:
    CMeshRender();
    ~CMeshRender();
};

