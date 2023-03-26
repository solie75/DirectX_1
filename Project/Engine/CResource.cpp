#include "pch.h"
#include "CResource.h"

CResource::CResource(RESOURCE_TYPE _type)
	: m_Type(_type)
	, m_iRefCount(0)
{
}

CResource::~CResource()
{
}

void CResource::ReleaseResource()
{
	--m_iRefCount;

	if (0 == m_iRefCount)
	{
		delete this;
	}
}