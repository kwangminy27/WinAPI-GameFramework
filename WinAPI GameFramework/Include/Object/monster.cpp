#include "monster.h"
#include "../math.h"
#include "../camera.h"
#include "object_manager.h"
#include "bullet.h"
#include "effect.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"
#include "../Collision/collider_rect.h"
#include "../Collision/collider_circle.h"

using namespace std;

float const kBarrelSize = 50.f;

bool Monster::Initialize()
{
	type_ = OBJECT_TYPE::MONSTER;

	set_size(50.f, 50.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(200.f);
	move_dir_ = 1.f;
	attack_range_ = 250.f;

	texture_ = ResourceManager::instance()->LoadTexture("Yasuo", L"Yasuo.bmp", "TexturePath");

	auto collider = dynamic_pointer_cast<ColliderRect>(AddCollider<ColliderRect>("MonsterBody"));
	collider->set_model({ 0.f, 0.f, 50.f, 50.f });
	collider->set_pivot({ 0.5f, 0.5f });
	collider->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		BeHit(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);

	auto collider2 = dynamic_pointer_cast<ColliderCircle>(AddCollider<ColliderCircle>("MonsterAttackRange"));
	collider2->set_model({ 0.f, 0.f, 250.f });

	collider2->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		set_target(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);

	collider2->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		release_target(src, dest, time);
	}, COLLISION_CALLBACK::LEAVE);

	return true;
}

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

void Monster::set_target(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
	if (src.expired() || dest.expired())
		return;

	auto caching_dest = dest.lock();
	auto caching_tag = caching_dest->tag();

	if (caching_tag == "PlayerBody" && target_.expired())
		target_ = caching_dest->object();
}

void Monster::release_target(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
	if (src.expired() || dest.expired())
		return;

	auto caching_dest = dest.lock();
	auto caching_tag = caching_dest->tag();

	if (caching_tag == "PlayerBody")
		target_.reset();
}

void Monster::BeHit(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
	if (src.expired() || dest.expired())
		return;

	auto caching_dest = dest.lock();
	auto caching_tag = caching_dest->tag();

	if (caching_tag == "BulletBody" || caching_tag == "GuidedBulletBody" || caching_tag == "ParabolaBulletBody" || caching_tag == "RotationBulletBody")
	{
		caching_dest->object()->set_activation(false);

		auto bomb_effect = dynamic_pointer_cast<Effect>(ObjectManager::instance()->CreateCloneObject("BombEffect", layer()));
		bomb_effect->set_position(caching_dest->intersect_position());
		bomb_effect->set_size(100.f, 200.f);
		bomb_effect->set_pivot(0.5f, 1.f);
		bomb_effect->set_target(weak_from_this());
		bomb_effect->AddAnimationClip("Bomb");
	}
}

Monster::Monster(Monster const& other) : Character(other)
{
	move_dir_ = other.move_dir_;
	fire_time_ = other.fire_time_;
	attack_range_ = other.attack_range_;
	target_ = other.target_;
}

Monster::Monster(Monster&& other) noexcept : Character(move(other))
{
	move_dir_ = move(other.move_dir_);
	fire_time_ = move(other.fire_time_);
	attack_range_ = move(other.attack_range_);
	target_ = move(other.target_);
}

void Monster::_Release()
{
}

void Monster::_Input(float time)
{
	Character::_Input(time);
}

void Monster::_Update(float time)
{
	Character::_Update(time);

	/*Move(0.f, move_speed_ * move_dir_, time);
	if (position_.y - pivot_.y * size_.y < 0.f)
	{
		move_dir_ = 1.f;
		position_.y = pivot_.y * size_.y;
	}
	else if (position_.y + (1.f - pivot_.y) * size_.y > static_cast<float>(RESOLUTION::HEIGHT))
	{
		move_dir_ = -1.f;
		position_.y = static_cast<float>(RESOLUTION::HEIGHT) + (pivot_.y - 1.f) * size_.y;
	}*/

	if(target())
		fire_time_ += time;

	if (fire_time_ > 1.f)
	{
		auto bullet = dynamic_pointer_cast<Bullet>(ObjectManager::instance()->CreateCloneObject("Bullet", layer()));

		XY barrel_end{ position_.x + cos(Math::DegreeToRadian(angle_)) * kBarrelSize, position_.y + sin(Math::DegreeToRadian(angle_)) * kBarrelSize };

		bullet->set_position(barrel_end);
		bullet->set_angle(Math::GetAngle(position_, target()->position()));

		auto collider_circle = dynamic_pointer_cast<ColliderCircle>(bullet->AddCollider<ColliderCircle>("MonsterBulletBody"));
		collider_circle->set_model({ 0.f, 0.f, 10.f });

		fire_time_ -= 1.f;
	}
}

void Monster::_LateUpdate(float time)
{
	Character::_LateUpdate(time);
}

void Monster::_Collision(float time)
{
	Character::_Collision(time);
}

void Monster::_Render(HDC device_context, float time)
{
	Character::_Render(device_context, time);

	if (target())
		angle_ = Math::GetAngle(position_, target_.lock()->position());

	auto camera_position = Camera::instance()->world();
	auto position_on_the_camera_coordinate_system = position_ - camera_position;

	MoveToEx(device_context, static_cast<int>(position_on_the_camera_coordinate_system.x), static_cast<int>(position_on_the_camera_coordinate_system.y), nullptr);
	XY barrel_end{ position_on_the_camera_coordinate_system.x + cos(Math::DegreeToRadian(angle_)) * kBarrelSize, position_on_the_camera_coordinate_system.y + sin(Math::DegreeToRadian(angle_)) * kBarrelSize };
	LineTo(device_context, static_cast<int>(barrel_end.x), static_cast<int>(barrel_end.y));
}

unique_ptr<Object, function<void(Object*)>> Monster::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new Monster(*this), [](Object* p) {
		dynamic_cast<Monster*>(p)->_Release();
		delete dynamic_cast<Monster*>(p);
	}};
}
