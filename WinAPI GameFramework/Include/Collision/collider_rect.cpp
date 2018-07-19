#include "collider_rect.h"
#include "../Object/object.h"

using namespace std;

LTRB ColliderRect::world() const
{
	return world_;
}

void ColliderRect::set_model(LTRB const& ltrb)
{
	model_ = ltrb;

	size_.x = ltrb.r - ltrb.l;
	size_.y = ltrb.b - ltrb.t;
}

bool ColliderRect::Collision(shared_ptr<Collider> const& dest)
{
	if (!dest)
		return false;

	switch (dest->collider_type())
	{
	case COLLIDER::RECT:
		return CollisionBetweenRectAndRect(world_, dynamic_pointer_cast<ColliderRect>(dest)->world_);
	}

	return false;
}

ColliderRect::ColliderRect(ColliderRect const& other) : Collider(other)
{
	model_ = other.model_;
	world_ = other.world_;
}

ColliderRect::ColliderRect(ColliderRect&& other) noexcept : Collider(other)
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
	set_tag("Rect"s);
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

	RECT rc{ static_cast<long>(world_.l), static_cast<long>(world_.t), static_cast<long>(world_.r), static_cast<long>(world_.b) };
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
