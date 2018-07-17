#include "main_scene.h"
#include "scene.h"
#include "layer.h"
#include "../Object/object_manager.h"
#include "../Object/player.h"
#include "../Object/monster.h"
#include "../Object/bullet.h"
#include "../Object/rotation_bullet.h"
#include "../Object/guided_bullet.h"
#include "../Object/parabola_bullet.h"

void MainScene::_Release()
{
}

bool MainScene::_Initialize()
{
	auto const& object_mananger = ObjectManager::instance();

	auto const& default_layer = scene()->FindLayer("Default"s);

	auto player = dynamic_pointer_cast<Player>(object_mananger->CreateObject<Player>("Player"s, default_layer));

	auto monster1 = dynamic_pointer_cast<Monster>(object_mananger->CreateObject<Monster>("Monster"s, default_layer));
	monster1->set_position(300.f, 300.f);
	monster1->set_target(player);

	auto monster2 = dynamic_pointer_cast<Monster>(object_mananger->CreateObject<Monster>("Monster"s, default_layer));
	monster2->set_position(400.f, 300.f);
	monster2->set_target(player);

	auto monster3 = dynamic_pointer_cast<Monster>(object_mananger->CreateObject<Monster>("Monster"s, default_layer));
	monster3->set_position(500.f, 300.f);
	monster3->set_target(player);
	
	object_mananger->CreatePrototype<Bullet>("Bullet"s, scene());
	object_mananger->CreatePrototype<RotationBullet>("RotationBullet"s, scene());
	object_mananger->CreatePrototype<GuidedBullet>("GuidedBullet"s, scene());
	object_mananger->CreatePrototype<ParabolaBullet>("ParabolaBullet"s, scene());

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
