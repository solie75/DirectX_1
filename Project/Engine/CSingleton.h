#pragma once

typedef void(*EXIT)(void); // 함수포인터 typedef

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

// 왜 class 밖에서 싱글톤 객체가 담길 변수인 m_Inst 를 초기화 하는가
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

