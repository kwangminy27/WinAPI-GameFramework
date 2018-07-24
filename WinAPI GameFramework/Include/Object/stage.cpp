#include "stage.h"
#include "../Resource/texture.h"
#include "../camera.h"
#include "../Collision/collider_pixel.h"

using namespace std;

XY const& Stage::map_size() const
{
	return map_size_;
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
	collider_pixel->set_collision_pixel_collection(L"Stage1.bmp", "TexturePath");

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
