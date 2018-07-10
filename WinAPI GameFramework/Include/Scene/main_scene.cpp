#include "main_scene.h"
#include "scene.h"
#include "layer.h"

void MainScene::_Release()
{
}

bool MainScene::_Initialize(std::shared_ptr<Scene> const& scene)
{
	Tag::_Initialize();

	set_scene(scene);

	auto const shared_scene = scene_.lock();

	if (!shared_scene)
		return false;

	auto const& layer = shared_scene->FindLayer("Default"s);

	return true;
}

void MainScene::_Input(float time)
{
}

void MainScene::_Update(float time)
{
}

void MainScene::_LateUpdate(float time)
{
}

void MainScene::_Collision(float time)
{
}

void MainScene::_Render(HDC device_context, float time)
{
}
