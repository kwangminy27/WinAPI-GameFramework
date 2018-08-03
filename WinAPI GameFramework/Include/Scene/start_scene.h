#pragma once

#include "scene_component.h"

class StartScene final : public SceneComponent
{
	friend class Scene;
public:
	virtual bool Initialize() override;

private:
	StartScene() = default;

	virtual void _Release() override;

	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	void _Start(float time);
	void _Exit();
};