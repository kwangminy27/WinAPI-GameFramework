#pragma once

#include "../tag.h"

class Scene;

class SceneComponent : public Tag
{
	friend class Scene;
public:
	std::shared_ptr<Scene> scene() const;
	void set_scene(std::shared_ptr<Scene> const& scene);

protected:
	SceneComponent() = default;
	virtual ~SceneComponent() = default;

	virtual void _Release() = 0;

	virtual bool _Initialize() = 0;
	virtual void _Input(float time) = 0;
	virtual void _Update(float time) = 0;
	virtual void _LateUpdate(float time) = 0;
	virtual void _Collision(float time) = 0;
	virtual void _Render(HDC device_context, float time) = 0;

	std::weak_ptr<Scene> scene_{};
};