#pragma once

#include "../tag.h"

class Object;

class Collider : public Tag, public std::enable_shared_from_this<Collider>
{
	friend class Object;
	friend class ObjectManager;
	friend class ColliderManager;
public:
	static HBRUSH green_brush_;
	static HBRUSH red_brush_;

	COLLIDER collider_type() const;
	std::string const& collision_group_tag() const;
	std::shared_ptr<Object> object() const;
	void set_pivot(XY const& xy);
	void set_collision_group_tag(std::string const& tag);
	void set_object(std::weak_ptr<Object> const& object);

protected:
	Collider() = default;
	Collider(Collider const& other);
	Collider(Collider&& other) noexcept;
	Collider& operator=(Collider const&) = default;
	Collider& operator=(Collider&&) noexcept = default;
	virtual ~Collider() = default;

	virtual void _Release() override;

	virtual bool _Initialize();
	virtual void _Update(float time);
	virtual void _Render(HDC device_context, float time);

	virtual std::unique_ptr<Collider, std::function<void(Collider*)>>_Clone() = 0;

	COLLIDER collider_type_{};
	XY pivot_{};
	XY size_{};
	std::string collision_group_tag_{ "Default" };
	std::weak_ptr<Object> object_{};
};