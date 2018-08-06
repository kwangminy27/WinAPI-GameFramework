#include "../camera.h"
#include "bar.h"
#include "../Resource/texture.h"
#include "../Collision/collider.h"
#include "../animation.h"

using namespace std;

bool Bar::Initialize()
{
	return true;
}

void Bar::set_range(XY const& range)
{
	range_ = range;
}

void Bar::set_value(float value)
{
	value_ = value;

	value_ = clamp(value_, range_.x, range_.y);
}

void Bar::set_cutting_direction(BAR_CUTTING_DIRECTION direction)
{
	cutting_direction_ = direction;
}

void Bar::AddValue(float value)
{
	value_ += value;

	value_ = clamp(value_, range_.x, range_.y);
}

Bar::Bar(Bar const& other) : Object(other)
{
	range_ = other.range_;
	value_ = other.value_;
	cutting_direction_ = other.cutting_direction_;
}

Bar::Bar(Bar&& other) noexcept : Object(move(other))
{
	range_ = move(other.range_);
	value_ = move(other.value_);
	cutting_direction_ = move(other.cutting_direction_);
}

void Bar::_Release()
{
}

void Bar::_Input(float time)
{
	Object::_Input(time);
}

void Bar::_Update(float time)
{
	Object::_Update(time);
}

void Bar::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void Bar::_Collision(float time)
{
	Object::_Collision(time);
}

void Bar::_Render(HDC device_context, float time)
{
	if (texture_.expired())
		return;

	auto caching_texture = texture_.lock();
	auto camera_position = Camera::instance()->world();
	
	switch (cutting_direction_)
	{
	case BAR_CUTTING_DIRECTION::LEFT:
		pivot_ = { 0.f, 0.f };
		break;
	case BAR_CUTTING_DIRECTION::RIGHT:
		pivot_ = { 1.f, 0.f };
		break;
	case BAR_CUTTING_DIRECTION::UP:
		pivot_ = { 0.f, 0.f };
		break;
	case BAR_CUTTING_DIRECTION::DOWN:
		pivot_ = { 0.f, 1.f };
		break;
	}

	int left = static_cast<int>(position_.x + size_.x * pivot_.x - Camera::instance()->world().x);
	int top = static_cast<int>(position_.y + size_.y * pivot_.y - Camera::instance()->world().y);
	int width = static_cast<int>(size_.x);
	int height = static_cast<int>(size_.y);

	float t = value_ / (range_.y - range_.x);

	switch (cutting_direction_)
	{
	case BAR_CUTTING_DIRECTION::LEFT:
		width = static_cast<int>(size_.x * t);
		break;
	case BAR_CUTTING_DIRECTION::RIGHT:
		width = static_cast<int>(size_.x * t);
		left -= width;
		break;
	case BAR_CUTTING_DIRECTION::UP:
		height = static_cast<int>(size_.y * t);
		break;
	case BAR_CUTTING_DIRECTION::DOWN:
		height = static_cast<int>(size_.y * t);
		top -= height;
		break;
	}

	if (is_color_key_)
	{
		if (animation_)
		{
			width = static_cast<int>(animation_->GetFrameWidth());
			height = static_cast<int>(animation_->GetFrameHeight());

			int frame_left = static_cast<int>(animation_->frame_x() * width);
			int frame_top = static_cast<int>(animation_->frame_y() * height);

			TransparentBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), frame_left, frame_top, width, height, color_key_);
		}
		else
			TransparentBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), 0, 0, caching_texture->width(), caching_texture->height(), color_key_);
	}
	else
		BitBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), 0, 0, SRCCOPY);

	for (auto const& collider : collider_collection_)
	{
		if (collider->enablement())
			collider->Render(device_context, time);
	}
}

unique_ptr<Object, function<void(Object*)>> Bar::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new Bar(*this), [](Object* p) {
		dynamic_cast<Bar*>(p)->_Release();
		delete dynamic_cast<Bar*>(p);
	}};
}
