//#pragma once
//
//#include "singleton.h"
//
//class Texture;
//
//struct Tile
//{
//	bool movable_flag_{};
//	std::weak_ptr<Texture> texture_{};
//	std::list<std::weak_ptr<Tile>> adjacent_tile_list_{};
//};
//
//class IsometricTileMapEditor final : public Singleton<IsometricTileMapEditor>
//{
//	friend class Singleton<IsometricTileMapEditor>;
//public:
//	bool Initialize();
//
//	std::vector<std::vector<std::shared_ptr<Tile>>>& whole_tile_map();
//
//	void set_width(int width);
//	void set_height(int height);
//	void set_size(XY const& size);
//
//private:
//	IsometricTileMapEditor() = default;
//	IsometricTileMapEditor(IsometricTileMapEditor const&) = delete;
//	IsometricTileMapEditor& operator=(IsometricTileMapEditor const&) = delete;
//
//	virtual void _Release() override;
//
//	int width_{};
//	int height_{};
//	XY size_{};
//
//	std::vector<std::vector<std::shared_ptr<Tile>>> whole_tile_map_{};
//};