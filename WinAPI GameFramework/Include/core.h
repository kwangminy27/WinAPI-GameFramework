#pragma once

#include "singleton.h"

class Core : public Singleton<Core>
{
	friend class Singleton<Core>;
public:
	bool Initialize(wchar_t const* class_name, wchar_t const* window_name, HINSTANCE instance, HICON icon, Resolution resolution);
	int Run();

private:
	Core() = default;
	Core(Core const&) = delete;
	Core& operator=(Core const&) = delete;

	static LRESULT CALLBACK _WindowProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param);
	void _RegisterClass(wchar_t const* class_name, HICON icon);
	void _CreateWindow(wchar_t const* class_name, wchar_t const* window_name);

	HINSTANCE instance_;
	HWND window_;
	Resolution resolution_;
};