#pragma once

#include "object.h"

class Character : public Object
{
public:
	float move_speed() const;
	void set_move_speed(float move_speed);

protected:
	Character() = default;
	Character(Character const& other);

	virtual void _Release() override = 0;

	virtual bool _Initialize() override = 0;
	virtual void _Input(float time) override = 0;
	virtual void _Update(float time) override = 0;
	virtual void _LateUpdate(float time) override = 0;
	virtual void _Collision(float time) override = 0;
	virtual void _Render(HDC device_context, float time) override = 0;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override = 0;

	float move_speed_{};
};