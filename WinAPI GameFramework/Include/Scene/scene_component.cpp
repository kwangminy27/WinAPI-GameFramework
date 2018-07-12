#include "scene_component.h"

using namespace std;

void SceneComponent::set_scene(weak_ptr<Scene> const& scene)
{
	scene_ = scene;
}

shared_ptr<Scene> SceneComponent::scene() const
{
	return scene_.lock();
}
