#include "camera.h"
#include "Object/object.h"

using namespace std;

bool Camera::Initialize()
{
	set_view_size({ static_cast<float>(RESOLUTION::WIDTH), static_cast<float>(RESOLUTION::HEIGHT) });

	return true;
}

void Camera::Update(float time)
{
	if (target_.expired())
		return;

	XY target_position = target_.lock()->position();
	world_ = target_position - view_size_ * pivot_;

	world_.x = clamp(world_.x, 0.f, map_size_.x - view_size_.x - 1.f);
	world_.y = clamp(world_.y, 0.f, map_size_.y - view_size_.y - 1.f);
}

void Camera::Move(float x, float y, float time)
{
	world_.x += x * time;
	world_.y += y * time;

	world_.x = clamp(world_.x, 0.f, map_size_.x - view_size_.x - 1.f);
	world_.y = clamp(world_.y, 0.f, map_size_.y - view_size_.y - 1.f);
}

XY const& Camera::world() const
{
	return world_;
}

XY const& Camera::view_size() const
{
	return view_size_;
}

XY const& Camera::pivot() const
{
	return pivot_;
}

XY const& Camera::map_size() const
{
	return map_size_;
}

shared_ptr<Object> Camera::target() const
{
	return target_.lock();
}

void Camera::set_view_size(XY const& xy)
{
	view_size_ = xy;
}

void Camera::set_pivot(XY const& xy)
{
	pivot_ = xy;
}

void Camera::set_map_size(XY const& xy)
{
	map_size_ = xy;
}

void Camera::set_target(weak_ptr<Object> const& object)
{
	if (object.expired())
		return;

	target_ = object;
}

void Camera::_Release()
{
}