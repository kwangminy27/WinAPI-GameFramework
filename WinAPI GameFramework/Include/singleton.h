#pragma once

#include "stdafx.h"

template <typename T>
class Singleton
{
public:
	static std::unique_ptr<T, std::function<void(T* p)>>& GetInstance();

protected:
	Singleton() = default;
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

	virtual void _Release() = 0;

private:
	static std::unique_ptr<T, std::function<void(T* p)>> instance_;
	static std::once_flag once_flag_;
};

#include "singleton.inl"