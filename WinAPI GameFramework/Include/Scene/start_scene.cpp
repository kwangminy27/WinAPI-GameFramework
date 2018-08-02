#include "scene_manager.h"
#include "scene.h"
#include "layer.h"
#include "start_scene.h"
#include "main_scene.h"
#include "../Object/object_manager.h"
#include "../input.h"
#include "../Object/button_ui.h"
#include "../Object/mouse_ui.h"

using namespace std;

bool StartScene::Initialize()
{
	auto current_scene = scene();
	current_scene->CreateLayer("UI", numeric_limits<int>::max());

	for (auto const& layer : current_scene->layer_list())
		layer->Initialize();

	auto const& ui_layer = scene()->FindLayer("UI");

	auto const& object_manager = ObjectManager::instance();

	auto button = dynamic_pointer_cast<ButtonUI>(object_manager->CreateObject<ButtonUI>("StartButton", ui_layer));
	button->set_callback([this](float time) {
		_Start(time);
	});

	Input::instance()->set_mouse(object_manager->CreateObject<MouseUI>("Mouse", ui_layer));

	return true;
}

void StartScene::_Release()
{
}

void StartScene::_Input(float time)
{
}

void StartScene::_Update(float time)
{
}

void StartScene::_LateUpdate(float time)
{
}

void StartScene::_Collision(float time)
{
}

void StartScene::_Render(HDC device_context, float time)
{
}

void StartScene::_Start(float time)
{
	SceneManager::instance()->CreateNextScene<MainScene>("MainScene");
}