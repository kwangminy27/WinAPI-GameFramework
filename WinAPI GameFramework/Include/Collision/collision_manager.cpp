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
	if (&FindCollisionGroup(tag) == &collision_group_nullptr_)
		return false;

	auto group = vector<std::weak_ptr<Collider>>{};
	group.reserve(100);

	collision_group_collection_.insert(make_pair(move(tag), move(group)));

	return true;
}

vector<weak_ptr<Collider>> const& CollisionManager::FindCollisionGroup(string const& tag)
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
		auto collision_group = FindCollisionGroup(collider->collision_group_tag());

		if (&collision_group == &collision_group_nullptr_)
			continue;

		collision_group.push_back(collider->weak_from_this());
	}
}

void CollisionManager::_Release()
{
}