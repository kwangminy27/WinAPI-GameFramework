#include "../input.h"
#include "../math.h"
#include "../camera.h"
#include "../Object/object.h"
#include "collider_point.h"
#include "collider_rect.h"
#include "collider_circle.h"
#include "collider_pixel.h"

using namespace std;

XY const& ColliderPoint::world() const
{
	return world_;
}

void ColliderPoint::set_model(XY const& model)
{
	model_ = model;
}

bool ColliderPoint::Collision(weak_ptr<Collider> const& dest)
{
	if (dest.expired())
		return false;

	auto caching_dest = dest.lock();

	switch (caching_dest->collider_type())
	{
	case COLLIDER::POINT:
		return _CollisionBetweenPointAndPoint(world(), dynamic_pointer_cast<ColliderPoint>(caching_dest)->world());
	case COLLIDER::RECT:
		return _CollisionBetweenPointAndRect(world(), dynamic_pointer_cast<ColliderRect>(caching_dest)->world());
	case COLLIDER::CIRCLE:
		return _CollisionBetweenPointAndCircle(world(), dynamic_pointer_cast<ColliderCircle>(caching_dest)->world());
	case COLLIDER::PIXEL:
		return _CollisionBetweenPointAndPixel(world(), dynamic_pointer_cast<ColliderPixel>(caching_dest)->pixel_collider());
	}

	return false;
}

ColliderPoint::ColliderPoint(ColliderPoint const& other) : Collider(other)
{
	model_ = other.model_;
	world_ = other.world_;
}

ColliderPoint::ColliderPoint(ColliderPoint&& other) noexcept : Collider(move(other))
{
	model_ = move(other.model_);
	world_ = move(other.world_);
}

void ColliderPoint::_Release()
{
}

bool ColliderPoint::_Initialize()
{
	collider_type_ = COLLIDER::POINT;

	return true;
}

void ColliderPoint::_Update(float time)
{
	if (object_.expired())
		return;

	auto caching_object = object();
	auto object_position = caching_object->position();

	if (caching_object->type() == OBJECT_TYPE::UI)
		object_position += Camera::instance()->world();

	world_.x = model_.x + object_position.x;
	world_.y = model_.y + object_position.y;
}

void ColliderPoint::_Render(HDC device_context, float time)
{
#ifdef _DEBUG
	if (object_.expired())
		return;

	if (collided_collider_list_.empty())
		pen_ = Collider::green_pen_;
	else
		pen_ = Collider::red_pen_;

	auto camera_world_position = Camera::instance()->world();

	old_pen_ = static_cast<HPEN>(SelectObject(device_context, pen_));
	XY position_on_the_camera_coordinate_system = world_ - camera_world_position;
	MoveToEx(device_context, static_cast<int>(position_on_the_camera_coordinate_system.x + 2), static_cast<int>(position_on_the_camera_coordinate_system.y), nullptr);
	for (size_t i = 30; i <= 360; i += 30)
	{
		position_on_the_camera_coordinate_system.x = world_.x - camera_world_position.x + cosf(Math::DegreeToRadian(static_cast<float>(i))) * 2;
		position_on_the_camera_coordinate_system.y = world_.y - camera_world_position.y + sinf(Math::DegreeToRadian(static_cast<float>(i))) * 2;

		LineTo(device_context, static_cast<int>(position_on_the_camera_coordinate_system.x), static_cast<int>(position_on_the_camera_coordinate_system.y));
	}
	SelectObject(device_context, old_pen_);
#endif
}

unique_ptr<Collider, function<void(Collider*)>> ColliderPoint::_Clone()
{
	return unique_ptr<Collider, function<void(Collider*)>>{ new ColliderPoint(*this), [](Collider* p) {
		dynamic_cast<ColliderPoint*>(p)->_Release();
		delete dynamic_cast<ColliderPoint*>(p);
	}};
}
