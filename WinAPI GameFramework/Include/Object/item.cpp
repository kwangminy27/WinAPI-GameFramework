#include "item.h"
#include "../Resource/resource_manager.h"

using namespace std;

float Item::life_time() const
{
	return life_time_;
}

void Item::set_life_time(float time)
{
	life_time_ = time;
}

Item::Item(Item const& other) : Object(other)
{
	life_time_ = other.life_time_;
}

Item::Item(Item && other) noexcept : Object(other)
{
	life_time_ = move(other.life_time_);
}

void Item::_Release()
{
}

bool Item::_Initialize()
{
	set_size(10.f, 10.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(1000.f);
	set_life_time(1.f);

	texture_ = ResourceManager::instance()->FindTexture("StarBack"s);

	return true;
}

void Item::_Input(float time)
{
	Object::_Input(time);
}

void Item::_Update(float time)
{
	Object::_Update(time);

	life_time_ -= time;

	if (position_.x < 0.f)
	{
		set_angle(angle_ + 90.f);
		position_.x = 0.f;
	}

	if (position_.x > static_cast<float>(RESOLUTION::WIDTH))
	{
		set_angle(angle_ + 90.f);
		position_.x = static_cast<float>(RESOLUTION::WIDTH);
	}

	if (position_.y < 0.f)
	{
		set_angle(angle_ + 90.f);
		position_.y = 0.f;
	}

	if (position_.y > static_cast<float>(RESOLUTION::HEIGHT))
	{
		set_angle(angle_ + 90.f);
		position_.y = static_cast<float>(RESOLUTION::HEIGHT);
	}

	MoveByAngle(time);

	if (life_time_ <= 0.f)
		set_activation(false);
}

void Item::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void Item::_Collision(float time)
{
	Object::_Collision(time);
}

void Item::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> Item::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new Item(*this), [](Object* p) {
		dynamic_cast<Item*>(p)->_Release();
		delete dynamic_cast<Item*>(p);
	}};
}
