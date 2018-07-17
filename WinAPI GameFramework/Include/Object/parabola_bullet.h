#pragma once

#include "bullet.h"

class ParabolaBullet : public Bullet
{
	friend class ObjectManager;
public:
	float start_angle() const;
	void set_start_angle(float angle);

private:
	ParabolaBullet() = default;
	ParabolaBullet(ParabolaBullet const& other);

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	float start_angle_{};
};