#pragma once

#include "object.h"

class Bar : public Object
{
	friend class ObjectManager;
public:
	virtual bool Initialize() override;

	void set_range(XY const& range);
	void set_value(float value);
	void set_cutting_direction(BAR_CUTTING_DIRECTION direction);

	void AddValue(float value);

protected:
	Bar() = default;
	Bar(Bar const& other);
	Bar(Bar&& other) noexcept;
	Bar& operator=(Bar const&) = default;
	Bar& operator=(Bar&&) noexcept = default;

	virtual void _Release() override;

	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	XY range_{};
	float value_{};
	BAR_CUTTING_DIRECTION cutting_direction_{ BAR_CUTTING_DIRECTION::LEFT };
};