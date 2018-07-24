#include "../math.h"
#include "../camera.h"
#include "../Object/object.h"
#include "collider_point.h"
#include "collider_rect.h"
#include "collider_circle.h"
#include "collider_pixel.h"

using namespace std;

CIRCLE_INFO const& ColliderCircle::world() const
{
	return world_;
}

void ColliderCircle::set_model(CIRCLE_INFO const& model)
{
	model_.center = model.center;
	model_.radius = model.radius;
}

bool ColliderCircle::Collision(weak_ptr<Collider> const& dest)
{
	if (dest.expired())
		return false;

	auto caching_dest = dest.lock();

	switch (caching_dest->collider_type())
	{
	case COLLIDER::POINT:
		return _CollisionBetweenPointAndCircle(dynamic_pointer_cast<ColliderPoint>(caching_dest)->world(), world_);
	case COLLIDER::RECT:
		return _CollisionBetweenRectAndCircle(dynamic_pointer_cast<ColliderRect>(caching_dest)->world(), world_);
	case COLLIDER::CIRCLE:
		return _CollisionBetweenCircleAndCircle(world_, dynamic_pointer_cast<ColliderCircle>(caching_dest)->world_);
	case COLLIDER::PIXEL:
		break;
	}

	return false;
}

ColliderCircle::ColliderCircle(ColliderCircle const& other) : Collider(other)
{
	model_ = other.model_;
	world_ = other.world_;
}

ColliderCircle::ColliderCircle(ColliderCircle&& other) noexcept : Collider(move(other))
{
	model_ = move(other.model_);
	world_ = move(other.world_);
}

void ColliderCircle::_Release()
{
	Collider::_Release();
}

bool ColliderCircle::_Initialize()
{
	collider_type_ = COLLIDER::CIRCLE;

	return true;
}

void ColliderCircle::_Update(float time)
{
	if (!object_.expired())
	{
		world_.radius = model_.radius;

		auto object_position = object()->position();
		world_.center.x = object_position.x + model_.center.x + (model_.radius * pivot_.x);
		world_.center.y = object_position.y + model_.center.y + (model_.radius * pivot_.y);
	}
}

void ColliderCircle::_Render(HDC device_context, float time)
{
#ifdef _DEBUG
	if (collided_collider_list_.empty())
		pen_ = Collider::green_pen_;
	else
		pen_ = Collider::red_pen_;

	if (!object_.expired())
	{
		auto camera_world_position = Camera::instance()->world();

		old_pen_ = static_cast<HPEN>(SelectObject(device_context, pen_));
		XY position_on_the_camera_coordinate_system = world_.center - camera_world_position;
		MoveToEx(device_context, static_cast<int>(position_on_the_camera_coordinate_system.x + world_.radius), static_cast<int>(position_on_the_camera_coordinate_system.y), nullptr);
		for (size_t i = 30; i <= 360; i += 30)
		{
			position_on_the_camera_coordinate_system.x = world_.center.x - camera_world_position.x + cosf(Math::DegreeToRadian(static_cast<float>(i))) * world_.radius;
			position_on_the_camera_coordinate_system.y = world_.center.y - camera_world_position.y + sinf(Math::DegreeToRadian(static_cast<float>(i))) * world_.radius;

			LineTo(device_context, static_cast<int>(position_on_the_camera_coordinate_system.x), static_cast<int>(position_on_the_camera_coordinate_system.y));
		}
		SelectObject(device_context, old_pen_);
	}
#endif
}

unique_ptr<Collider, function<void(Collider*)>> ColliderCircle::_Clone()
{
	return unique_ptr<Collider, function<void(Collider*)>>{new ColliderCircle(*this), [](Collider* p) {
		dynamic_cast<ColliderCircle*>(p)->_Release();
		delete dynamic_cast<ColliderCircle*>(p);
	}};
}