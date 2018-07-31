#include "button_ui.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"

using namespace std;

ButtonUI::ButtonUI(ButtonUI const& other) : UI(other)
{
	state_ = other.state_;
}

ButtonUI::ButtonUI(ButtonUI&& other) noexcept : UI(move(other))
{
	state_ = move(other.state_);
}

void ButtonUI::_Release()
{
}

bool ButtonUI::_Initialize()
{
	if (UI::_Initialize())
		return false;
	
	state_ = BUTTON_STATE::NORMAL;

	set_position(200.f, 200.f);
	set_size(200.f, 100.f);
	set_pivot(0.5f, 0.5f);
	set_offset({ 200.f, 0.f });

	texture_ = ResourceManager::instance()->LoadTexture("Button", L"StartButton.bmp");

	return true;
}

void ButtonUI::_Input(float time)
{
	UI::_Input(time);
}

void ButtonUI::_Update(float time)
{
	UI::_Update(time);
}

void ButtonUI::_LateUpdate(float time)
{
	UI::_LateUpdate(time);
}

void ButtonUI::_Collision(float time)
{
	UI::_Collision(time);
}

void ButtonUI::_Render(HDC device_context, float time)
{
	UI::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> ButtonUI::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{ new ButtonUI(*this), [](Object* p) {
		dynamic_cast<ButtonUI*>(p)->_Release();
		delete dynamic_cast<ButtonUI*>(p);
	} };
}