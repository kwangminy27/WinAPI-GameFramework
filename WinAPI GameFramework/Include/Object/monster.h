#pragma once

#include "character.h"

class Monster final : public Character
{
	friend class ObjectManager;
public:
	float move_dir() const;
	float fire_time() const;
	float attack_range() const;
	std::shared_ptr<Object> target() const;

	void set_move_dir(float move_dir);
	void set_fire_time(float fire_time);
	void set_attack_range(float attack_range);
	void set_target(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);
	void release_target(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);

	void BeHit(weak_ptr<Collider> const& src, weak_ptr<Collider> const& dest, float time);

private:
	Monster() = default;
	Monster(Monster const& other);
	Monster(Monster&& other) noexcept;
	Monster& operator=(Monster const&) = default;
	Monster& operator=(Monster&&) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	float move_dir_{};
	float fire_time_{};
	float attack_range_{};

	std::weak_ptr<Object> target_{};
};

