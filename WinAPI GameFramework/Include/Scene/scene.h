#pragma once

#include "../tag.h"

class Scene final : public Tag
{
	friend class SceneManager;
private:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void _Release() override;

	bool _Initialize(float time);
	void _Input(float time);
	void _Update(float time);
	void _LastUpdate(float time);
	void _Collision(float time);
	void _Render(HDC device_context, float time);
};