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
	std::vector<std::weak_ptr<Collider>>& FindCollisionGroup(std::string const& tag);
	void AddCollider(std::shared_ptr<Object> const& object);
	void Collision(float time);

	void CreateCollisionPixelCollectionPrototype(std::string const& tag, std::wstring const& file_name, std::string const& path_tag);
	std::shared_ptr<PIXEL24_INFO> const& FindCollisionPixelCollectionPrototype(std::string const& tag) const;

private:
	CollisionManager() = default;
	CollisionManager(CollisionManager const&) = delete;
	CollisionManager& operator=(CollisionManager const&) = delete;

	virtual void _Release() override;

	std::vector<std::weak_ptr<Collider>> collision_group_nullptr_{};
	std::unordered_map<std::string, std::vector<std::weak_ptr<Collider>>> collision_group_collection_{};

	std::shared_ptr<PIXEL24_INFO> pixel_collider_prototype_nullptr_{};
	std::unordered_map<std::string, std::shared_ptr<PIXEL24_INFO>> pixel_collider_prototype_collection_{};
};