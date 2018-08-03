#pragma once

#include "bullet.h"

class ParabolaBullet : public Bullet
{
	friend class ObjectManager;
public:
	virtual bool Initialize() override;

	float start_angle() const;
	void set_start_angle(float angle);

private:
	ParabolaBullet() = default;
	ParabolaBullet(ParabolaBullet const& other);
	ParabolaBullet(ParabolaBullet&& other) noexcept;
	ParabolaBullet& operator=(ParabolaBullet const&) = default;
	ParabolaBullet& operator=(ParabolaBullet&&) noexcept = default;

	virtual void _Release() override;

	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	float start_angle_{};
};