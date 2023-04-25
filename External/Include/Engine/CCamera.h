#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    float m_fAspectRatio; // Á¾È¾ºñ
    PROJECTION_TYPE m_ProjectionType;

    Matrix m_matView;
    Matrix m_matProjection;

public:
    const Matrix& GetViewMatrix() { return m_matView; }
    const Matrix& GetProjectionMatrix() { return m_matProjection; }

    void SetProjectionType(PROJECTION_TYPE _t) { m_ProjectionType = _t; }
    PROJECTION_TYPE GetProjectionType() { return m_ProjectionType; }

public:
    virtual void ComponentFinaltick() override;

    CLONE(CCamera);

public:
    CCamera();
    ~CCamera();
};

