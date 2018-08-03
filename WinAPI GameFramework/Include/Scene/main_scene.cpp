#include "main_scene.h"
#include "scene.h"
#include "layer.h"
#include "../Object/object_manager.h"
#include "../Object/player.h"
#include "../Object/monster.h"
#include "../input.h"
#include "../camera.h"
#include "../Object/bullet.h"
#include "../Object/rotation_bullet.h"
#include "../Object/guided_bullet.h"
#include "../Object/parabola_bullet.h"
#include "../Object/stage.h"
#include "../Object/effect.h"
#include "../Object/button_ui.h"
#include "../Object/mouse_ui.h"
#include "../Object/number.h"
#include "../Collision/collider_circle.h"

bool MainScene::Initialize()
{
	auto current_scene = scene();
	current_scene->CreateLayer("Background", numeric_limits<int>::min());
	current_scene->CreateLayer("Default");
	current_scene->CreateLayer("UI", numeric_limits<int>::max());

	for (auto const& layer : current_scene->layer_list())
		layer->Initialize();

	auto const& camera = Camera::instance();
	auto const& object_manager = ObjectManager::instance();

	auto const& background_layer = scene()->FindLayer("Background");
	auto const& default_layer = scene()->FindLayer("Default");
	auto const& ui_layer = scene()->FindLayer("UI");

	object_manager->CreatePrototype<Bullet>("Bullet", scene());
	object_manager->CreatePrototype<RotationBullet>("RotationBullet", scene());
	object_manager->CreatePrototype<GuidedBullet>("GuidedBullet", scene());
	object_manager->CreatePrototype<ParabolaBullet>("ParabolaBullet", scene());

	auto stage = dynamic_pointer_cast<Stage>(object_manager->CreateObject<Stage>("Stage", background_layer));
	camera->set_map_size(stage->map_size());

	auto player = dynamic_pointer_cast<Player>(object_manager->CreateObject<Player>("Player", default_layer));
	camera->set_target(player);
	camera->set_pivot({ 0.5f, 0.5f });

	auto monster1 = dynamic_pointer_cast<Monster>(object_manager->CreateObject<Monster>("Monster", default_layer));
	monster1->set_position(200.f, 200.f);

	auto monster2 = dynamic_pointer_cast<Monster>(object_manager->CreateObject<Monster>("Monster", default_layer));
	monster2->set_position(640.f, 600.f);

	auto monster3 = dynamic_pointer_cast<Monster>(object_manager->CreateObject<Monster>("Monster", default_layer));
	monster3->set_position(1080.f, 1000.f);

	object_manager->CreatePrototype<Effect>("BombEffect", scene());

	auto button = object_manager->CreateObject<ButtonUI>("Button", ui_layer);
	Input::instance()->set_mouse(object_manager->CreateObject<MouseUI>("Mouse", ui_layer));

	number_ = dynamic_pointer_cast<Number>(object_manager->CreateObject<Number>("Number", default_layer));
	number_->set_size({ 62.6f, 88.f });
	number_->set_position({ static_cast<float>(RESOLUTION::WIDTH) - 343.f, 500.f });
	number_->set_texture("Number", L"Number.bmp");
	number_->set_number(1000);

	return true;
}

void MainScene::_Release()
{
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
