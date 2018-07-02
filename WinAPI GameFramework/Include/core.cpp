#include "core.h"

using namespace std;

bool Core::Initialize(wchar_t const* class_name, wchar_t const* window_name, HINSTANCE instance, HICON icon, Resolution resolution)
{
	instance_ = instance;
	resolution_ = resolution;

	_RegisterClass(class_name, icon);

	_CreateWindow(class_name, window_name);

	return true;
}

int Core::Run()
{
	MSG message{};
	while (GetMessage(&message, nullptr, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return static_cast<int>(message.wParam);
}

LRESULT Core::_WindowProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(window, message, w_param, l_param);
}

void Core::_RegisterClass(wchar_t const* class_name, HICON icon)
{
	WNDCLASS wc{};
	wc.lpfnWndProc = Core::_WindowProc;
	wc.hInstance = instance_;
	wc.hIcon = icon;
	wc.lpszClassName = class_name;
	RegisterClass(&wc);
}

void Core::_CreateWindow(wchar_t const* class_name, wchar_t const* window_name)
{
	window_ = CreateWindow(
		class_name, window_name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, instance_,
		nullptr
	);

	if (!window_)
		return;

	RECT rc{ 0, 0, resolution_.width_, resolution_.height_ };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(window_, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, NULL);

	ShowWindow(window_, SW_SHOW);
}
