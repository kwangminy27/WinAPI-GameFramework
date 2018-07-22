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
	static HPEN green_pen_;
	static HPEN red_pen_;
	HBRUSH brush_;
	HPEN pen_;
	HPEN old_pen_;


	COLLIDER collider_type() const;
	std::string const& collision_group_tag() const;
	std::shared_ptr<Object> object() const;
	void set_pivot(XY const& xy);
	void set_collision_group_tag(std::string const& tag);
	void set_object(std::weak_ptr<Object> const& object);

	virtual bool Collision(std::shared_ptr<Collider> const& dest) = 0;

	void SetCallBack(std::function<void(std::weak_ptr<Collider>, std::weak_ptr<Collider>, float)> function, COLLISION_CALLBACK type);
	template <typename T> void SetCallBack(T* object, void (T::*function)(std::weak_ptr<Collider>, std::weak_ptr<Collider>, float), COLLISION_CALLBACK type);

	void OnCollisionEnter(std::weak_ptr<Collider> const& dest, float time);
	void OnCollision(std::weak_ptr<Collider> const& dest, float time);
	void OnCollisionLeave(std::weak_ptr<Collider> const& dest, float time);

	bool IsCollidedCollider(std::weak_ptr<Collider> const& collider);
	void AddCollidedCollider(std::weak_ptr<Collider> const& collider);
	void RemoveCollidedCollider();

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

	bool _CollisionBetweenRectAndRect(LTRB const& src, LTRB const& dest);
	bool _CollisionBetweenSphereAndSphere(SPHERE const& src, SPHERE const& dest);
	bool _CollisionBetweenRectAndSphere(LTRB const& src, SPHERE const& dest);

	COLLIDER collider_type_{};
	XY pivot_{};
	XY size_{};
	std::string collision_group_tag_{ "Default" };
	std::array<std::list<std::function<void(std::weak_ptr<Collider>, std::weak_ptr<Collider>, float)>>, static_cast<size_t>(COLLISION_CALLBACK::END)> collision_callback_collection_{};
	std::list<std::weak_ptr<Collider>> collided_collider_list_{};
	std::weak_ptr<Object> object_{};
};

#include "collider.inl"