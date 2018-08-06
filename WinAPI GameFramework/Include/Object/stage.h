#pragma once

#include "object.h"

class Stage : public Object
{
	friend class ObjectManager;
public:
	virtual bool Initialize() override;

	XY const& map_size() const;
	int idx_width() const;
	int idx_height() const;
	XY const& tile_size() const;
	bool tile_option_flag() const;

	void set_map_size(XY const& size);
	void set_idx_width(int width);
	void set_idx_height(int height);
	void set_tile_size(XY const& size);
	void set_tile_option_flag(bool flag);

	void CreateGrid(TILE_TYPE type, int idx_width, int idx_height, XY const& map_size, std::string const& tag, std::wstring const& file_name, std::string path_tag = "TexturePath");

	std::shared_ptr<Object>& GetTile(float x, float y);

	void BeAttached(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);
	void BeDetached(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);

private:
	Stage() = default;
	Stage(Stage const& other);
	Stage(Stage&& other) noexcept;
	Stage& operator=(Stage const&) = default;
	Stage& operator=(Stage&&) noexcept = default;

	virtual void _Release() override;

	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	XY map_size_{};
	int idx_width_{};
	int idx_height_{};
	XY tile_size_{};
	std::pair<int, int> idx_view_x_range_{};
	std::pair<int, int> idx_view_y_range_{};
	bool tile_option_flag_{};
	std::vector<std::vector<std::shared_ptr<Object>>> tile_collection_{};
};