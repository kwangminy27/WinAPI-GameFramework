#pragma once

#include "../tag.h"

class Scene;
class Layer;

class Object : public Tag
{
	friend class Layer;
	friend class ObjectManager;
public:
	XY position() const;
	XY size() const;
	XY pivot() const;

	void set_position(float x, float y);
	void set_position(XY const& xy);
	void set_size(float x, float y);
	void set_size(XY const& xy);
	void set_pivot(float x, float y);
	void set_pivot(XY const& xy);

	std::shared_ptr<Scene> scene() const;
	std::shared_ptr<Layer> layer() const;

	void set_scene(std::shared_ptr<Scene> const& scene);
	void set_layer(std::shared_ptr<Layer> const& layer);

	void Move(float x, float y);
	void Move(float x, float y, float time);
	void Move(XY xy);
	void Move(XY xy, float time);

protected:
	Object() = default;
	Object(Object const& other);
	virtual ~Object() = default;

	virtual void _Release() override = 0;

	virtual bool _Initialize() = 0;
	virtual void _Input(float time) = 0;
	virtual void _Update(float time) = 0;
	virtual void _LateUpdate(float time) = 0;
	virtual void _Collision(float time) = 0;
	virtual void _Render(HDC device_context, float time) = 0;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() = 0;

	XY position_{};
	XY size_{};
	XY pivot_{};
	std::weak_ptr<Scene> scene_{};
	std::weak_ptr<Layer> layer_{};
};