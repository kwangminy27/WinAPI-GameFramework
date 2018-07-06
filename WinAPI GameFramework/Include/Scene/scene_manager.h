#pragma once

#include "../singleton.h"

class Scene;

class SceneManager final : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;
public:
	bool Initialize();
	void Input(float time);
	void Update(float time);
	void LastUpdate(float time);
	void Collision(float time);
	void Render(HDC device_context, float time);

private:
	SceneManager() = default;
	SceneManager(SceneManager const&) = delete;
	SceneManager& operator=(SceneManager const&) = delete;

	virtual void _Release() override;

	std::unique_ptr<Scene, std::function<void(Scene*)>> _CreateScene(std::string tag);

	std::unique_ptr<Scene, std::function<void(Scene*)>> scene_{};
};