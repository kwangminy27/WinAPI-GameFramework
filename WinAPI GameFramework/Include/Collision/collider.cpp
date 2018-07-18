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