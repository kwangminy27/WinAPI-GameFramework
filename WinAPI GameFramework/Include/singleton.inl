#pragma once

using namespace std;

template <typename T>
unique_ptr<T, function<void(T*)>> Singleton<T>::instance_;
template <typename T>
once_flag Singleton<T>::once_flag_;

template <typename T>
unique_ptr<T, function<void(T*)>>& Singleton<T>::GetInstance()
{
	call_once(once_flag_, []() {
		instance_ = unique_ptr<T, function<void(T* p)>>(new T, [](T* p) {
			p->_Release();
			delete p;
		});
	});
	return instance_;
}