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
	void LateUpdate(float time);
	void Collision(float time);
	void Render(HDC device_context, float time);

	template <typename T> void CreateNextScene(std::string const& tag);
	void AttemptSceneChanging();

private:
	SceneManager() = default;
	SceneManager(SceneManager const&) = delete;
	SceneManager& operator=(SceneManager const&) = delete;

	virtual void _Release() override;

	std::shared_ptr<Scene> _CreateScene(std::string const& tag);

	std::shared_ptr<Scene> scene_{};
	std::shared_ptr<Scene> next_scene_{};
};

#include "scene_manager.inl"