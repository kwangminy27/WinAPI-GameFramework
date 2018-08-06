#include "../core.h"
#include "scene_manager.h"
#include "scene.h"
#include "layer.h"
#include "start_scene.h"
#include "main_scene.h"
#include "edit_scene.h"
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

	auto start_button = dynamic_pointer_cast<ButtonUI>(object_manager->CreateObject<ButtonUI>("StartButton", ui_layer));
	start_button->set_position(200.f, 200.f);
	start_button->set_callback([this](float time) {
		_Start(time);
	});

	auto edit_button = dynamic_pointer_cast<ButtonUI>(object_manager->CreateObject<ButtonUI>("EditButton", ui_layer));
	edit_button->set_position(200.f, 350.f);
	edit_button->set_callback([this](float time) {
		_Edit();
	});

	auto exit_button = dynamic_pointer_cast<ButtonUI>(object_manager->CreateObject<ButtonUI>("ExitButton", ui_layer));
	exit_button->set_position(200.f, 500.f);
	exit_button->set_callback([this](float time) {
		_Exit();
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

void StartScene::_Edit()
{
	SceneManager::instance()->CreateNextScene<EditScene>("EditScene");
}

void StartScene::_Exit()
{
	DestroyWindow(Core::instance()->main_window());
}