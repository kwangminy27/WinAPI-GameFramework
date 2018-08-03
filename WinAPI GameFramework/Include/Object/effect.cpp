#include "effect.h"

bool Effect::Initialize()
{
	type_ = OBJECT_TYPE::EFFECT;

	set_color_key(RGB(255, 0, 255));

	return true;
}

float Effect::life_time() const
{
	return life_time_;
}

float Effect::range() const
{
	return range_;
}

shared_ptr<Object> Effect::target() const
{
	return target_.lock();
}

void Effect::set_life_time(float time)
{
	life_time_ = time;
}

void Effect::set_range(float range)
{
	range_ = range;
}

void Effect::set_target(weak_ptr<Object> const& target)
{
	target_ = target;
}

Effect::Effect(Effect const& other) : Object(other)
{
	life_time_ = other.life_time_;
	range_ = other.range_;

	// target을 복제해 줄 필요가 있을까?
}

Effect::Effect(Effect&& other) noexcept : Object(move(other))
{
	life_time_ = move(other.life_time_);
	range_ = move(other.range_);
	target_ = move(other.target_);
}

void Effect::_Release()
{
}

void Effect::_Input(float time)
{
	Object::_Input(time);
}

void Effect::_Update(float time)
{
	Object::_Update(time);
}

void Effect::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void Effect::_Collision(float time)
{
	Object::_Collision(time);
}

void Effect::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> Effect::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{ new Effect(*this), [](Object* p) {
		dynamic_cast<Effect*>(p)->_Release();
		delete dynamic_cast<Effect*>(p);
	} };
}
