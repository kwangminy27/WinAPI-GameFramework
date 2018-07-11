#pragma once

#include "scene_component.h"

class MainScene final : public SceneComponent
{
	friend class Scene;
private:
	MainScene() = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;
};