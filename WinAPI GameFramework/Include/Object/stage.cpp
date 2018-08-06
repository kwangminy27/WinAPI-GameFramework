#include "stage.h"
#include "../Resource/texture.h"
#include "../camera.h"
#include "../Collision/collider_pixel.h"
#include "tile.h"

using namespace std;

bool Stage::Initialize()
{
	type_ = OBJECT_TYPE::STAGE;

	set_size({ static_cast<float>(RESOLUTION::WIDTH), static_cast<float>(RESOLUTION::HEIGHT) });
	set_texture("Rogue Encampment", L"Rogue Encampment.bmp", "TexturePath");

	auto caching_texture = texture_.lock();
	set_map_size({ static_cast<float>(caching_texture->width()), static_cast<float>(caching_texture->height()) });
	Camera::instance()->set_map_size(map_size_);

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

XY const& Stage::map_size() const
{
	return map_size_;
}

int Stage::idx_width() const
{
	return idx_width_;
}

int Stage::idx_height() const
{
	return idx_height_;
}

XY const& Stage::tile_size() const
{
	return tile_size_;
}

bool Stage::tile_option_flag() const
{
	return tile_option_flag_;
}

void Stage::set_map_size(XY const& size)
{
	map_size_ = size;
}

void Stage::set_idx_width(int width)
{
	idx_width_ = width;
}

void Stage::set_idx_height(int height)
{
	idx_height_ = height;
}

void Stage::set_tile_size(XY const& size)
{
	tile_size_ = size;
}

void Stage::set_tile_option_flag(bool flag)
{
	tile_option_flag_ = flag;
}

void Stage::CreateGrid(TILE_TYPE type, int idx_width, int idx_height, XY const& map_size, string const& tag, wstring const& file_name, string path_tag)
{
	set_map_size(map_size);
	set_idx_width(idx_width);
	set_idx_height(idx_height);
	set_tile_size({ map_size.x / idx_width, map_size.y / idx_height });

	switch (type)
	{
	case TILE_TYPE::NORMAL:
		tile_collection_.resize(idx_height);
		for (int i = 0; i < idx_height; ++i)
		{
			tile_collection_.at(i).resize(idx_width);
			for (int j = 0; j < idx_width; ++j)
			{
				auto tile = shared_ptr<Tile>(new Tile, [](Tile* p) {
					p->_Release();
					delete (p);
				});

				tile->Initialize();

				tile->set_position({ tile_size_.x * j, tile_size_.y * i });
				tile->set_size(tile_size_);
				tile->set_idx({ j, i });

				tile->set_texture(tag, file_name);

				tile_collection_.at(i).at(j) = move(tile);
			}
		}
		break;
	case TILE_TYPE::ISOMETRIC:
		break;
	}
}

shared_ptr<Object>& Stage::GetTile(float x, float y)
{
	if (tile_collection_.empty())
		assert(!"Stage::GetTile");

	if (dynamic_pointer_cast<Tile>(tile_collection_.at(0).at(0))->type() == TILE_TYPE::ISOMETRIC)
	{
		// 아이소메트릭 방식으로 처리
	}

	int	idx_x = static_cast<int>(x / tile_size_.x);
	int	idx_y = static_cast<int>(y / tile_size_.y);

	idx_x = clamp(idx_x, 0, idx_width_ - 1);
	idx_y = clamp(idx_y, 0, idx_height_ - 1);

	return tile_collection_.at(idx_y).at(idx_x);
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
	idx_width_ = other.idx_width_;
	idx_height_ = other.idx_height_;
	tile_size_ = other.tile_size_;
	idx_view_x_range_ = other.idx_view_x_range_;
	idx_view_y_range_ = other.idx_view_y_range_;
	tile_option_flag_ = other.tile_option_flag_;

	if (!other.tile_collection_.empty())
	{
		tile_collection_.clear();
		tile_collection_.resize(other.tile_collection_.size());
		for (size_t i = 0; i < tile_collection_.size(); ++i)
		{
			tile_collection_.at(i).resize(other.tile_collection_.at(i).size());
			for (size_t j = 0; j < tile_collection_.at(0).size(); ++j)
				tile_collection_.at(i).at(j) = dynamic_pointer_cast<Tile>(other.tile_collection_.at(i).at(j))->_Clone();
		}
	}
}

Stage::Stage(Stage&& other) noexcept : Object(move(other))
{
	idx_width_ = move(other.idx_width_);
	idx_height_ = move(other.idx_height_);
	tile_size_ = move(other.tile_size_);
	idx_view_x_range_ = move(other.idx_view_x_range_);
	idx_view_y_range_ = move(other.idx_view_y_range_);
	tile_option_flag_ = move(other.tile_option_flag_);

	tile_collection_ = move(other.tile_collection_);
}

void Stage::_Release()
{
}

void Stage::_Input(float time)
{
	Object::_Input(time);

	if (tile_collection_.empty())
		return;

	for (auto i = idx_view_y_range_.first; i <= idx_view_y_range_.second; ++i)
		for (auto j = idx_view_x_range_.first; j <= idx_view_x_range_.second; ++j)
			dynamic_pointer_cast<Tile>(tile_collection_.at(i).at(j))->_Input(time);
}

void Stage::_Update(float time)
{
	Object::_Update(time);

	auto const& camera_view_start = Camera::instance()->world();
	auto const& camera_view_end = XY{ camera_view_start.x + static_cast<float>(RESOLUTION::WIDTH), camera_view_start.y + static_cast<float>(RESOLUTION::HEIGHT) };

	idx_view_x_range_ = { static_cast<int>(camera_view_start.x / tile_size_.x), static_cast<int>(camera_view_end.x / tile_size_.x) };
	idx_view_y_range_ = { static_cast<int>(camera_view_start.y / tile_size_.y), static_cast<int>(camera_view_end.y / tile_size_.y) };

	if (tile_collection_.empty())
		return;

	for (auto i = idx_view_y_range_.first; i <= idx_view_y_range_.second; ++i)
		for (auto j = idx_view_x_range_.first; j <= idx_view_x_range_.second; ++j)
			dynamic_pointer_cast<Tile>(tile_collection_.at(i).at(j))->_Update(time);
}

void Stage::_LateUpdate(float time)
{
	Object::_LateUpdate(time);

	if (tile_collection_.empty())
		return;

	for (auto const& tile_row : tile_collection_)
		for (auto const& tile : tile_row)
			dynamic_pointer_cast<Tile>(tile)->_LateUpdate(time);
}

void Stage::_Collision(float time)
{
	Object::_Collision(time);

	if (tile_collection_.empty())
		return;

	for (auto i = idx_view_y_range_.first; i <= idx_view_y_range_.second; ++i)
		for (auto j = idx_view_x_range_.first; j <= idx_view_x_range_.second; ++j)
			dynamic_pointer_cast<Tile>(tile_collection_.at(i).at(j))->_Collision(time);
}

void Stage::_Render(HDC device_context, float time)
{
	if (texture_.expired())
		return;

	auto caching_texture = texture_.lock();

	XY camera_position = Camera::instance()->world();

	TransparentBlt(device_context, 0, 0, static_cast<int>(size_.x), static_cast<int>(size_.y), caching_texture->memory_device_context(), static_cast<int>(camera_position.x), static_cast<int>(camera_position.y), static_cast<int>(size_.x), static_cast<int>(size_.y), color_key_);

	if (tile_collection_.empty())
		return;

	for (auto i = idx_view_y_range_.first; i <= idx_view_y_range_.second; ++i)
		for (auto j = idx_view_x_range_.first; j <= idx_view_x_range_.second; ++j)
			dynamic_pointer_cast<Tile>(tile_collection_.at(i).at(j))->_Render(device_context, time);

	if (tile_option_flag_)
	{
		for (auto i = idx_view_y_range_.first; i <= idx_view_y_range_.second; ++i)
			for (auto j = idx_view_x_range_.first; j <= idx_view_x_range_.second; ++j)
				dynamic_pointer_cast<Tile>(tile_collection_.at(i).at(j))->RenderOptionTile(device_context, time);
	}
}

unique_ptr<Object, function<void(Object*)>> Stage::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>{new Stage(*this), [](Object* p) {
		dynamic_cast<Stage*>(p)->_Release();
		delete dynamic_cast<Stage*>(p);
	}};
}
