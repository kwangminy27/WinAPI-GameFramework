#pragma once

#include "../tag.h"

class Layer;

class Scene final : public Tag
{
	friend class SceneManager;
private:
	Scene() = default;

	virtual void _Release() override;

	void _CreateLayer(std::string const& tag, int z_order = 0);

	bool _Initialize(std::shared_ptr<Scene> const& scene);
	void _Input(float time);
	void _Update(float time);
	void _LastUpdate(float time);
	void _Collision(float time);
	void _Render(HDC device_context, float time);

	std::list<std::unique_ptr<Layer, std::function<void(Layer*)>>> layer_list_{};
};