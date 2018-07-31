#include "../path_manager.h"
#include "../camera.h"
#include "../Object/object.h"
#include "collider_point.h"
#include "collider_rect.h"
#include "collider_circle.h"
#include "collider_pixel.h"
#include "collision_manager.h"

using namespace std;
using namespace filesystem;

XY const& ColliderPixel::world() const
{
	return pixel_collider()->world;
}

PIXEL24 const& ColliderPixel::comparision_pixel() const
{
	return pixel_collider()->comparision_pixel24;
}

shared_ptr<PIXEL24_INFO> ColliderPixel::pixel_collider() const
{
	return pixel_collider_.lock();
}

void ColliderPixel::set_world(XY const& xy)
{
	pixel_collider()->world = xy;
}

void ColliderPixel::set_pixel_collider(string const& tag)
{
	pixel_collider_ = CollisionManager::instance()->FindCollisionPixelCollectionPrototype(tag);
}

void ColliderPixel::set_comparision_pixel(PIXEL24 const& pixel)
{
	pixel_collider()->comparision_pixel24 = pixel;
}

bool ColliderPixel::Collision(weak_ptr<Collider> const& dest)
{
	if (dest.expired())
		return false;

	auto caching_dest = dest.lock();

	switch (caching_dest->collider_type())
	{
	case COLLIDER::POINT:
		return _CollisionBetweenPointAndPixel(dynamic_pointer_cast<ColliderPoint>(caching_dest)->world(), pixel_collider_);
	case COLLIDER::RECT:
		return _CollisionBetweenRectAndPixel(dynamic_pointer_cast<ColliderRect>(caching_dest)->world(), pixel_collider_);
	case COLLIDER::CIRCLE:
		return _CollisionBetweenCircleAndPixel(dynamic_pointer_cast<ColliderCircle>(caching_dest)->world(), pixel_collider_);
	case COLLIDER::PIXEL:
		return _CollisionBetweenPixelAndPixel(pixel_collider_, dynamic_pointer_cast<ColliderPixel>(caching_dest)->pixel_collider_);
	}

	return false;
}

ColliderPixel::ColliderPixel(ColliderPixel const& other) : Collider(other)
{
	pixel_collider_ = other.pixel_collider_;
}

ColliderPixel::ColliderPixel(ColliderPixel&& other) noexcept : Collider(move(other))
{
	pixel_collider_ = move(other.pixel_collider_);
}

void ColliderPixel::_Release()
{
	Collider::_Release();
}

bool ColliderPixel::_Initialize()
{
	collider_type_ = COLLIDER::PIXEL;

	return true;
}

void ColliderPixel::_Update(float time)
{
	if (object_.expired())
		return;

	auto caching_object = object();
	auto object_position = caching_object->position();

	if (caching_object->type() == OBJECT_TYPE::UI)
		object_position += Camera::instance()->world();

	pixel_collider()->world.x = object_position.x - pixel_collider()->pixel24_collection.at(0).size() * pivot_.x;
	pixel_collider()->world.y = object_position.y - pixel_collider()->pixel24_collection.size() * pivot_.y;
}

void ColliderPixel::_Render(HDC device_context, float time)
{
}

unique_ptr<Collider, function<void(Collider*)>> ColliderPixel::_Clone()
{
	return unique_ptr<Collider, function<void(Collider*)>>{ new ColliderPixel(*this), [](Collider* p) {
		dynamic_cast<ColliderPixel*>(p)->_Release();
		delete dynamic_cast<ColliderPixel*>(p);
	} };
}
