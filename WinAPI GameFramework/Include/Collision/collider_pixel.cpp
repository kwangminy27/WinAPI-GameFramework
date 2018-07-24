#include "../path_manager.h"
#include "../Object/object.h"
#include "collider_point.h"
#include "collider_rect.h"
#include "collider_circle.h"
#include "collider_pixel.h"

using namespace std;
using namespace filesystem;

vector<vector<PIXEL24>> const& ColliderPixel::collision_pixel_collection() const
{
	return collision_pixel_collection_;
}

PIXEL24 const& ColliderPixel::comparision_pixel() const
{
	return comparision_pixel_;
}

void ColliderPixel::set_collision_pixel_collection(wstring const& file_name, string const& path_tag)
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

	// 1. 비트맵의 픽셀 크기를 구해서 픽셀 구조체를 특정한다. -> 일단 PIXEL24로 고정해서 사용하자.
	// 2. 특정한 구조체를 담는 벡터로 픽셀 충돌체 프로토 타입을 만든다.
	// 3. 픽셀 충돌체를 공유 포인터로 참조하는 식으로 관리한다.

	collision_pixel_collection_.resize(bitmap_info_header.biHeight);
	for (size_t i = 0; i < bitmap_info_header.biHeight; ++i)
	{
		collision_pixel_collection_.at(i).resize(bitmap_info_header.biWidth);
		file.read(reinterpret_cast<char*>(&collision_pixel_collection_.at(i).at(0)), sizeof(PIXEL24) * bitmap_info_header.biWidth);
	}

	reverse(collision_pixel_collection_.begin(), collision_pixel_collection_.end());
}

void ColliderPixel::set_comparision_pixel(PIXEL24 const& pixel)
{
	comparision_pixel_ = pixel;
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
	comparision_pixel_ = other.comparision_pixel_;
}

ColliderPixel::ColliderPixel(ColliderPixel&& other) noexcept : Collider(move(other))
{
	comparision_pixel_ = move(other.comparision_pixel_);
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
	} };
}
