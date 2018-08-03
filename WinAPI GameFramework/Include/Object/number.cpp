#include "../camera.h"
#include "number.h"
#include "../Resource/texture.h"
#include "../Collision/collider.h"
#include "../animation.h"

using namespace std;

bool Number::Initialize()
{
	return true;
}

void Number::set_number(int number)
{
	number_ = number;
}

void Number::AddNumber(int value)
{
	number_ += value;
}

void Number::set_number_piece_size(XY const& size)
{
	number_piece_size_ = size;
}

void Number::set_offset(XY const& offset)
{
	offset_ = offset;
}

Number::Number(Number const& other) : Object(other)
{
	number_ = other.number_;
}

Number::Number(Number&& other) noexcept : Object(move(other))
{
	number_ = move(other.number_);
}

void Number::_Release()
{
}

void Number::_Input(float time)
{
	Object::_Input(time);
}

void Number::_Update(float time)
{
	Object::_Update(time);
}

void Number::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void Number::_Collision(float time)
{
	Object::_Collision(time);
}

void Number::_Render(HDC device_context, float time)
{
	if (texture_.expired())
		return;

	auto caching_texture = texture_.lock();

	int number = number_;

	number_slot_.clear();
	while (number > 0)
	{
		int result = number % 10;
		number /= 10;
		number_slot_.push_back(result);
	}

	XY position_on_the_world_coordinate_system = position_;
	XY position_on_the_camera_coordinate_system = position_on_the_world_coordinate_system - Camera::instance()->world();

	int left = static_cast<int>(position_on_the_camera_coordinate_system.x - size_.x * pivot_.x);
	int top = static_cast<int>(position_on_the_camera_coordinate_system.y - size_.y * pivot_.y);
	int width = static_cast<int>(number_piece_size_.x);
	int height = static_cast<int>(number_piece_size_.y);

	int rendering_position_x = left + static_cast<int>(size_.x);
	int frame_left{};
	int frame_top{};
	for (size_t i = 0; i < number_slot_.size(); ++i)
	{
		rendering_position_x -= static_cast<int>(number_piece_size_.x);

		frame_left = number_slot_.at(i) * static_cast<int>(number_piece_size_.x);

		if (is_color_key_)
		{
			if (animation_)
			{
				width = static_cast<int>(animation_->GetFrameWidth());
				height = static_cast<int>(animation_->GetFrameHeight());

				frame_left = static_cast<int>(animation_->frame_x() * width);
				frame_top = static_cast<int>(animation_->frame_y() * height);

				TransparentBlt(device_context, rendering_position_x, top, width, height, caching_texture->memory_device_context(), frame_left, frame_top, width, height, color_key_);
			}
			else
				TransparentBlt(device_context, rendering_position_x, top, width, height, caching_texture->memory_device_context(), frame_left, frame_top, width, height, color_key_);
		}
		else
			BitBlt(device_context, rendering_position_x, top, width, height, caching_texture->memory_device_context(), frame_left, frame_top, SRCCOPY);
	}

	for (auto const& collider : collider_collection_)
	{
		if (collider->enablement())
			collider->Render(device_context, time);
	}
}

unique_ptr<Object, function<void(Object*)>> Number::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new Number(*this), [](Object* p) {
		dynamic_cast<Number*>(p)->_Release();
		delete dynamic_cast<Number*>(p);
	}};
}