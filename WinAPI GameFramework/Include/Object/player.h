#pragma once

#include "character.h"

class Bullet;

class Player final : public Character
{
	friend class ObjectManager;
public:
	float barrel_size() const;
	void set_barrel_size(float barrel_size);
	void BulletHit(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);

private:
	Player() = default;
	Player(Player const& other);
	Player(Player&& other) noexcept;
	Player& operator=(Player const&) = default;
	Player& operator=(Player&&) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	float barrel_size_{};
	std::shared_ptr<Bullet> bullet_{};
};
