#include "ui.h"
#include "../Resource/texture.h"
#include "../Collision/collider.h"
#include "../animation.h"

using namespace std;

void UI::set_offset(XY const& offset)
{
	offset_ = offset;
}

UI::UI(UI const& other) : Object(other)
{
	offset_ = other.offset_;
}

UI::UI(UI&& other) noexcept : Object(move(other))
{
	offset_ = move(other.offset_);
}

void UI::_Release()
{
}

bool UI::_Initialize()
{
	if (Object::_Initialize())
		return false;

	type_ = OBJECT_TYPE::UI;

	return true;
}

void UI::_Input(float time)
{
	Object::_Input(time);
}

void UI::_Update(float time)
{
	Object::_Update(time);
}

void UI::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void UI::_Collision(float time)
{
	Object::_Collision(time);
}

void UI::_Render(HDC device_context, float time)
{
	if (texture_.expired())
		return;

	auto caching_texture = texture_.lock();

	int left = static_cast<int>(position_.x - size_.x * pivot_.x);
	int top = static_cast<int>(position_.y - size_.y * pivot_.y);
	int width = static_cast<int>(size_.x);
	int height = static_cast<int>(size_.y);

	if (is_color_key_)
	{
		if (animation_)
		{
			width = static_cast<int>(animation_->GetFrameWidth());
			height = static_cast<int>(animation_->GetFrameHeight());

			int frame_left = static_cast<int>(animation_->frame_x_ * width);
			int frame_top = static_cast<int>(animation_->frame_y_ * height);

			TransparentBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), frame_left + static_cast<int>(offset_.x), frame_top + static_cast<int>(offset_.y), width, height, color_key_);
		}
		else
			TransparentBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), static_cast<int>(offset_.x), static_cast<int>(offset_.y), caching_texture->width(), caching_texture->height(), color_key_);
	}
	else
		BitBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), static_cast<int>(offset_.x), static_cast<int>(offset_.y), SRCCOPY);

	for (auto const& collider : collider_collection_)
	{
		if (collider->enablement())
			collider->_Render(device_context, time);
	}
}