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
	void ErasePrototype(std::shared_ptr<Scene> const& scene);
	template <typename T> std::shared_ptr<Object> CreateObject(std::string const& tag, std::shared_ptr<Layer> const& layer);
	std::shared_ptr<Object> CreateCloneObject(std::string const& tag, std::shared_ptr<Layer> const& layer);

private:
	ObjectManager() = default;
	ObjectManager(ObjectManager const&) = delete;
	ObjectManager& operator=(ObjectManager const&) = delete;

	virtual void _Release() override;

	std::unique_ptr<Object, std::function<void(Object*)>> const& _FindPrototype(std::string const& tag) const;

	std::shared_ptr<Object> object_nullptr_{};
	std::unique_ptr<Object, std::function<void(Object*)>> nullptr_prototype_{};
	std::unordered_map<std::string, std::unique_ptr<Object, std::function<void(Object*)>>> prototype_collection_{};
};

#include "object_manager.inl"