#include "collision_manager.h"
#include "collider.h"
#include "../Object/object.h"

using namespace std;

bool CollisionManager::Initialize()
{
	CreateCollisionGroup("Default"s);
	CreateCollisionGroup("UI"s);

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

void CollisionManager::AddCollider(shared_ptr<Object> const& object)
{
	auto const& collider_collection = object->collider_collection();

	if (collider_collection.empty())
		return;

	for (auto const& collider : collider_collection)
	{
		auto& collision_group = FindCollisionGroup(collider->collision_group_tag());

		if (&collision_group == &collision_group_nullptr_)
			continue;

		collision_group.push_back(collider);
	}
}

void CollisionManager::ClearExpiredCollider()
{
	for (auto& collision_group : collision_group_collection_)
		collision_group.second.clear();
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
					src->RemoveCollidedCollider(dest);
					dest->RemoveCollidedCollider(src);

					src->OnCollisionLeave(dest, time);
					dest->OnCollisionLeave(src, time);
				}
			}
		}

		collision_group.second.clear();
	}
}

void CollisionManager::_Release()
{
}