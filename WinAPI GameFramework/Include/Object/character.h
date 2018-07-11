#pragma once

#include "object.h"

class Character : public Object
{
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

	virtual std::unique_ptr<Object, std::function<void(void*)>> _Clone() override = 0;
};