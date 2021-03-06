#include "mouse_ui.h"
#include "../Collision/collider_point.h"

using namespace std;

bool MouseUI::Initialize()
{
	if (!UI::Initialize())
		return false;

	set_size(32.f, 31.f);
	set_texture("Mouse", L"Mouse/0.bmp");
	set_color_key(RGB(255, 0, 255));

	auto collider_point = dynamic_pointer_cast<ColliderPoint>(AddCollider<ColliderPoint>("MouseBody"));
	collider_point->set_collision_group_tag("UI");

	return true;
}

MouseUI::MouseUI(MouseUI const& other) : UI(other)
{
}

MouseUI::MouseUI(MouseUI&& other) noexcept : UI(move(other))
{
}

void MouseUI::_Release()
{
}

void MouseUI::_Input(float time)
{
	UI::_Input(time);
}

void MouseUI::_Update(float time)
{
	UI::_Update(time);
}

void MouseUI::_LateUpdate(float time)
{
	UI::_LateUpdate(time);
}

void MouseUI::_Collision(float time)
{
	UI::_Collision(time);
}

void MouseUI::_Render(HDC device_context, float time)
{
	UI::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> MouseUI::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{ new MouseUI(*this), [](Object* p) {
		dynamic_cast<MouseUI*>(p)->_Release();
		delete dynamic_cast<MouseUI*>(p);
	} };
}