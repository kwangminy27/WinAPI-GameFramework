#pragma once

#include "singleton.h"

class Object;

class Camera final : public Singleton<Camera>
{
	friend class Singleton<Camera>;
public:
	bool Initialize();
	void Update(float time);
	void Move(float x, float y, float time);

	XY const& world() const;
	XY const& view_size() const;
	XY const& pivot() const;
	XY const& map_size() const;
	std::shared_ptr<Object> target() const;

	void set_view_size(XY const& xy);
	void set_pivot(XY const& xy);
	void set_map_size(XY const& xy);
	void set_target(std::weak_ptr<Object> const& object);
private:
	Camera() = default;
	Camera(Camera const&) = delete;
	Camera& operator=(Camera const&) = delete;

	virtual void _Release() override;

	XY world_{};
	XY view_size_{};
	XY pivot_{};
	XY map_size_{};

	std::weak_ptr<Object> target_{};
};