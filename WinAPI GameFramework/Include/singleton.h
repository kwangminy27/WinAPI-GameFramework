#pragma once

#include "stdafx.h"

template <typename T>
class Singleton
{
public:
	static std::unique_ptr<T>& GetInstance();

protected:
	Singleton() = default;
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

private:
	static std::unique_ptr<T> instance_;
	static std::once_flag once_flag_;
};

#include "singleton.inl"