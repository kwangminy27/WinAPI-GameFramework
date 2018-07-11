#pragma once

#include "object.h"

class Bullet : public Object
{
	friend class ObjectManager;
public:
	void set_move_speed(float move_speed);
	void set_dir(XY dir);

protected:
	Bullet() = default;
	Bullet(Bullet const& other);

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	float move_speed_{};
	XY dir_{};
};

