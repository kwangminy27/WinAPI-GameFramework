#pragma once

#include "../singleton.h"

class Scene;
class Layer;
class Object;

class ObjectManager final : public Singleton<ObjectManager>
{
	friend class Singleton<ObjectManager>;
public:
	template <typename T> void CreatePrototype(std::string const& tag, std::shared_ptr<Scene> const& scene);
	void ErasePrototype(std::shared_ptr<Scene> const& scene); // 씬 전환 시 명시적으로 호출해서 안쓰는 프로토타입을 정리하도록 하자.
	void ClearExpiredSceneObject();
	template <typename T> std::shared_ptr<Object> CreateObject(std::string const& tag, std::shared_ptr<Layer> const& layer);
	std::shared_ptr<Object> CreateCloneObject(std::string const& tag, std::shared_ptr<Layer> const& layer);
	std::pair<std::unordered_multimap<std::string, std::weak_ptr<Object>>::iterator, std::unordered_multimap<std::string, std::weak_ptr<Object>>::iterator> FindObjects(std::string const& tag);

private:
	ObjectManager() = default;
	ObjectManager(ObjectManager const&) = delete;
	ObjectManager& operator=(ObjectManager const&) = delete;

	virtual void _Release() override;

	std::unique_ptr<Object, std::function<void(Object*)>> const& _FindPrototype(std::string const& tag) const;

	std::shared_ptr<Object> object_nullptr_{};
	std::unique_ptr<Object, std::function<void(Object*)>> nullptr_prototype_{};
	std::unordered_map<std::string, std::unique_ptr<Object, std::function<void(Object*)>>> prototype_collection_{};
	std::unordered_multimap<std::string, std::weak_ptr<Object>> scene_object_collection_{};
};

#include "object_manager.inl"