#include "bullet.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"

using namespace std;

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

Bullet::Bullet(Bullet const& other) : Object(other)
{
	range_ = other.range_;
}

void Bullet::_Release()
{
}

bool Bullet::_Initialize()
{
	set_size(10.f, 10.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(500.f);
	set_range(1000.f);

	texture_ = ResourceManager::instance()->LoadTexture("Bullet"s, L"Bullet.bmp"s, "TexturePath"s);
	set_color_key(RGB(0, 248, 0));

	return true;
}

void Bullet::_Input(float time)
{
}

void Bullet::_Update(float time)
{
	range_ -= move_ * move_speed_ * time;
	MoveByAngle(time);
	if (range_ <= 0.f)
		set_activation(false);
}

void Bullet::_LateUpdate(float time)
{
}

void Bullet::_Collision(float time)
{
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
