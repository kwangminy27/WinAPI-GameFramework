#include "rotation_bullet.h"
#include "../Resource/resource_manager.h"
#include "../math.h"

using namespace std;

XY RotationBullet::rotation_center() const
{
	return rotation_center_;
}

float RotationBullet::rotation_range() const
{
	return rotation_range_;
}

float RotationBullet::rotation_angle() const
{
	return rotation_angle_;
}

void RotationBullet::set_rotation_center(XY const& rotation_centor)
{
	rotation_center_ = rotation_centor;
}

void RotationBullet::set_rotation_range(float rotation_range)
{
	rotation_range_ = rotation_range;
}

void RotationBullet::set_rotation_angle(float rotation_angle)
{
	rotation_angle_ = rotation_angle;
}

RotationBullet::RotationBullet(RotationBullet const& other) : Bullet(other)
{
	rotation_center_ = other.rotation_center_;
	rotation_range_ = other.rotation_range_;
	rotation_angle_ = other.rotation_angle_;
}

void RotationBullet::_Release()
{
}

bool RotationBullet::_Initialize()
{
	set_size(10.f, 10.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(500.f);
	set_rotation_speed(1080.f);
	set_range(1000.f);
	set_rotation_range(50.f);

	texture_ = ResourceManager::instance()->LoadTexture("Bullet"s, L"Bullet.bmp"s, "TexturePath"s);
	set_color_key(RGB(0, 248, 0));

	return true;
}

void RotationBullet::_Input(float time)
{
}

void RotationBullet::_Update(float time)
{
	range_ -= move_speed_ * time;
	
	rotation_center_.x += cos(Math::DegreeToRadian(angle_)) * move_speed_ * time;
	rotation_center_.y += sin(Math::DegreeToRadian(angle_)) * move_speed_ * time;

	rotation_angle_ += rotation_speed_* time;

	position_.x = rotation_center_.x + cos(Math::DegreeToRadian(rotation_angle_)) * rotation_range_;
	position_.y = rotation_center_.y + sin(Math::DegreeToRadian(rotation_angle_)) * rotation_range_;

	if (range_ <= 0)
		set_activation(false);
}

void RotationBullet::_LateUpdate(float time)
{
}

void RotationBullet::_Collision(float time)
{
}

void RotationBullet::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> RotationBullet::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new RotationBullet(*this), [](Object* p) {
		dynamic_cast<RotationBullet*>(p)->_Release();
		delete dynamic_cast<RotationBullet*>(p);
	}};
}