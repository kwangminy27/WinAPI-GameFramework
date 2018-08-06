#include "tile.h"
#include "../camera.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"

using namespace std;

bool Tile::Initialize()
{
	set_color_key(RGB(255, 0, 255));
	option_tile_ = ResourceManager::instance()->LoadTexture("Normal", L"Tile/OptionNone.bmp");

	return true;
}

void Tile::RenderOptionTile(HDC device_context, float time)
{
	XY const& camera_position = Camera::instance()->world();

	int left = static_cast<int>(position_.x - size_.x * pivot_.x - camera_position.x);
	int top = static_cast<int>(position_.y - size_.y * pivot_.y - camera_position.y);
	int width = static_cast<int>(size_.x);
	int height = static_cast<int>(size_.y);

	TransparentBlt(device_context, left, top, width, height, option_tile_->memory_device_context(), 0, 0, width, height, color_key_);
}

TILE_TYPE Tile::type() const
{
	return type_;
}

TILE_OPTION Tile::option() const
{
	return option_;
}

pair<int, int> const& Tile::idx() const
{
	return idx_;
}

void Tile::set_type(TILE_TYPE type)
{
	type_ = type;
}

void Tile::set_option(TILE_OPTION option)
{
	option_ = option;

	switch (option)
	{
	case TILE_OPTION::NONE:
		option_tile_ = ResourceManager::instance()->LoadTexture("Normal", L"Tile/OptionNone.bmp");
		break;
	case TILE_OPTION::BLOCKED:
		option_tile_ = ResourceManager::instance()->LoadTexture("Blocked", L"Tile/OptionNoMove.bmp");
		break;
	}
}

void Tile::set_idx(std::pair<int, int> const& idx)
{
	idx_ = idx;
}

Tile::Tile(Tile const& other) : Object(other)
{
	type_ = other.type_;
	option_ = other.option_;
	idx_ = other.idx_;
	option_tile_ = other.option_tile_;
}

Tile::Tile(Tile&& other) noexcept : Object(move(other))
{
	type_ = move(other.type_);
	option_ = move(other.option_);
	idx_ = move(other.idx_);
	option_tile_ = move(other.option_tile_);
}

void Tile::_Release()
{
}

void Tile::_Input(float time)
{
	Object::_Input(time);
}

void Tile::_Update(float time)
{
	Object::_Update(time);
}

void Tile::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void Tile::_Collision(float time)
{
	Object::_Collision(time);
}

void Tile::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}

unique_ptr<Object, function<void(Object*)>> Tile::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new Tile(*this), [](Object* p) {
		dynamic_cast<Tile*>(p)->_Release();
		delete dynamic_cast<Tile*>(p);
	}};
}