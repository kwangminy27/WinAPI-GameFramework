#pragma once

#include "singleton.h"

class Timer;

class Core final : public Singleton<Core>
{
	friend class Singleton<Core>;
public:
	bool Initialize(wchar_t const* class_name, wchar_t const* window_name, HINSTANCE instance, HICON icon);
	int Run();

	HINSTANCE main_instance() const;
	HWND main_window() const;
	HDC device_context() const;

private:
	Core() = default;
	Core(Core const&) = delete;
	Core& operator=(Core const&) = delete;

	virtual void _Release() override;

	static LRESULT CALLBACK _WindowProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param);
	void _RegisterClass(wchar_t const* class_name, HICON icon);
	void _CreateWindow(wchar_t const* class_name, wchar_t const* window_name);

	bool _GetFlag(FLAG flag) const;
	void _SetFlag(FLAG flag, bool value);

	void _Logic();
	void _Input(float time);
	void _Update(float time);
	void _Collision(float time);
	void _Render(float time);

	HINSTANCE main_instance_{};
	HWND main_window_{};
	HDC device_context_{};

	std::array<bool, static_cast<int>(FLAG::END)> flag_{};
	std::unique_ptr<Timer, std::function<void(Timer*)>> timer_{};
	float time_scale_{};
};