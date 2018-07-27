#pragma once

#include "../tag.h"

class Scene;
class Layer;
class Texture;
class Collider;

class Object : public Tag, public std::enable_shared_from_this<Object>
{
	friend class Layer;
	friend class ObjectManager;
public:
	XY position() const;
	XY size() const;
	XY pivot() const;
	float angle() const;
	float move_speed() const;
	float rotation_speed() const;
	COLORREF color_key() const;
	bool is_color_key() const;

	bool physics_flag() const;
	float velocity() const;
	float energy() const;

	void set_position(float x, float y);
	void set_position(XY const& xy);
	void set_size(float x, float y);
	void set_size(XY const& xy);
	void set_pivot(float x, float y);
	void set_pivot(XY const& xy);
	void set_angle(float angle);
	void set_move_speed(float move_speed);
	void set_rotation_speed(float rotation_speed);
	void set_color_key(COLORREF color_key);

	void set_physics_flag(bool flag);
	void set_velocity(float velocity);
	void set_energy(float energy);

	std::list<std::shared_ptr<Collider>> const& collider_collection() const;

	std::shared_ptr<Scene> scene() const;
	std::shared_ptr<Layer> layer() const;

	void set_scene(std::weak_ptr<Scene> const& scene);
	void set_layer(std::weak_ptr<Layer> const& layer);
	void set_texture(std::weak_ptr<Texture> const& texture);
	bool set_texture(std::string const& tag, std::wstring const& file_name, std::string const& path_tag);
	bool set_texture(std::string const& tag);

	void Move(float x, float y);
	void Move(float x, float y, float time);
	void Move(XY xy);
	void Move(XY xy, float time);
	void MoveByAngle(float time);
	void Rotate(float time);

	template <typename T> std::shared_ptr<Collider> AddCollider(std::string tag);

protected:
	Object() = default;
	Object(Object const& other);
	Object(Object&& other) noexcept;
	Object& operator=(Object const&) = default;
	Object& operator=(Object&&) noexcept = default;
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
	float angle_{};
	float move_speed_{};
	float rotation_speed_{};
	COLORREF color_key_{};
	bool is_color_key_{};

	bool physics_flag_{};
	float velocity_{};
	float energy_{};

	std::shared_ptr<Collider> collider_nullptr_{};
	std::list<std::shared_ptr<Collider>> collider_collection_{};

	std::weak_ptr<Scene> scene_{};
	std::weak_ptr<Layer> layer_{};
	std::weak_ptr<Texture> texture_{};
};

#include "object.inl"