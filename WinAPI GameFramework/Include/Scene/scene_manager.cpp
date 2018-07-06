#include "scene_manager.h"
#include "scene.h"

using namespace std;

bool SceneManager::Initialize()
{
	scene_ = _CreateScene("MainScene"s);

	return true;
}

void SceneManager::Input(float time)
{
	scene_->_Input(time);
}

void SceneManager::Update(float time)
{
	scene_->_Update(time);
}

void SceneManager::LastUpdate(float time)
{
	scene_->_LastUpdate(time);
}

void SceneManager::Collision(float time)
{
	scene_->_Collision(time);
}

void SceneManager::Render(HDC device_context, float time)
{
	scene_->_Render(device_context, time);
}

void SceneManager::_Release()
{
}

unique_ptr<Scene, function<void(Scene*)>> SceneManager::_CreateScene(std::string tag)
{
	auto scene = unique_ptr<Scene, function<void(Scene*)>>(new Scene, [](Scene *p) {
		p->_Release();
		delete p;
	});

	scene->set_tag(tag);

	return scene;
}
