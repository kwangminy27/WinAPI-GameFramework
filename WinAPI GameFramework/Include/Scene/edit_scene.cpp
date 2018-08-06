#include "../core.h"
#include "edit_scene.h"
#include "scene.h"
#include "layer.h"
#include "../input.h"
#include "../path_manager.h"
#include "../camera.h"
#include "../Object/object_manager.h"
#include "../Object/player.h"
#include "../Object/stage.h"
#include "../Object/tile.h"
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
	stage->CreateGrid(TILE_TYPE::NORMAL, 100, 100, { 5200.f, 5200.f }, "Base", L"Tile/BaseTile.bmp");
	camera->set_map_size(stage->map_size());

	Input::instance()->AddKey("GridToggle"s, 'G');
	Input::instance()->AddKey("MakeBlocked"s, VK_LBUTTON);
	Input::instance()->AddKey("MakeNone"s, VK_RBUTTON);
	Input::instance()->AddKey("Save"s, VK_CONTROL, 'S');
	Input::instance()->AddKey("Load"s, VK_CONTROL, 'O');

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

void EditScene::SaveStageFile(wstring const& file_name)
{
}

void EditScene::LoadStageFile(wstring const& file_name)
{
}

void EditScene::_Release()
{
}

void EditScene::_Input(float time)
{
	auto const& input_manager = Input::instance();
	auto const& camera = Camera::instance();
	auto stage = dynamic_pointer_cast<Stage>((*(ObjectManager::instance()->FindObjects("Stage").first)).second.lock());

	static auto const& KeyPush = [&input_manager](string const& tag) -> bool { return input_manager->KeyPush(tag); };
	static auto const& KeyPressed = [&input_manager](string const& tag) -> bool { return input_manager->KeyPressed(tag); };
	static auto const& KeyUp = [&input_manager](string const& tag) -> bool { return input_manager->KeyUp(tag); };

	if (KeyPressed("MoveLeft"))
		camera->Move(-800.f, 0.f, time);

	if (KeyPressed("MoveRight"))
		camera->Move(800.f, 0.f, time);

	if (KeyPressed("MoveUp"))
		camera->Move(0.f, -800.f, time);

	if (KeyPressed("MoveDown"))
		camera->Move(0.f, 800.f, time);

	if (KeyPush("GridToggle"))
		stage->set_tile_option_flag(stage->tile_option_flag() ^ true);

	if (KeyPressed("MakeBlocked"))
	{
		XY mouse_world_position = Input::instance()->mouse_client_position() + Camera::instance()->world();
		auto tile = dynamic_pointer_cast<Tile>(stage->GetTile(mouse_world_position.x, mouse_world_position.y));
		tile->set_texture("Rock", L"Tile/RockTile.bmp");
		tile->set_option(TILE_OPTION::BLOCKED);
	}

	if (KeyPressed("MakeNone"))
	{
		XY mouse_world_position = Input::instance()->mouse_client_position() + Camera::instance()->world();
		auto tile = dynamic_pointer_cast<Tile>(stage->GetTile(mouse_world_position.x, mouse_world_position.y));
		tile->set_texture("Base", L"Tile/RockTile.bmp");
		tile->set_option(TILE_OPTION::NONE);
	}

	if (KeyPush("Save"))
	{
		OPENFILENAME open_file_name{};
		open_file_name.lStructSize = sizeof(OPENFILENAME);
		open_file_name.hwndOwner = Core::instance()->main_window();
		open_file_name.lpstrFilter = L"Every File(*.*)\0*.*\0Stage File\0*.stg\0";

		wchar_t file_name[MAX_PATH]{};
		open_file_name.lpstrFile = file_name;
		open_file_name.nMaxFile = MAX_PATH;

		filesystem::path path_buffer = PathManager::instance()->FindPath("RootPath");
		wstring wstring_buffer = path_buffer.wstring();
		wchar_t const* initial_directory = wstring_buffer.c_str();

		open_file_name.lpstrInitialDir = initial_directory;

		ShowCursor(true);
		if (GetSaveFileName(&open_file_name))
			SaveStageFile(file_name);
		ShowCursor(false);
	}

	if (KeyPush("Load"))
	{
		OPENFILENAME open_file_name{};
		open_file_name.lStructSize = sizeof(OPENFILENAME);
		open_file_name.hwndOwner = Core::instance()->main_window();
		open_file_name.lpstrFilter = L"Every File(*.*)\0*.*\0Stage File\0*.stg\0";

		wchar_t file_name[MAX_PATH]{};
		open_file_name.lpstrFile = file_name;
		open_file_name.nMaxFile = MAX_PATH;

		filesystem::path path_buffer = PathManager::instance()->FindPath("RootPath");
		wstring wstring_buffer = path_buffer.wstring();
		wchar_t const* initial_directory = wstring_buffer.c_str();

		open_file_name.lpstrInitialDir = initial_directory;

		ShowCursor(true);
		if (GetOpenFileName(&open_file_name))
			LoadStageFile(file_name);
		ShowCursor(false);
	}
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