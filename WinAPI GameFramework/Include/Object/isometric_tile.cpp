#include "isometric_tile.h"

using namespace std;

bool IsometricTile::Initialize()
{
	set_type(TILE_TYPE::ISOMETRIC);

	return true;
}

IsometricTile::IsometricTile(IsometricTile const& other)
{
}

IsometricTile::IsometricTile(IsometricTile&& other) noexcept
{
}

void IsometricTile::_Release()
{
}

void IsometricTile::_Input(float time)
{
	Object::_Input(time);
}

void IsometricTile::_Update(float time)
{
	Object::_Update(time);
}

void IsometricTile::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void IsometricTile::_Collision(float time)
{
	Object::_Collision(time);
}

void IsometricTile::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> IsometricTile::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new IsometricTile(*this), [](Object* p) {
		dynamic_cast<IsometricTile*>(p)->_Release();
		delete dynamic_cast<IsometricTile*>(p);
	}};
}