#include "../camera.h"
#include "../Object/object.h"
#include "collider_point.h"
#include "collider_rect.h"
#include "collider_circle.h"
#include "collider_pixel.h"

using namespace std;

RECT_INFO const& ColliderRect::world() const
{
	return world_;
}

void ColliderRect::set_model(RECT_INFO const& model)
{
	model_ = model;

	size_.x = model.r - model.l;
	size_.y = model.b - model.t;
}

bool ColliderRect::Collision(weak_ptr<Collider> const& dest)
{
	if (dest.expired())
		return false;

	auto caching_dest = dest.lock();

	switch (caching_dest->collider_type())
	{
	case COLLIDER::POINT:
		return _CollisionBetweenPointAndRect(dynamic_pointer_cast<ColliderPoint>(caching_dest)->world(), world_);
	case COLLIDER::RECT:
		return _CollisionBetweenRectAndRect(world_, dynamic_pointer_cast<ColliderRect>(caching_dest)->world_);
	case COLLIDER::CIRCLE:
		return _CollisionBetweenRectAndCircle(world_, dynamic_pointer_cast<ColliderCircle>(caching_dest)->world());
	case COLLIDER::PIXEL:
		break;
	}

	return false;
}

ColliderRect::ColliderRect(ColliderRect const& other) : Collider(other)
{
	model_ = other.model_;
	world_ = other.world_;
}

ColliderRect::ColliderRect(ColliderRect&& other) noexcept : Collider(move(other))
{
	model_ = move(other.model_);
	world_ = move(other.world_);
}

void ColliderRect::_Release()
{
	Collider::_Release();
}

bool ColliderRect::_Initialize()
{
	collider_type_ = COLLIDER::RECT;
	
	return true;
}

void ColliderRect::_Update(float time)
{
	size_.x = model_.r - model_.l;
	size_.y = model_.b - model_.t;

	if(!object_.expired())
	{
		XY object_position = object()->position();
		world_.l = object_position.x + model_.l - pivot_.x * size_.x;
		world_.t = object_position.y + model_.t - pivot_.y * size_.y;
		world_.r = world_.l + size_.x;
		world_.b = world_.t + size_.y;
	}
}

void ColliderRect::_Render(HDC device_context, float time)
{
#ifdef _DEBUG
	if (collided_collider_list_.empty())
		brush_ = Collider::green_brush_;
	else
		brush_ = Collider::red_brush_;

	auto camera_position = Camera::instance()->world();

	auto position_on_the_camera_coordinate_system = world_;
	position_on_the_camera_coordinate_system.l -= camera_position.x;
	position_on_the_camera_coordinate_system.r -= camera_position.x;
	position_on_the_camera_coordinate_system.t -= camera_position.y;
	position_on_the_camera_coordinate_system.b -= camera_position.y;

	RECT rc{ static_cast<long>(position_on_the_camera_coordinate_system.l), static_cast<long>(position_on_the_camera_coordinate_system.t), static_cast<long>(position_on_the_camera_coordinate_system.r), static_cast<long>(position_on_the_camera_coordinate_system.b) };
	FrameRect(device_context, &rc, brush_);
#endif
}

unique_ptr<Collider, function<void(Collider*)>> ColliderRect::_Clone()
{
	return unique_ptr<Collider, function<void(Collider*)>>{new ColliderRect, [](Collider* p) {
		dynamic_cast<ColliderRect*>(p)->_Release();
		delete dynamic_cast<ColliderRect*>(p);
	}};
}
