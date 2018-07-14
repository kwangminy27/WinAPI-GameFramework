#pragma once

#include "bullet.h"

class RotationBullet final : public Bullet
{
	friend class ObjectManager;
public:
	XY rotation_center() const;
	float rotation_range() const;
	float rotation_angle() const;

	void set_rotation_center(XY const& rotation_centor);
	void set_rotation_range(float rotation_range);
	void set_rotation_angle(float rotation_angle);

private:
	RotationBullet() = default;
	RotationBullet(RotationBullet const& other);

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	XY rotation_center_{};
	float rotation_range_{};
	float rotation_angle_{};
};