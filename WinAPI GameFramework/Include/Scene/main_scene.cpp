#include "main_scene.h"
#include "scene.h"
#include "layer.h"
#include "../Object/object_manager.h"
#include "../Object/player.h"
#include "../Object/bullet.h"

void MainScene::_Release()
{
}

bool MainScene::_Initialize()
{
	auto const& default_layer = scene()->FindLayer("Default"s);
	auto player = ObjectManager::instance()->CreateObject<Player>("Player"s, default_layer);
	ObjectManager::instance()->CreatePrototype<Bullet>("Bullet"s, scene());

	player->set_position(100.f, 100.f);
	player->set_size(100.f, 100.f);
	player->set_pivot(0.5f, 0.5f);

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
