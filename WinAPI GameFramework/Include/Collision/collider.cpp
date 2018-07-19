#include "collider.h"
#include "../Object/object.h"

using namespace std;

HBRUSH Collider::green_brush_ = CreateSolidBrush(RGB(0, 255, 0));
HBRUSH Collider::red_brush_ = CreateSolidBrush(RGB(255, 0, 0));

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

void Collider::set_object(std::weak_ptr<Object> const& object)
{
	object_ = object;
}

void Collider::SetCallBack(function<void(weak_ptr<Collider>, weak_ptr<Collider>, float)> function, COLLISION_CALLBACK type)
{
	collision_callback_collection_.at(static_cast<size_t>(type)).push_back(function);
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
	for (auto const& collided_collider : collided_collider_list_)
	{
		if (collided_collider.lock() == collider.lock())
			return true;
	}

	return false;
}

void Collider::AddCollidedCollider(weak_ptr<Collider> const& collider)
{
	collided_collider_list_.push_back(collider);
}

void Collider::RemoveCollidedCollider(weak_ptr<Collider> const& collider)
{
	for (auto iter = collided_collider_list_.begin(); iter != collided_collider_list_.end(); ++iter)
	{
		if ((*iter).lock() == collider.lock())
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

bool Collider::CollisionBetweenRectAndRect(LTRB const& src, LTRB const& dest)
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
