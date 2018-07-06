#pragma once

#include "singleton.h"

class Timer;

class Core : public Singleton<Core>
{
	friend class Singleton<Core>;
public:
	bool Initialize(wchar_t const* class_name, wchar_t const* window_name, HINSTANCE instance, HICON icon);
	int Run();

private:
	Core() = default;
	Core(Core const&) = delete;
	Core& operator=(Core const&) = delete;

	virtual void _Release();

	static LRESULT CALLBACK _WindowProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param);
	void _RegisterClass(wchar_t const* class_name, HICON icon);
	void _CreateWindow(wchar_t const* class_name, wchar_t const* window_name);
	bool _GetFlag(FLAG flag) const;
	void _SetFlag(FLAG flag, bool value);

	void _Logic();
	void _Input(float delta_time);
	void _Update(float delta_time);
	void _Collision(float delta_time);
	void _Render(float delta_time);

	HINSTANCE instance_{};
	HWND window_{};
	HDC device_context_{};

	std::array<bool, static_cast<int>(FLAG::END)> flag_{};
	std::unique_ptr<Timer, std::function<void(Timer* p)>> timer_{};
};