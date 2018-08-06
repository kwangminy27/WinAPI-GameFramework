#include "edit_scene.h"
#include "scene.h"
#include "layer.h"
#include "../camera.h"
#include "../Object/object_manager.h"
#include "../Object/player.h"
#include "../Object/stage.h"
#include "../isometric_tile_map_editor.h"
#include "../Resource/resource_manager.h"
#include "../Resource/texture.h"

using namespace std;

bool EditScene::Initialize()
{
	auto current_scene = scene();
	current_scene->CreateLayer("Background", numeric_limits<int>::min());
	current_scene->CreateLayer("Default", 0);

	for (auto const& layer : current_scene->layer_list())
		layer->Initialize();

	auto const& camera = Camera::instance();
	auto const& object_manager = ObjectManager::instance();

	auto const& background_layer = scene()->FindLayer("Background");
	auto const& default_layer = scene()->FindLayer("Default");

	auto stage = dynamic_pointer_cast<Stage>(object_manager->CreateObject<Stage>("Stage", background_layer));
	stage->CreateGrid(TILE_TYPE::NORMAL, 100, 100, { 5200, 5200 }, "Ground", L"Tile/BaseTile.bmp");
	camera->set_map_size(stage->map_size());

	auto player = dynamic_pointer_cast<Player>(object_manager->CreateObject<Player>("Player", default_layer));
	camera->set_target(player);
	camera->set_pivot({ 0.5f, 0.5f });

	/*auto const& editer = IsometricTileMapEditor::instance();

	editer->set_width(10);
	editer->set_height(10);

	auto texture1 = ResourceManager::instance()->LoadTexture("Tile1", L"tile1.bmp");
	auto texture2 = ResourceManager::instance()->LoadTexture("Tile2", L"tile2.bmp");

	auto& whole_tile_map = editer->whole_tile_map();
	whole_tile_map.resize(10);
	for (size_t i = 0; i < 10; ++i)
	{
		whole_tile_map.at(i).resize(10);
		for (size_t j = 0; j < 10; ++j)
		{
			whole_tile_map.at(i).at(j) = shared_ptr<Tile>{ new Tile, [](Tile* p) {
				delete p;
			} };
			whole_tile_map.at(i).at(j)->movable_flag_ = true;
			whole_tile_map.at(i).at(j)->texture_ = texture2;
		}
	}*/

	return true;
}

void EditScene::_Release()
{
}

void EditScene::_Input(float time)
{
}

void EditScene::_Update(float time)
{
}

void EditScene::_LateUpdate(float time)
{
}

void EditScene::_Collision(float time)
{
}

void EditScene::_Render(HDC device_context, float time)
{
	//Rectangle(device_context, 0, 0, 1280, 720);

	//auto& whole_tile_map = IsometricTileMapEditor::instance()->whole_tile_map();

	//for (auto i = 0; i < whole_tile_map.size(); ++i)
	//{
	//	for (auto j = 0; j < whole_tile_map.at(0).size(); ++j)
	//	{
	//		//TransparentBlt(device_context, left, top, width, height, caching_texture->memory_device_context(), 0, 0, caching_texture->width(), caching_texture->height(), color_key_);
	//		TransparentBlt(device_context, 640 + 65 * j - 65 * i, -100 + 33 * i + 33 * j, 128, 192, whole_tile_map.at(i).at(j)->texture_.lock()->memory_device_context(), 0, 0, 128, 192, RGB(224, 32, 64));
	//	}
	//}
}