#pragma once

#include "../tag.h"

class Scene;
class Layer;
class Texture;

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

	void set_scene(std::weak_ptr<Scene> const& scene);
	void set_layer(std::weak_ptr<Layer> const& layer);
	bool set_texture(std::string const& tag, std::wstring const& file_name, std::string const& path_tag);
	bool set_texture(std::string const& tag);
	bool set_texture(std::weak_ptr<Texture> const& texture);

	void Move(float x, float y);
	void Move(float x, float y, float time);
	void Move(XY xy);
	void Move(XY xy, float time);

protected:
	Object() = default;
	Object(Object const& other);
	virtual ~Object() = default;

	virtual void _Release() override = 0;

	virtual bool _Initialize();
	virtual void _Input(float time);
	virtual void _Update(float time);
	virtual void _LateUpdate(float time);
	virtual void _Collision(float time);
	virtual void _Render(HDC device_context, float time);

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() = 0;

	XY position_{};
	XY size_{};
	XY pivot_{};
	std::weak_ptr<Scene> scene_{};
	std::weak_ptr<Layer> layer_{};
	std::weak_ptr<Texture> texture_{};
};