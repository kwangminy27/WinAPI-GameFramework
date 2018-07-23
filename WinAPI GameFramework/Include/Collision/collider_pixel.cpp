#include "../path_manager.h"
#include "../Object/object.h"
#include "collider_point.h"
#include "collider_rect.h"
#include "collider_circle.h"
#include "collider_pixel.h"

using namespace std;
using namespace filesystem;

PIXEL_INFO const& ColliderPixel::world() const
{
	return world_;
}

void ColliderPixel::set_model(wstring file_name, string path_tag)
{
	path path_buffer = PathManager::instance()->FindPath(path_tag);

	if (path_buffer.empty())
		return;

	wstring full_path = path_buffer.wstring() + file_name;

	ifstream file{ full_path, ios::binary };

	if (file.bad())
		return;

	BITMAPFILEHEADER bitmap_file_header{};
	BITMAPINFOHEADER bitmap_info_header{};

	file.read(reinterpret_cast<char*>(&bitmap_file_header), sizeof(BITMAPFILEHEADER));
	file.read(reinterpret_cast<char*>(&bitmap_info_header), sizeof(BITMAPINFOHEADER));
	
	model_.pixel_size = bitmap_info_header.biBitCount / 8;
	model_.pixel_count = bitmap_info_header.biWidth * bitmap_info_header.biHeight;
	model_.width = bitmap_info_header.biWidth;
	model_.height = bitmap_info_header.biHeight;
}

bool ColliderPixel::Collision(weak_ptr<Collider> const& dest)
{
	if (dest.expired())
		return false;

	auto caching_dest = dest.lock();

	switch (caching_dest->collider_type())
	{
	case COLLIDER::POINT:
		break;
	case COLLIDER::RECT:
		break;
	case COLLIDER::CIRCLE:
		break;
	case COLLIDER::PIXEL:
		break;
	}

	return false;
}

ColliderPixel::ColliderPixel(ColliderPixel const& other) : Collider(other)
{
	model_ = other.model_;
	world_ = other.world_;
}

ColliderPixel::ColliderPixel(ColliderPixel&& other) noexcept : Collider(move(other))
{
	model_ = move(other.model_);
	world_ = move(other.world_);
}

void ColliderPixel::_Release()
{
}

bool ColliderPixel::_Initialize()
{
	collider_type_ = COLLIDER::PIXEL;

	return true;
}

void ColliderPixel::_Update(float time)
{
}

void ColliderPixel::_Render(HDC device_context, float time)
{
}

unique_ptr<Collider, function<void(Collider*)>> ColliderPixel::_Clone()
{
	return unique_ptr<Collider, function<void(Collider*)>>{ new ColliderPixel(*this), [](Collider* p) {
		dynamic_cast<ColliderPixel*>(p)->_Release();
		delete dynamic_cast<ColliderPixel*>(p);
	}};
}
