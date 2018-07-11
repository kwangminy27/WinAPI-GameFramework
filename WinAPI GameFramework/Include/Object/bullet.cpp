#include "bullet.h"

using namespace std;

void Bullet::set_move_speed(float move_speed)
{
	move_speed_ = move_speed;
}

void Bullet::set_dir(XY dir)
{
	dir_ = dir;
}

Bullet::Bullet(Bullet const& other) : Object(other)
{
	move_speed_ = other.move_speed_;
}

void Bullet::_Release()
{
}

bool Bullet::_Initialize()
{
	set_move_speed(500.f);
	set_size(50.f, 50.f);
	set_pivot(0.5f, 0.5f);
	set_dir({ 1.f, 0.f });

	return true;
}

void Bullet::_Input(float time)
{
}

void Bullet::_Update(float time)
{
	//Move()
}

void Bullet::_LateUpdate(float time)
{
}

void Bullet::_Collision(float time)
{
}

void Bullet::_Render(HDC device_context, float time)
{
	float left{ position_.x - size_.x * pivot_.x };
	float top{ position_.y - size_.y * pivot_.y };
	Rectangle(device_context, static_cast<int>(left), static_cast<int>(top), static_cast<int>(left + size_.x), static_cast<int>(top + size_.y));
}

unique_ptr<Object, function<void(Object*)>> Bullet::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>(new Bullet(*this), [](Object* p) {
		dynamic_cast<Bullet*>(p)->_Release();
		delete dynamic_cast<Bullet*>(p);
	});
}
