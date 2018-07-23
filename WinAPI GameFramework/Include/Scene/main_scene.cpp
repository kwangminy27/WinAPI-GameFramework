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
#include "../Collision/collider_circle.h"

void MainScene::_Release()
{
}

bool MainScene::_Initialize()
{
	auto const& object_mananger = ObjectManager::instance();

	auto const& default_layer = scene()->FindLayer("Default");

	object_mananger->CreatePrototype<Bullet>("Bullet", scene());
	object_mananger->CreatePrototype<RotationBullet>("RotationBullet", scene());
	object_mananger->CreatePrototype<GuidedBullet>("GuidedBullet", scene());
	object_mananger->CreatePrototype<ParabolaBullet>("ParabolaBullet", scene());

	auto player = dynamic_pointer_cast<Player>(object_mananger->CreateObject<Player>("Player", default_layer));

	auto monster1 = dynamic_pointer_cast<Monster>(object_mananger->CreateObject<Monster>("Monster", default_layer));
	monster1->set_position(200.f, 0.f);

	auto monster2 = dynamic_pointer_cast<Monster>(object_mananger->CreateObject<Monster>("Monster", default_layer));
	monster2->set_position(640.f, 360.f);

	auto monster3 = dynamic_pointer_cast<Monster>(object_mananger->CreateObject<Monster>("Monster", default_layer));
	monster3->set_position(1080.f, 720.f);

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
