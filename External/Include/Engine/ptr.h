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

	void operator = (T* _Resource)
	{
		if (nullptr != m_Resource)
		{
			m_Resource->ReleaseResource();
		}

		m_Resource = _Resource;

		if (nullptr != m_Resource)
		{
			m_Resource->AddRef();
		}
	}

	void operator = (const Ptr<T>& _Resource)
	{
		if (nullptr != m_Resource)
		{
			m_Resource->ReleaseResource();
		}

		m_Resource = _Resource;

		if (nullptr != m_Resource)
		{
			m_Resource->AddRef();
		}
	}

public:
	Ptr()
		: m_Resource(nullptr)
	{

	}

	Ptr(T* _Resource)
		: m_Resource(_Resource)
	{
		if (nullptr != m_Resource)
		{
			m_Resource->AddRef();
		}
	}
	
	Ptr(const Ptr<T>& _Resource)
		:m_Resource(_Resource)
	{
		if (nullptr != m_Resource)
		{
			m_Resource->AddRef();
		}
	}

	~Ptr()
	{
		if (nullptr == m_Resource)
		{
			m_Resource->ReleaseResource();
		}
	}
};