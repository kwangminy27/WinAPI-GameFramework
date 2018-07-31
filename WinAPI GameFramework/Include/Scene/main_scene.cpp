#include "main_scene.h"
#include "scene.h"
#include "layer.h"
#include "../Object/object_manager.h"
#include "../Object/player.h"
#include "../Object/monster.h"
#include "../camera.h"
#include "../Object/bullet.h"
#include "../Object/rotation_bullet.h"
#include "../Object/guided_bullet.h"
#include "../Object/parabola_bullet.h"
#include "../Object/stage.h"
#include "../Object/effect.h"
#include "../Object/button_ui.h"
#include "../Collision/collider_circle.h"

void MainScene::_Release()
{
}

bool MainScene::_Initialize()
{
	auto const& camera = Camera::instance();
	auto const& object_manager = ObjectManager::instance();

	auto const& background_layer = scene()->FindLayer("Background");
	auto const& default_layer = scene()->FindLayer("Default");
	auto const& ui_layer = scene()->FindLayer("UI");

	object_manager->CreatePrototype<Bullet>("Bullet", scene());
	object_manager->CreatePrototype<RotationBullet>("RotationBullet", scene());
	object_manager->CreatePrototype<GuidedBullet>("GuidedBullet", scene());
	object_manager->CreatePrototype<ParabolaBullet>("ParabolaBullet", scene());

	object_manager->CreateObject<Stage>("Stage", background_layer);

	auto player = dynamic_pointer_cast<Player>(object_manager->CreateObject<Player>("Player", default_layer));

	// camera의 set_world_size는 맵 크기를 얻어와야 할텐데.. 일단 테스트용으로 대충 숫자 집어넣자.
	camera->set_map_size({ 1500.f, 1200.f });
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
