#pragma once

template<typename T>
class Ptr
{
private:
	T* m_Resource;

public:
	T* GetResource() const { return m_Resource;}

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

	bool operator == (T* _Other)
	{
		return m_Resource == _Other;
	}

	bool operator != (T* _Other)
	{
		return m_Resource != _Other;
	}

	bool operator == (const Ptr<T>& _Other)
	{
		return m_Resource == _Other.m_Resource;
	}

	bool operator == (const Ptr<T>& _Other)
	{
		return m_Resource != _Other.m_Resource;
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
		if (nullptr != m_Resource)
		{
			m_Resource->ReleaseResource();
		}
	}
};

template<typename T>
bool operator == (void* _Res, const Ptr<T>& _Ptr)
{
	return _Res == _Ptr.GetResource();
}

template<typename T>
bool operator != (void* _Res, const Ptr<T>& _Ptr)
{
	return _Res != _Ptr.GetResource();
}