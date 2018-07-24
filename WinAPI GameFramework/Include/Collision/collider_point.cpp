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
		return _CollisionBetweenPointAndPoint(world_, dynamic_pointer_cast<ColliderPoint>(caching_dest)->world_);
	case COLLIDER::RECT:
		return _CollisionBetweenPointAndRect(world_, dynamic_pointer_cast<ColliderRect>(caching_dest)->world());
	case COLLIDER::CIRCLE:
		return _CollisionBetweenPointAndCircle(world_, dynamic_pointer_cast<ColliderCircle>(caching_dest)->world());
	case COLLIDER::PIXEL:
		return _CollisionBetweenPointAndPixel(world_, dynamic_pointer_cast<ColliderPixel>(caching_dest)->pixel_collider());
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
	auto object_position = object()->position();
	world_ = object_position + model_;
}

void ColliderPoint::_Render(HDC device_context, float time)
{
}

unique_ptr<Collider, function<void(Collider*)>> ColliderPoint::_Clone()
{
	return unique_ptr<Collider, function<void(Collider*)>>{ new ColliderPoint(*this), [](Collider* p) {
		dynamic_cast<ColliderPoint*>(p)->_Release();
		delete dynamic_cast<ColliderPoint*>(p);
	}};
}
