#include "core.h"
#include "timer.h"
#include "Input.h"
#include "path_manager.h"
#include "Scene/scene_manager.h"
#include "Object/object_manager.h"
#include "Resource/resource_manager.h"
#include "Resource/texture.h"
#include "Collision/collision_manager.h"
#include "Collision/collider.h"

using namespace std;

bool Core::Initialize(wchar_t const* class_name, wchar_t const* window_name, HINSTANCE instance, HICON icon)
{	
	main_instance_ = instance;
	_SetFlag(FLAG::RUN, true);

	_RegisterClass(class_name, icon);
	_CreateWindow(class_name, window_name);

	device_context_ = GetDC(main_window_);

	timer_ = unique_ptr<Timer, function<void(Timer*)>>(new Timer, [](Timer* p) {
		delete p;
	});
	timer_->Initialize();
	time_scale_ = 1.f;

	if (!Input::instance()->Initialize())
		return false;

	if (!PathManager::instance()->Initialize())
		return false;

	if (!ResourceManager::instance()->Initialize())
		return false;

	if (!SceneManager::instance()->Initialize())
		return false;
	
	if (!CollisionManager::instance()->Initialize())
		return false;

	back_buffer_ = ResourceManager::instance()->FindTexture("BackBuffer"s);

	return true;
}

int Core::Run()
{
	MSG message{};
	while (_GetFlag(FLAG::RUN))
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			_Logic();
		}
	}

	return static_cast<int>(message.wParam);
}

HINSTANCE Core::main_instance() const
{
	return main_instance_;
}

HWND Core::main_window() const
{
	return main_window_;
}

HDC Core::device_context() const
{
	return device_context_;
}

void Core::_Release()
{
	ReleaseDC(main_window_, device_context_);

	// Coliider Brush »èÁ¦
	DeleteObject(Collider::red_brush_);
	DeleteObject(Collider::green_brush_);
}

LRESULT Core::_WindowProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (w_param)
		{
		case VK_ESCAPE:
			DestroyWindow(window);
			break;
		}
		return 0;
	case WM_DESTROY:
		Core::instance()->_SetFlag(FLAG::RUN, false);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(window, message, w_param, l_param);
}

void Core::_RegisterClass(wchar_t const* class_name, HICON icon)
{
	WNDCLASS wc{};
	wc.lpfnWndProc = Core::_WindowProc;
	wc.hInstance = main_instance_;
	wc.hIcon = icon;
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
	wc.lpszClassName = class_name;
	RegisterClass(&wc);
}

void Core::_CreateWindow(wchar_t const* class_name, wchar_t const* window_name)
{
	main_window_ = CreateWindow(
		class_name, window_name,
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, main_instance_,
		nullptr
	);

	if (!main_window_)
		return;

	RECT rc{ 0, 0, static_cast<long>(RESOLUTION::WIDTH), static_cast<long>(RESOLUTION::HEIGHT) };
	AdjustWindowRect(&rc, WS_CAPTION | WS_SYSMENU, false);
	SetWindowPos(main_window_, HWND_TOP, 100, 100, rc.right - rc.left, rc.bottom - rc.top, NULL);

	ShowWindow(main_window_, SW_SHOW);
}

void Core::_SetFlag(FLAG flag, bool value)
{
	flag_.at(static_cast<int>(flag)) = value;
}

void Core::_Logic()
{
	timer_->Update();

	float delta_time = timer_->delta_time();

	Input::instance()->Update(delta_time * time_scale_);

	_Input(delta_time * time_scale_);
	_Update(delta_time * time_scale_);
	_Collision(delta_time * time_scale_);
	_Render(delta_time * time_scale_);

	if(Input::instance()->KeyPush("Pause"s))
		time_scale_ = time_scale_ == 1.f ? 0.f : 1.f;

	ObjectManager::instance()->ClearExpiredSceneObject();
	CollisionManager::instance()->ClearExpiredCollider();
}

void Core::_Input(float time)
{ 
	SceneManager::instance()->Input(time);
}

void Core::_Update(float time)
{
	auto const& scene_manager = SceneManager::instance();
	scene_manager->Update(time);
	scene_manager->LateUpdate(time);
}

void Core::_Collision(float time)
{
	SceneManager::instance()->Collision(time);
	CollisionManager::instance()->Collision(time);
}

void Core::_Render(float time)
{
	auto const& scene_manager = SceneManager::instance();
	auto back_buffer = back_buffer_.lock();

	Rectangle(back_buffer->memory_device_context(),
		0, 0, static_cast<int>(RESOLUTION::WIDTH), static_cast<int>(RESOLUTION::HEIGHT));

	scene_manager->Render(back_buffer->memory_device_context(), time);

	BitBlt(device_context_,
		0, 0, static_cast<int>(RESOLUTION::WIDTH), static_cast<int>(RESOLUTION::HEIGHT),
		back_buffer->memory_device_context(),
		0, 0, SRCCOPY);

	wstring wstr = to_wstring(timer_->frame_per_second());
	wstr += L" FPS";
	float LTGRAY = 255 * 0.75f;
	SetBkColor(device_context_, RGB(LTGRAY, LTGRAY, LTGRAY));
	TextOut(device_context_, 0, 0, wstr.c_str(), static_cast<int>(wstr.size()));

	//random_device rd;
	//mt19937 gen(rd());
	//uniform_real_distribution<double> urdistr(0.0, 1.0);
	//bernoulli_distribution distr(urdistr(gen));
	//unordered_map<bool, int> histogram;
	//for (int i = 0; i < 100; ++i)
	//	++histogram[distr(gen)];
}

bool Core::_GetFlag(FLAG flag) const
{
	switch (flag)
	{
	case FLAG::RUN:
		return flag_.at(static_cast<int>(FLAG::RUN));
	}

	return false;
}
