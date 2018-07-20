#include "collider_sphere.h"
#include "../math.h"
#include "../Object/object.h"
#include "collider_rect.h"

using namespace std;

SPHERE ColliderSphere::world() const
{
	return world_;
}

void ColliderSphere::set_model(SPHERE const& model)
{
	model_.center = model.center;
	model_.radius = model.radius;
}

bool ColliderSphere::Collision(shared_ptr<Collider> const& dest)
{
	if (!dest)
		return false;

	switch (dest->collider_type())
	{
	case COLLIDER::RECT:
		return _CollisionBetweenRectAndSphere(dynamic_pointer_cast<ColliderRect>(dest)->world(), world_);
	case COLLIDER::SPHERE:
		return _CollisionBetweenSphereAndSphere(world_, dynamic_pointer_cast<ColliderSphere>(dest)->world_);
	}

	return false;
}

ColliderSphere::ColliderSphere(ColliderSphere const& other) : Collider(other)
{
	model_ = other.model_;
	world_ = other.world_;
}

ColliderSphere::ColliderSphere(ColliderSphere&& other) noexcept : Collider(other)
{
	model_ = move(other.model_);
	world_ = move(other.world_);
}

void ColliderSphere::_Release()
{
	Collider::_Release();
}

bool ColliderSphere::_Initialize()
{
	collider_type_ = COLLIDER::SPHERE;

	return true;
}

void ColliderSphere::_Update(float time)
{
	if (!object_.expired())
	{
		world_.radius = model_.radius;

		auto object_position = object()->position();
		world_.center.x = object_position.x + model_.center.x + (model_.radius * pivot_.x);
		world_.center.y = object_position.y + model_.center.y + (model_.radius * pivot_.y);
	}
}

void ColliderSphere::_Render(HDC device_context, float time)
{
#ifdef _DEBUG
	if (collided_collider_list_.empty())
		pen_ = Collider::green_pen_;
	else
		pen_ = Collider::red_pen_;

	if (!object_.expired())
	{
		old_pen_ = static_cast<HPEN>(SelectObject(device_context, pen_));
		XY position = world_.center;
		MoveToEx(device_context, static_cast<int>(position.x + world_.radius), static_cast<int>(position.y), nullptr);
		for (size_t i = 6; i <= 360; i += 6)
		{
			position.x = world_.center.x + cosf(Math::DegreeToRadian(static_cast<float>(i))) * world_.radius;
			position.y = world_.center.y + sinf(Math::DegreeToRadian(static_cast<float>(i))) * world_.radius;

			LineTo(device_context, static_cast<int>(position.x), static_cast<int>(position.y));
		}
		SelectObject(device_context, old_pen_);
	}
#endif
}

unique_ptr<Collider, function<void(Collider*)>> ColliderSphere::_Clone()
{
	return unique_ptr<Collider, function<void(Collider*)>>{new ColliderSphere(*this), [](Collider* p) {
		dynamic_cast<ColliderSphere*>(p)->_Release();
		delete dynamic_cast<ColliderSphere*>(p);
	}};
}