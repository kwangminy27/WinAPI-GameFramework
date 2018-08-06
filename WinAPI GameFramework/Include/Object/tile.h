#pragma once

#include "object.h"

class Tile : public Object
{
	friend class ObjectManager;
	friend class Stage;
public:
	virtual bool Initialize();
	void RenderOptionTile(HDC device_context, float time);

	TILE_TYPE type() const;
	TILE_OPTION option() const;
	std::pair<int, int> const& idx() const;

	void set_type(TILE_TYPE type);
	void set_option(TILE_OPTION option);
	void set_idx(std::pair<int, int> const& idx);

protected:
	Tile() = default;
	Tile(Tile const& other);
	Tile(Tile&& other) noexcept;
	Tile& operator=(Tile const&) = default;
	Tile& operator=(Tile&&) noexcept = default;
	virtual ~Tile() = default;

	virtual void _Release() override;

	virtual void _Input(float time);
	virtual void _Update(float time);
	virtual void _LateUpdate(float time);
	virtual void _Collision(float time);
	virtual void _Render(HDC device_context, float time);

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	TILE_TYPE type_{ TILE_TYPE::NORMAL };
	TILE_OPTION option_{ TILE_OPTION::NONE };
	std::pair<int, int> idx_{};
	std::shared_ptr<Texture> option_tile_{};
};