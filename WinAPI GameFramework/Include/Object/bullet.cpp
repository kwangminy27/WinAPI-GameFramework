#include "bullet.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"
#include "../Collision/collider_rect.h"
#include "../Collision/collider_circle.h"

using namespace std;

bool Bullet::Initialize()
{
	type_ = OBJECT_TYPE::BULLET;

	set_size(20.f, 20.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(500.f);
	set_range(1000.f);

	texture_ = ResourceManager::instance()->LoadTexture("Bullet", L"Bullet.bmp", "TexturePath");
	set_color_key(RGB(0, 248, 0));

	return true;
}

void Bullet::set_range(float range)
{
	range_ = range;
}

void Bullet::stop()
{
	move_ = false;
}

void Bullet::start()
{
	move_ = true;
}

void Bullet::set_growth_speed(float speed)
{
	growth_speed_ = speed;
}

Bullet::Bullet(Bullet const& other) : Object(other)
{
	range_ = other.range_;
	growth_speed_ = other.growth_speed_;
}

Bullet::Bullet(Bullet&& other) noexcept : Object(move(other))
{
	range_ = move(other.range_);
	growth_speed_ = move(other.growth_speed_);
}

void Bullet::_Release()
{
}

void Bullet::_Input(float time)
{
	Object::_Input(time);
}

void Bullet::_Update(float time)
{
	Object::_Update(time);

	for (auto& collider : collider_collection_)
		dynamic_pointer_cast<ColliderCircle>(collider)->set_model({ 0.f, 0.f, size_.x / 2.f });

	MoveByAngle(time);

	range_ -= move_ * move_speed_ * time;
	if (range_ <= 0.f)
		set_activation(false);
}

void Bullet::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void Bullet::_Collision(float time)
{
	Object::_Collision(time);
}

void Bullet::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> Bullet::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new Bullet(*this), [](Object* p) {
		dynamic_cast<Bullet*>(p)->_Release();
		delete dynamic_cast<Bullet*>(p);
	}};
}
