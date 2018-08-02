#pragma once

template <typename T>
void SceneManager::CreateNextScene(string const& tag)
{
	next_scene_ = _CreateScene(tag);

	next_scene_->scene_component_ = next_scene_->_CreateSceneCompoenet<T>(tag);
	next_scene_->scene_component_->Initialize();
}