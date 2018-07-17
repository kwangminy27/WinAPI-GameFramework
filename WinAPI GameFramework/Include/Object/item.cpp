#include "item.h"
#include "../Resource/resource_manager.h"

using namespace std;

Item::Item(Item const& other) : Object(other)
{
}

void Item::_Release()
{
}

bool Item::_Initialize()
{
	set_size(100.f, 100.f);
	set_pivot(0.5f, 0.5f);
	set_move_speed(500.f);

	texture_ = ResourceManager::instance()->LoadTexture("Bullet"s, L"Bullet.bmp"s, "TexturePath"s);
	set_color_key(RGB(0, 248, 0));

	return true;
}

void Item::_Input(float time)
{
}

void Item::_Update(float time)
{
}

void Item::_LateUpdate(float time)
{
}

void Item::_Collision(float time)
{
}

void Item::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> Item::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new Item(*this), [](Object* p) {
		dynamic_cast<Item*>(p)->_Release();
		delete dynamic_cast<Item*>(p);
	}};
}
