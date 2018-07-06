#include "core.h"
#include "timer.h"
#include "Input.h"

using namespace std;

bool Core::Initialize(wchar_t const* class_name, wchar_t const* window_name, HINSTANCE instance, HICON icon)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc();

	instance_ = instance;
	_SetFlag(FLAG::RUN, true);

	_RegisterClass(class_name, icon);
	_CreateWindow(class_name, window_name);

	device_context_ = GetDC(window_);

	timer_ = unique_ptr<Timer, function<void(Timer* p)>>(new Timer, [](Timer* p) {
		delete p;
	});
	timer_->Initialize();
	time_scale_ = 1.f;

	if (!Input::GetInstance()->Initialize())
		return false;

	player_.SetRect(100, 100, 200, 200);

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

void Core::_Release()
{
	ReleaseDC(window_, device_context_);
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
		Core::GetInstance()->_SetFlag(FLAG::RUN, false);
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
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
	wc.lpszClassName = class_name;
	RegisterClass(&wc);
}

void Core::_CreateWindow(wchar_t const* class_name, wchar_t const* window_name)
{
	window_ = CreateWindow(
		class_name, window_name,
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, instance_,
		nullptr
	);

	if (!window_)
		return;

	RECT rc{ 0, 0, static_cast<long>(RESOLUTION::WIDTH), static_cast<long>(RESOLUTION::HEIGHT) };
	AdjustWindowRect(&rc, WS_CAPTION | WS_SYSMENU, false);
	SetWindowPos(window_, HWND_TOP, 100, 100, rc.right - rc.left, rc.bottom - rc.top, NULL);

	ShowWindow(window_, SW_SHOW);
}

void Core::_SetFlag(FLAG flag, bool value)
{
	flag_.at(static_cast<int>(flag)) = value;
}

void Core::_Logic()
{
	timer_->Update();

	float delta_time = timer_->GetDeltaTime();

	Input::GetInstance()->Update(delta_time * time_scale_);

	_Input(delta_time * time_scale_);
	_Update(delta_time * time_scale_);
	_Collision(delta_time * time_scale_);
	_Render(delta_time * time_scale_);

	if(Input::GetInstance()->KeyPush("Pause"s))
		time_scale_ = time_scale_ == 1.f ? 0.f : 1.f;
}

void Core::_Input(float delta_time)
{
	static int const kMoveSpeed = 200;

	auto const& input_manager = Input::GetInstance();

	static auto KeyPush = [&input_manager](string const& name) -> bool { return input_manager->KeyPush(name); };
	static auto KeyPressed = [&input_manager](string const& name) -> bool { return input_manager->KeyPressed(name); };
	static auto KeyUp = [&input_manager](string const& name) -> bool { return input_manager->KeyUp(name); };

	if (KeyPressed("MoveUp"s))
	{
		player_.Move(0, -kMoveSpeed * delta_time);
	}

	if (KeyPressed("MoveDown"s))
	{
		player_.Move(0, kMoveSpeed * delta_time);
	}

	if (KeyPressed("MoveLeft"s))
	{
		player_.Move(-kMoveSpeed * delta_time, 0);
	}

	if (KeyPressed("MoveRight"s))
	{
		player_.Move(kMoveSpeed * delta_time, 0);
	}

	if (KeyPush("Fire"s))
	{
		Rect rect = player_;
		rect.Move(player_.GetWidth(), 0);
		bullet_list_.push_back(move(rect));
	}
}

void Core::_Update(float delta_time)
{
	for (auto & bullet : bullet_list_)
		bullet.Move(100.f * delta_time, 0.f);
}

void Core::_Collision(float delta_time)
{
	bullet_list_.remove_if([](Rect rect) {
		return rect.l > static_cast<int>(RESOLUTION::WIDTH);
	});
}

void Core::_Render(float delta_time)
{
	wstring wstr = to_wstring(timer_->GetFPS());
	wstr += L" FPS";
	float LTGRAY = 255 * 0.75f;
	SetBkColor(device_context_, RGB(LTGRAY, LTGRAY, LTGRAY));
	TextOut(device_context_, 0, 0, wstr.c_str(), static_cast<int>(wstr.size()));

	player_.Render(device_context_);

	for (auto const& bullet : bullet_list_)
		bullet.RenderEllipse(device_context_);

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> urdistr(0.0, 1.0);
	bernoulli_distribution distr(urdistr(gen));
	unordered_map<bool, int> histogram;
	for (int i = 0; i < 100; ++i)
		++histogram[distr(gen)];

	wstr.clear();
	wstr = L"                                                                                                    ";
	TextOut(device_context_, 0, 200, wstr.c_str(), static_cast<int>(wstr.size()));
	wstr.clear();
	wstr = L"                                                                                                    ";
	TextOut(device_context_, 0, 215, wstr.c_str(), static_cast<int>(wstr.size()));
	wstr.clear();
	wstr = L"                                                                                                    ";
	TextOut(device_context_, 0, 230, wstr.c_str(), static_cast<int>(wstr.size()));
	wstr.clear();
	wstr = L"                                                                                                    ";
	TextOut(device_context_, 0, 245, wstr.c_str(), static_cast<int>(wstr.size()));
	wstr.clear();
	wstr = L"                                                                                                    ";
	TextOut(device_context_, 0, 260, wstr.c_str(), static_cast<int>(wstr.size()));

	wstr.clear();
	wstr.assign(histogram[true], L':');
	TextOut(device_context_, 0, 200, wstr.c_str(), static_cast<int>(wstr.size()));
	wstr.clear();
	wstr.assign(histogram[true], L':');
	TextOut(device_context_, 0, 215, wstr.c_str(), static_cast<int>(wstr.size()));
	wstr.clear();
	wstr.assign(histogram[true], L':');
	TextOut(device_context_, 0, 230, wstr.c_str(), static_cast<int>(wstr.size()));
	wstr.clear();
	wstr.assign(histogram[true], L':');
	TextOut(device_context_, 0, 245, wstr.c_str(), static_cast<int>(wstr.size()));
	wstr.clear();
	wstr.assign(histogram[true], L':');
	TextOut(device_context_, 0, 260, wstr.c_str(), static_cast<int>(wstr.size()));
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
