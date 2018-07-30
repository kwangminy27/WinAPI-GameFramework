#include "stage.h"
#include "../Resource/texture.h"
#include "../camera.h"
#include "../Collision/collider_pixel.h"

using namespace std;

XY const& Stage::map_size() const
{
	return map_size_;
}

void Stage::set_map_size(XY const& size)
{
	map_size_ = size;
}

void Stage::BeAttached(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
	if (src.expired() || dest.expired())
		return;

	auto caching_dest = dest.lock();

	if (caching_dest->tag() == "PlayerBody")
	{
		auto caching_src = dynamic_pointer_cast<ColliderPixel>(src.lock());
		auto pixel_collider = caching_src->pixel_collider();

		XY const& intersect_position = caching_src->intersect_position();
		auto const& comparision_pixel24 = pixel_collider->comparision_pixel24;
		auto const& pixel24_collection = pixel_collider->pixel24_collection;

		auto object = caching_dest->object();

		XY const& object_position_on_the_model_coordinate_system = object->position() - caching_src->world();
		XY const& object_size = object->size();
		XY const& object_pivot = object->pivot();

		if (object_position_on_the_model_coordinate_system.y <= intersect_position.y)
		{
			for (int i = static_cast<int>(object_position_on_the_model_coordinate_system.y); i <= static_cast<int>(intersect_position.y); ++i)
			{
				if (pixel24_collection.at(i).at(static_cast<int>(intersect_position.x)).r == comparision_pixel24.r &&
					pixel24_collection.at(i).at(static_cast<int>(intersect_position.x)).g == comparision_pixel24.g &&
					pixel24_collection.at(i).at(static_cast<int>(intersect_position.x)).b == comparision_pixel24.b)
				{
					XY object_position = object->position();
					object_position.y = i - object_size.y * object_pivot.y + 1.f;
					object->set_position(object_position);

					object->set_physics_flag(false);
					object->set_velocity(0.f);
					object->set_energy(0.f);
					return;
				}
			}
		}
		else
		{
			for (int i = static_cast<int>(object_position_on_the_model_coordinate_system.y); i >= static_cast<int>(intersect_position.y); --i)
			{
				if (pixel24_collection.at(i).at(static_cast<int>(intersect_position.x)).r == comparision_pixel24.r &&
					pixel24_collection.at(i).at(static_cast<int>(intersect_position.x)).g == comparision_pixel24.g &&
					pixel24_collection.at(i).at(static_cast<int>(intersect_position.x)).b == comparision_pixel24.b)
				{
					XY object_position = object->position();
					object_position.y = i + object_size.y * object_pivot.y;
					object->set_position(object_position);
					return;
				}
			}
		}
	}
}

void Stage::BeDetached(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time)
{
	if (src.expired() || dest.expired())
		return;

	auto caching_dest = dest.lock();

	if (caching_dest->tag() == "PlayerBody")
	{
		auto object = caching_dest->object();

		object->set_physics_flag(true);
	}
}

Stage::Stage(Stage const& other) : Object(other)
{
}

Stage::Stage(Stage&& other) noexcept : Object(move(other))
{
}

void Stage::_Release()
{
}

bool Stage::_Initialize()
{
	set_size({ static_cast<float>(RESOLUTION::WIDTH), static_cast<float>(RESOLUTION::HEIGHT) });
	set_texture("Stage", L"Stage1.bmp", "TexturePath");

	auto collider_pixel = dynamic_pointer_cast<ColliderPixel>(AddCollider<ColliderPixel>("StageCollider"));
	collider_pixel->set_pixel_collider("MainStage");
	collider_pixel->set_comparision_pixel({ 255, 0, 255 });
	collider_pixel->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		BeAttached(src, dest, time);
	}, COLLISION_CALLBACK::ENTER);
	collider_pixel->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		BeAttached(src, dest, time);
	}, COLLISION_CALLBACK::STAY);
	collider_pixel->SetCallBack([this](weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time) {
		BeDetached(src, dest, time);
	}, COLLISION_CALLBACK::LEAVE);

	return true;
}

void Stage::_Input(float time)
{
	Object::_Input(time);
}

void Stage::_Update(float time)
{
	Object::_Update(time);
}

void Stage::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void Stage::_Collision(float time)
{
	Object::_Collision(time);
}

void Stage::_Render(HDC device_context, float time)
{
	if (texture_.expired())
		return;

	auto caching_texture = texture_.lock();

	XY camera_position = Camera::instance()->world();

	TransparentBlt(device_context, 0, 0, static_cast<int>(size_.x), static_cast<int>(size_.y), caching_texture->memory_device_context(), static_cast<int>(camera_position.x), static_cast<int>(camera_position.y), static_cast<int>(size_.x), static_cast<int>(size_.y), color_key_);
}

unique_ptr<Object, function<void(Object*)>> Stage::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{ new Stage(*this), [](Object* p) {
		dynamic_cast<Stage*>(p)->_Release();
		delete dynamic_cast<Stage*>(p);
	} };
}
