#pragma once

template<typename T>
class Ptr
{
private:
	T* m_Resource;

public:
	T* GetResource() { return m_Resource;}

	T* operator -> ()
	{
		return m_Resource;
	}

	void operator = (T* _resource)
	{
		if (nullptr != m_Resource)
		{
			m_Resource->ReleaseResource()
		}

		m_Resource = _resource;

		if (nullptr != m_Resource)
		{
			m_Resource->AddRef();
		}
	}
public:
	Ptr()
		: m_Res(nullptr)
	{

	}

	Ptr(T* _Resource)
		: m_Res(_resource)
	{
		if (nullptr != m_Resource)
		{
			m_Resource->AddRef();
		}
	}

	~Ptr()
	{
		if (nullptr == m_Res)
		{
			m_Res->ReleaseResource();
		}
	}
};