#include "collider.h"
#include "../Object/object.h"
#include "../math.h"

using namespace std;

HBRUSH Collider::green_brush_ = CreateSolidBrush(RGB(0, 255, 0));
HBRUSH Collider::red_brush_ = CreateSolidBrush(RGB(255, 0, 0));
HPEN Collider::green_pen_ = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
HPEN Collider::red_pen_ = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

COLLIDER Collider::collider_type() const
{
	return collider_type_;
}

string const& Collider::collision_group_tag() const
{
	return collision_group_tag_;
}

shared_ptr<Object> Collider::object() const
{
	return object_.lock();
}

void Collider::set_pivot(XY const& xy)
{
	pivot_ = xy;
}

void Collider::set_collision_group_tag(string const& tag)
{
	collision_group_tag_ = tag;
}

void Collider::set_object(weak_ptr<Object> const& object)
{
	if (object.expired())
		return;

	object_ = object;
}

void Collider::SetCallBack(function<void(weak_ptr<Collider> const&, weak_ptr<Collider> const&, float)> const& function, COLLISION_CALLBACK type)
{
	collision_callback_collection_.at(static_cast<size_t>(type)).push_back(move(function));
}

void Collider::OnCollisionEnter(weak_ptr<Collider> const& dest, float time)
{
	for (auto const& function : collision_callback_collection_.at(static_cast<size_t>(COLLISION_CALLBACK::ENTER)))
		function(weak_from_this(), dest, time);
}

void Collider::OnCollision(weak_ptr<Collider> const& dest, float time)
{
	for (auto const& function : collision_callback_collection_.at(static_cast<size_t>(COLLISION_CALLBACK::STAY)))
		function(weak_from_this(), dest, time);
}

void Collider::OnCollisionLeave(weak_ptr<Collider> const& dest, float time)
{
	for (auto const& function : collision_callback_collection_.at(static_cast<size_t>(COLLISION_CALLBACK::LEAVE)))
		function(weak_from_this(), dest, time);
}

bool Collider::IsCollidedCollider(weak_ptr<Collider> const& collider)
{
	if (collider.expired())
		return false;

	auto caching_collider = collider.lock();

	for (auto const& collided_collider : collided_collider_list_)
	{
		if (collided_collider.lock() == caching_collider)
			return true;
	}

	return false;
}

void Collider::AddCollidedCollider(weak_ptr<Collider> const& collider)
{
	if (collider.expired())
		return;

	collided_collider_list_.push_back(collider);
}

void Collider::RemoveCollidedCollider(weak_ptr<Collider> const& collider)
{
	for (auto iter = collided_collider_list_.begin(); iter != collided_collider_list_.end(); ++iter)
	{
		if ((*iter).expired() || (*iter).lock() == collider.lock())
		{
			collided_collider_list_.erase(iter);
			return;
		}
	}
}

Collider::Collider(Collider const& other)
{
	*this = other;
}

Collider::Collider(Collider&& other) noexcept
{
	*this = move(other);
}

void Collider::_Release()
{
	for (auto iter = collided_collider_list_.begin(); iter != collided_collider_list_.end(); ++iter)
	{
		(*iter).lock()->RemoveCollidedCollider(weak_from_this());
		(*iter).lock()->OnCollisionLeave(weak_from_this(), 0.f);
	}
}

bool Collider::_Initialize()
{
	return true;
}

void Collider::_Update(float time)
{
}

void Collider::_Render(HDC device_context, float time)
{
}

bool Collider::_CollisionBetweenPointAndPoint(XY const & src, XY const & dest)
{
	return (src.x == dest.x) && (src.y == dest.y);
}

bool Collider::_CollisionBetweenPointAndRect(XY const & src, LTRB const & dest)
{
	if (src.x < dest.l)
		return false;

	if (src.x > dest.r)
		return false;

	if (src.y < dest.t)
		return false;

	if (src.y > dest.b)
		return false;

	return true;
}

bool Collider::_CollisionBetweenPointAndSphere(XY const & src, SPHERE const & dest)
{
	return Math::GetDistance(src, dest.center) <= dest.radius;
}

bool Collider::_CollisionBetweenRectAndRect(LTRB const& src, LTRB const& dest)
{
	if (src.r < dest.l)
		return false;

	if (src.l > dest.r)
		return false;

	if (src.b < dest.t)
		return false;

	if (src.t > dest.b)
		return false;

	return true;
}

bool Collider::_CollisionBetweenRectAndSphere(LTRB const& src, SPHERE const& dest)
{
	float closest_x = clamp(dest.center.x, src.l, src.r);
	float closest_y = clamp(dest.center.y, src.t, src.b);

	float distance = Math::GetDistance({ closest_x, closest_y }, dest.center);

	return distance <= dest.radius;
}

bool Collider::_CollisionBetweenSphereAndSphere(SPHERE const& src, SPHERE const& dest)
{
	return Math::GetDistance(src.center, dest.center) <= src.radius + dest.radius;
}
