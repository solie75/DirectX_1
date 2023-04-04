#pragma once

template<typename T, UINT Size>
void Safe_Del_Array(T* (&arr)[Size])
{
	for (UINT i = 0; i < Size; ++i)
	{
		if (nullptr != arr[i])
		{
			delete arr[i];
		}
	}
}

template<typename T>
void Safe_Del_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		for (nullptr != _vec[i])
		{
			delete _vec[i];
		}
	}
	_vec.clear();
}