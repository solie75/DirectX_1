#pragma once

typedef void(*EXIT)(void); // �Լ������� typedef

template<typename T>
class CSingleton
{
private:
	static T* m_Inst;

public:
	static T* GetInst();
	static void Destroy();

public:
	CSingleton() {}
	virtual ~CSingleton() {}
};

// �� class �ۿ��� �̱��� ��ü�� ��� ������ m_Inst �� �ʱ�ȭ �ϴ°�
template<typename T>
T* CSingleton<T>::m_Inst = nullptr;

template<typename T>
inline T* CSingleton<T>::GetInst()
{
	if (nullptr == m_Inst)
	{
		m_Inst = new T;
		atexit((EXIT) &CSingleton<T>::Destroy);
	}

	return m_Inst;
}

template<typename T>
inline void CSingleton<T>::Destroy()
{
	if (nullptr != m_Inst)
	{
		delete m_Inst;
		m_Inst = nullptr;
	}
}

