#pragma once

#include "object.h"

class Character : public Object
{
protected:
	Character() = default;
	Character(Character const& other);
	Character(Character&& other) noexcept;
	Character& operator=(Character const&) = default;
	Character& operator=(Character&&) noexcept = default;

	virtual void _Release() override = 0;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override = 0;
};