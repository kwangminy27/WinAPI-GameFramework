#include "scene_manager.h"
#include "scene.h"
#include "../Object/object_manager.h"

using namespace std;

bool SceneManager::Initialize()
{
	scene_ = _CreateScene("StartScene");
	scene_->_Initialize();

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

void SceneManager::LateUpdate(float time)
{
	scene_->_LateUpdate(time);
}

void SceneManager::Collision(float time)
{
	scene_->_Collision(time);
}

void SceneManager::Render(HDC device_context, float time)
{
	scene_->_Render(device_context, time);
}

void SceneManager::AttemptSceneChanging()
{
	if (next_scene_)
	{
		ObjectManager::instance()->ErasePrototype(scene_);
		scene_ = move(next_scene_);
	}
}

void SceneManager::_Release()
{
}

shared_ptr<Scene> SceneManager::_CreateScene(string const& tag)
{
	auto scene = shared_ptr<Scene>(new Scene, [](Scene *p) {
		p->_Release();
		delete p;
	});

	scene->set_tag(tag);

	return scene;
}
