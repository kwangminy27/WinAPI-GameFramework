#include "parabola_bullet.h"
#include "../Resource/resource_manager.h"
#include "../Collision/collider_rect.h"
#include "../Collision/collider_sphere.h"

using namespace std;

float ParabolaBullet::start_angle() const
{
	return start_angle_;
}

void ParabolaBullet::set_start_angle(float angle)
{
	start_angle_ = angle;
}

ParabolaBullet::ParabolaBullet(ParabolaBullet const& other) : Bullet(other)
{
	start_angle_ = other.start_angle_;
}

ParabolaBullet::ParabolaBullet(ParabolaBullet&& other) noexcept : Bullet(move(other))
{
	start_angle_ = move(other.start_angle_);
}

void ParabolaBullet::_Release()
{
}

bool ParabolaBullet::_Initialize()
{
	set_size(10.f, 10.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(500.f);

	texture_ = ResourceManager::instance()->LoadTexture("Bullet", L"Bullet.bmp", "TexturePath");
	set_color_key(RGB(0, 248, 0));

	return true;
}

void ParabolaBullet::_Input(float time)
{
	Object::_Input(time);
}

void ParabolaBullet::_Update(float time)
{
	Object::_Update(time);

	angle_ += 120.f * time * 3.f;
	MoveByAngle(time * 3.f);
	if (angle_ >= start_angle_ + 120.f)
		set_activation(false);
}

void ParabolaBullet::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void ParabolaBullet::_Collision(float time)
{
	Object::_Collision(time);
}

void ParabolaBullet::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> ParabolaBullet::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>(new ParabolaBullet(*this), [](Object* p) {
		dynamic_cast<ParabolaBullet*>(p)->_Release();
		delete dynamic_cast<ParabolaBullet*>(p);
	});
}
