#pragma once

using namespace std;

template <typename T>
auto Scene::_CreateSceneCompoenet(string const& tag)
{
	auto scene_component = unique_ptr<SceneComponent, function<void(SceneComponent*)>>(new T, [](SceneComponent* p) {
		p->_Release();
		delete p;
	});

	scene_component->set_tag(tag);

	return scene_component;
}