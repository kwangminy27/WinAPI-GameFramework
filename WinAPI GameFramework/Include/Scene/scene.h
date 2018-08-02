#pragma once

#include "../tag.h"

class Layer;
class SceneComponent;

class Scene final : public Tag, public std::enable_shared_from_this<Scene>
{
	friend class SceneManager;
public:
	void CreateLayer(std::string const& tag, int z_order = 0);
	std::shared_ptr<Layer> const& FindLayer(std::string const& tag) const;

	std::list<std::shared_ptr<Layer>> const& layer_list() const;

private:
	Scene() = default;
	
	virtual void _Release() override;

	template <typename T> std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>> _CreateSceneCompoenet(std::string const& tag);

	bool _Initialize();
	void _Input(float time);
	void _Update(float time);
	void _LateUpdate(float time);
	void _Collision(float time);
	void _Render(HDC device_context, float time);
	
	std::shared_ptr<Layer> layer_nullptr_{};
	std::list<std::shared_ptr<Layer>> layer_list_{};
	std::unique_ptr<SceneComponent, std::function<void(SceneComponent*)>> scene_component_{};
};

#include "scene.inl"