#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    float m_fAspectRatio; // Á¾È¾ºñ

    Matrix m_matView;
    Matrix m_matProjection;

public:
    const Matrix& GetViewMatrix() { return m_matView; }
    const Matrix& GetProjectionMatrix() { return m_matProjection; }

public:
    virtual void ComponentFinaltick() override;

    CLONE(CCamera);

public:
    CCamera();
    ~CCamera();
};

