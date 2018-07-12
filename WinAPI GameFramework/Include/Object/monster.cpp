#include "monster.h"
#include "../math.h"
#include "object_manager.h"
#include "bullet.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"

using namespace std;

float Monster::move_dir() const
{
	return move_dir_;
}

float Monster::fire_time() const
{
	return fire_time_;
}

float Monster::attack_range() const
{
	return attack_range_;
}

shared_ptr<Object> Monster::target() const
{
	return target_.lock();
}

void Monster::set_move_dir(float move_dir)
{
	move_dir_ = move_dir;
}

void Monster::set_fire_time(float fire_time)
{
	fire_time_ = fire_time;
}

void Monster::set_attack_range(float attack_range)
{
	attack_range_ = attack_range;
}

void Monster::set_target(weak_ptr<Object> const& target)
{
	target_ = target;
}

Monster::Monster(Monster const& other) : Character(other)
{
	move_dir_ = other.move_dir_;
	fire_time_ = other.fire_time_;
	attack_range_ = other.attack_range_;
	target_ = other.target_;
}

void Monster::_Release()
{
}

bool Monster::_Initialize()
{
	set_position(700.f, 100.f);
	set_size(100.f, 100.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(700.f);
	move_dir_ = 1.f;
	attack_range_ = 500.f;

	texture_ = ResourceManager::instance()->LoadTexture("Yasuo"s, L"Yasuo.bmp"s, "TexturePath"s);

	return true;
}

void Monster::_Input(float time)
{
}

void Monster::_Update(float time)
{
	Move(0.f, move_speed_ * move_dir_, time);
	if (position_.y - pivot_.y * size_.y < 0.f)
	{
		move_dir_ = 1.f;
		position_.y = pivot_.y * size_.y;
	}
	else if (position_.y + (1.f - pivot_.y) * size_.y > static_cast<float>(RESOLUTION::HEIGHT))
	{
		move_dir_ = -1.f;
		position_.y = static_cast<float>(RESOLUTION::HEIGHT) + (pivot_.y - 1.f) * size_.y;
	}

	if(Math::GetDistance(position_, target()->position()) <= attack_range_)
		fire_time_ += time;

	if (fire_time_ > 1.f)
	{
		weak_ptr<Object> bullet = ObjectManager::instance()->CreateCloneObject("Bullet"s, layer());
		bullet.lock()->set_position(position_ - XY{ 75.f, 0.f });
		dynamic_cast<Bullet*>(bullet.lock().get())->set_move_dir({ -1.f, 0.f });
		fire_time_ -= 1.f;
	}
}

void Monster::_LateUpdate(float time)
{
}

void Monster::_Collision(float time)
{
}

void Monster::_Render(HDC device_context, float time)
{
	Character::_Render(device_context, time);
}

unique_ptr<Object,function<void(Object*)>> Monster::_Clone()
{
	return std::unique_ptr<Object, std::function<void(Object*)>>();
}
