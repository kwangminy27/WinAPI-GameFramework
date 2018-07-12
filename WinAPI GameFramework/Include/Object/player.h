#pragma once

#include "character.h"

class Bullet;

class Player final : public Character
{
	friend class ObjectManager;
private:
	Player() = default;
	Player(Player const& other);

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	std::shared_ptr<Bullet> bullet_{};
};