#pragma once

using namespace std;

template <typename T>
unique_ptr<T> Singleton<T>::instance_;
template <typename T>
once_flag Singleton<T>::once_flag_;

template <typename T>
unique_ptr<T>& Singleton<T>::GetInstance()
{
	call_once(once_flag_, []() {
		instance_.reset(new T);
	});
	return instance_;
}