#pragma once

#include "../tag.h"

class Layer;
class SceneComponent;

class Scene final : public Tag
{
	friend class SceneManager;
public:
	std::unique_ptr<Layer, std::function<void(Layer*)>> const& FindLayer(std::string const& tag) const;

private:
	Scene() = default;

	virtual void _Release() override;

	void _CreateLayer(std::string const& tag, int z_order = 0);
	template <typename T> auto _CreateSceneCompoenet(std::string const& tag);

	bool _Initialize(std::shared_ptr<Scene> const& scene);
	void _Input(float time);
	void _Update(float time);
	void _LateUpdate(float time);
	void _Collision(float time);
	void _Render(HDC device_context, float time);

	std::list<std::unique_ptr<Layer, std::function<void(Layer*)>>> layer_list_{};
	std::unique_ptr<Layer, std::function<void(Layer*)>> nullptr_layer_{};
	std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>> scene_component_{};
};

#include "scene.inl"