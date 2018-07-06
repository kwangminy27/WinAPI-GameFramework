#pragma once

#include "../tag.h"

class Scene;

class Layer : public Tag
{
	friend class Scene;
public:
	void set_scene(std::shared_ptr<Scene> const& scene);
	void set_z_order(int z_order);

private:
	Layer() = default;

	virtual void _Release() override;

	bool _Initialize(float time);
	void _Input(float time);
	void _Update(float time);
	void _LastUpdate(float time);
	void _Collision(float time);
	void _Render(HDC device_context, float time);

	std::weak_ptr<Scene> scene_{};
	int z_order_{};
};