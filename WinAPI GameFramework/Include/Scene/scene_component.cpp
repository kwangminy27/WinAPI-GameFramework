#include "scene_component.h"

using namespace std;

void SceneComponent::set_scene(std::shared_ptr<Scene> const& scene)
{
	scene_ = scene;
}