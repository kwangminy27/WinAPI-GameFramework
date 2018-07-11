#include "scene.h"
#include "layer.h"
#include "main_scene.h"
#include "../Object/object_manager.h"
#include "../Object/player.h"

void MainScene::_Release()
{
}

bool MainScene::_Initialize()
{
	Tag::_Initialize();
	
	auto default_layer = scene()->FindLayer("Default"s);
	auto player = ObjectManager::instance()->CreateObject<Player>("Player"s, default_layer);

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
