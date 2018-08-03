#include "../math.h"
#include "../Object/object.h"
#include "collider.h"

using namespace std;

HBRUSH Collider::green_brush_ = CreateSolidBrush(RGB(0, 255, 0));
HBRUSH Collider::red_brush_ = CreateSolidBrush(RGB(255, 0, 0));
HPEN Collider::green_pen_ = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
HPEN Collider::red_pen_ = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));

COLLIDER Collider::collider_type() const
{
	return collider_type_;
}

XY const& Collider::pivot() const
{
	return pivot_;
}

XY const& Collider::size() const
{
	return size_;
}

XY const& Collider::intersect_position() const
{
	return intersect_position_;
}

string const& Collider::collision_group_tag() const
{
	return collision_group_tag_;
}

shared_ptr<Object> Collider::object() const
{
	return object_.lock();
}

list<weak_ptr<Collider>>& Collider::collided_collider_list()
{
	return collided_collider_list_;
}

void Collider::set_pivot(XY const& xy)
{
	pivot_ = xy;
}

void Collider::set_size(XY const& xy)
{
	size_ = xy;
}

void Collider::set_intersect_position(XY const& xy)
{
	intersect_position_ = xy;
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

void Collider::Render(HDC device_context, float time)
{
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

bool Collider::_CollisionBetweenPointAndPoint(XY const & src, XY const & dest)
{
	return (src.x == dest.x) && (src.y == dest.y);
}

bool Collider::_CollisionBetweenPointAndRect(XY const & src, RECT_INFO const & dest)
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

bool Collider::_CollisionBetweenPointAndCircle(XY const & src, CIRCLE_INFO const & dest)
{
	return Math::GetDistance(src, dest.center) <= dest.radius;
}

bool Collider::_CollisionBetweenPointAndPixel(XY const& src, weak_ptr<PIXEL24_INFO> const& dest)
{
	if (dest.expired())
		return false;

	return false;
}

bool Collider::_CollisionBetweenRectAndRect(RECT_INFO const& src, RECT_INFO const& dest)
{
	if (src.r < dest.l)
		return false;

	if (src.l > dest.r)
		return false;

	if (src.b < dest.t)
		return false;

	if (src.t > dest.b)
		return false;

	RECT_INFO intersect_rect{};
	
	if (src.l > dest.l)
		intersect_rect.l = src.l;
	else
		intersect_rect.l = dest.l;

	if (src.r < dest.r)
		intersect_rect.r = src.r;
	else
		intersect_rect.r = dest.r;

	if (src.t > dest.t)
		intersect_rect.t = src.t;
	else
		intersect_rect.t = dest.t;

	if (src.b < dest.b)
		intersect_rect.b = src.b;
	else
		intersect_rect.b = dest.b;

	intersect_position_.x = (intersect_rect.l + intersect_rect.r) / 2.f;
	intersect_position_.y = (intersect_rect.t + intersect_rect.b) / 2.f;

	return true;
}

bool Collider::_CollisionBetweenRectAndCircle(RECT_INFO const& src, CIRCLE_INFO const& dest)
{
	float closest_x = clamp(dest.center.x, src.l, src.r);
	float closest_y = clamp(dest.center.y, src.t, src.b);

	float distance = Math::GetDistance({ closest_x, closest_y }, dest.center);

	bool result = distance <= dest.radius;

	if (result)
	{
		float t = (distance - dest.radius) / distance;
		intersect_position_.x = closest_x + (dest.center.x - closest_x) * t;
		intersect_position_.y = closest_y + (dest.center.y - closest_y) * t;
	}

	return result;
}

bool Collider::_CollisionBetweenRectAndPixel(RECT_INFO const& src, weak_ptr<PIXEL24_INFO> const& dest)
{
	if (dest.expired())
		return false;

	auto caching_dest = dest.lock();

	RECT_INFO src_on_the_pixel_coordinate_system = { src.l - caching_dest->world.x, src.t - caching_dest->world.y, src.r - caching_dest->world.x, src.b - caching_dest->world.y };

	float pixel_collider_width = static_cast<float>(caching_dest->pixel24_collection.at(0).size());
	float pixel_collider_height = static_cast<float>(caching_dest->pixel24_collection.size());

	if (src_on_the_pixel_coordinate_system.r < 0.f ||
		src_on_the_pixel_coordinate_system.l > pixel_collider_width ||
		src_on_the_pixel_coordinate_system.b < 0.f ||
		src_on_the_pixel_coordinate_system.t > pixel_collider_height)
		return false;

	src_on_the_pixel_coordinate_system.r = src_on_the_pixel_coordinate_system.r > pixel_collider_width ? pixel_collider_width : src_on_the_pixel_coordinate_system.r;
	src_on_the_pixel_coordinate_system.l = src_on_the_pixel_coordinate_system.l < 0.f ? 0.f : src_on_the_pixel_coordinate_system.l;
	src_on_the_pixel_coordinate_system.b = src_on_the_pixel_coordinate_system.b > pixel_collider_height ? pixel_collider_height : src_on_the_pixel_coordinate_system.b;
	src_on_the_pixel_coordinate_system.t = src_on_the_pixel_coordinate_system.t < 0.f ? 0.f : src_on_the_pixel_coordinate_system.t;

	auto const& pixel24_collection = caching_dest->pixel24_collection;
	auto const& comparision_pixel24 = caching_dest->comparision_pixel24;
	for (int i = static_cast<int>(src_on_the_pixel_coordinate_system.t); i < static_cast<int>(src_on_the_pixel_coordinate_system.b); ++i)
	{
		for (int j = static_cast<int>(src_on_the_pixel_coordinate_system.l); j < static_cast<int>(src_on_the_pixel_coordinate_system.r); ++j)
		{
			if (pixel24_collection.at(i).at(j).r == comparision_pixel24.r &&
				pixel24_collection.at(i).at(j).g == comparision_pixel24.g &&
				pixel24_collection.at(i).at(j).b == comparision_pixel24.b)
			{
				intersect_position_ = XY{ static_cast<float>(j), static_cast<float>(i) };
				return true;
			}
		}
	}

	return false;
}

bool Collider::_CollisionBetweenCircleAndCircle(CIRCLE_INFO const& src, CIRCLE_INFO const& dest)
{
	float distance = Math::GetDistance(src.center, dest.center);

	bool result = distance <= src.radius + dest.radius;

	if (result)
	{
		float t = (distance - dest.radius) / distance;
		intersect_position_ = src.center + (dest.center - src.center) * t;
	}

	return result;
}

bool Collider::_CollisionBetweenCircleAndPixel(CIRCLE_INFO const& src, weak_ptr<PIXEL24_INFO> const& dest)
{
	if (dest.expired())
		return false;

	return false;
}

bool Collider::_CollisionBetweenPixelAndPixel(weak_ptr<PIXEL24_INFO> const& src, weak_ptr<PIXEL24_INFO> const& dest)
{
	if (dest.expired())
		return false;

	return false;
}