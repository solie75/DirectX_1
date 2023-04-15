#pragma once
#include "CResource.h"

#include "CGraphicsShader.h"

#include "ptr.h"

class CMaterial :
    public CResource
{
private:
    Ptr<CGraphicsShader> m_pShader;

    //tMtrlConst
};

