#include "button_ui.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"
#include "../Collision/collider_rect.h"

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
	if (!UI::_Initialize())
		return false;
	
	state_ = BUTTON_STATE::NORMAL;

	set_position(200.f, 200.f);
	set_size(200.f, 100.f);
	set_pivot(0.5f, 0.5f);
	set_offset({ 0.f, 0.f });

	texture_ = ResourceManager::instance()->LoadTexture("Button", L"StartButton.bmp");

	auto collider_rect = dynamic_pointer_cast<ColliderRect>(AddCollider<ColliderRect>("ButtonBody"));
	collider_rect->set_collision_group_tag("UI");
	collider_rect->set_model({ 0.f, 0.f, 200.f, 100.f });
	collider_rect->set_pivot({ 0.5f, 0.5 });
	collider_rect->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		_OnCollisionEnter(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);
	collider_rect->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		_OnCollision(src, dest, time);
	}, COLLISION_CALLBACK::STAY);
	collider_rect->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		_OnCollisionLeave(src, dest, time);
	}, COLLISION_CALLBACK::LEAVE);

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

void ButtonUI::_OnCollisionEnter(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
}

void ButtonUI::_OnCollision(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
}

void ButtonUI::_OnCollisionLeave(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
}