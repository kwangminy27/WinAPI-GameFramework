#include "bullet.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"
#include "../Collision/collider_rect.h"
#include "../Collision/collider_sphere.h"

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

Bullet::Bullet(Bullet&& other) noexcept : Object(other)
{
	range_ = move(other.range_);
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

	//auto collider = dynamic_pointer_cast<ColliderRect>(AddCollider<ColliderRect>("BulletBody"s));
	//collider->set_model({ 0.f, 0.f, 10.f, 10.f });
	//collider->set_pivot({ 0.5f, 0.5f });

	auto collider_sphere = dynamic_pointer_cast<ColliderSphere>(AddCollider<ColliderSphere>("BulletBody"s));
	collider_sphere->set_model({ 0.f, 0.f, 5.f });

	return true;
}

void Bullet::_Input(float time)
{
	Object::_Input(time);
}

void Bullet::_Update(float time)
{
	Object::_Update(time);

	range_ -= move_ * move_speed_ * time;
	MoveByAngle(time);
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
