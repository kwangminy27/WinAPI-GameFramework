#pragma once

#include "tile.h"

class IsometricTile : Tile
{
	friend class ObjectManager;
public:
	virtual bool Initialize();

protected:
	IsometricTile() = default;
	IsometricTile(IsometricTile const& other);
	IsometricTile(IsometricTile&& other) noexcept;
	IsometricTile& operator=(IsometricTile const&) = default;
	IsometricTile& operator=(IsometricTile&&) noexcept = default;
	virtual ~IsometricTile() = default;

	virtual void _Release() override;

	virtual void _Input(float time);
	virtual void _Update(float time);
	virtual void _LateUpdate(float time);
	virtual void _Collision(float time);
	virtual void _Render(HDC device_context, float time);

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;
};