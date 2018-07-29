#include "../path_manager.h"
#include "collision_manager.h"
#include "collider.h"
#include "../Object/object.h"

using namespace std;
using namespace filesystem;

bool CollisionManager::Initialize()
{
	CreateCollisionGroup("Default");
	CreateCollisionGroup("UI");

	CreateCollisionPixelCollectionPrototype("MainStage", L"Stage1.bmp", "TexturePath");

	return true;
}

bool CollisionManager::CreateCollisionGroup(string const& tag)
{
	if (&FindCollisionGroup(tag) != &collision_group_nullptr_)
		return false;

	auto group = vector<std::weak_ptr<Collider>>{};
	group.reserve(100);

	collision_group_collection_.insert(make_pair(move(tag), move(group)));

	return true;
}

vector<weak_ptr<Collider>>& CollisionManager::FindCollisionGroup(string const& tag)
{
	auto iter = collision_group_collection_.find(tag);

	if (iter == collision_group_collection_.end())
		return collision_group_nullptr_;

	return iter->second;
}

void CollisionManager::AddCollider(weak_ptr<Object> const& object)
{
	if (object.expired())
		return;

	auto caching_object = object.lock();
	auto const& collider_collection = caching_object->collider_collection();

	if (collider_collection.empty())
		return;

	for (auto const& collider : collider_collection)
	{
		if (!collider->enablement())
			continue;

		auto& collision_group = FindCollisionGroup(collider->collision_group_tag());

		if (&collision_group == &collision_group_nullptr_)
			continue;

		collision_group.push_back(collider);
	}
}

void CollisionManager::Collision(float time)
{
	for (auto& collision_group : collision_group_collection_)
	{
		auto current_collision_group = collision_group.second;
		if (current_collision_group.size() < 2)
		{
			collision_group.second.clear();
			continue;
		}

		for (size_t i = 0; i < current_collision_group.size() - 1; ++i)
		{
			auto src = current_collision_group.at(i).lock();
			auto src_object = src->object();
			for (size_t j = i + 1; j < current_collision_group.size(); ++j)
			{
				auto dest = current_collision_group.at(j).lock();
				auto dest_object = dest->object();

				if (src_object == dest_object)
					continue;

				if (src->Collision(dest))
				{
					if (!src->IsCollidedCollider(dest))
					{
						src->AddCollidedCollider(dest);
						dest->AddCollidedCollider(src);

						src->OnCollisionEnter(dest, time);
						dest->OnCollisionEnter(src, time);
					}
					else
					{
						src->OnCollision(dest, time);
						dest->OnCollision(src, time);
					}
				}
				else
				{
					if (src->IsCollidedCollider(dest))
					{
						src->RemoveCollidedCollider(dest);
						dest->RemoveCollidedCollider(src);

						src->OnCollisionLeave(dest, time);
						dest->OnCollisionLeave(src, time);
					}
				}
			}
		}

		collision_group.second.clear();
	}
}

void CollisionManager::CreateCollisionPixelCollectionPrototype(string const& tag, wstring const& file_name, string const& path_tag)
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
	// 2. ColliderManager에서 PIXEL24를 담는 벡터로 픽셀 충돌체 프로토 타입을 만든다.
	// 3. ColliderManager에서 FindColliderPixel을 제공하자. shared_ptr로 반환
	// 4. 스테이지가 변경되면 기존 픽셀 충돌체 프로토 타입을 정리해주자. (충분히 다 들고 있을만 하면 그냥 해제 하는 부분 따로 만들지 말자.)

	auto pixel_collider = make_shared<PIXEL24_INFO>();

	pixel_collider->pixel24_collection.resize(bitmap_info_header.biHeight);

	for (size_t i = 0; i < bitmap_info_header.biHeight; ++i)
	{
		pixel_collider->pixel24_collection.at(i).resize(bitmap_info_header.biWidth);
		file.read(reinterpret_cast<char*>(&pixel_collider->pixel24_collection.at(i).at(0)), sizeof(PIXEL24) * bitmap_info_header.biWidth);
	}
	reverse(pixel_collider->pixel24_collection.begin(), pixel_collider->pixel24_collection.end());

	pixel_collider_prototype_collection_.insert(make_pair(move(tag), move(pixel_collider)));
}

shared_ptr<PIXEL24_INFO> const& CollisionManager::FindCollisionPixelCollectionPrototype(string const& tag) const
{
	auto iter = pixel_collider_prototype_collection_.find(tag);

	if (iter == pixel_collider_prototype_collection_.end())
		return pixel_collider_prototype_nullptr_;

	return iter->second;
}

void CollisionManager::_Release()
{
}