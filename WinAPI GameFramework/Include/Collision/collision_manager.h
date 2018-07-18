#pragma once

#include "../singleton.h"

class Collider;
class Object;

class CollisionManager final : public Singleton<CollisionManager>
{
	friend class Singleton<CollisionManager>;
public:
	bool Initialize();
	bool CreateCollisionGroup(std::string const& tag);
	std::vector<std::weak_ptr<Collider>> const& FindCollisionGroup(std::string const& tag);
	void AddCollider(std::shared_ptr<Object> const& object);

private:
	CollisionManager() = default;
	CollisionManager(CollisionManager const&) = delete;
	CollisionManager& operator=(CollisionManager const&) = delete;

	virtual void _Release() override;

	std::vector<std::weak_ptr<Collider>> collision_group_nullptr_{};
	std::unordered_map<std::string, std::vector<std::weak_ptr<Collider>>> collision_group_collection_{};
};