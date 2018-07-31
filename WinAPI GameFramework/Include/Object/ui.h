#pragma once

#include "object.h"

class UI : public Object
{
	friend class ObjectManager;
public:
	void set_offset(XY const& offset);

protected:
	UI() = default;
	UI(UI const& other);
	UI(UI&& other) noexcept;
	UI& operator=(UI const&) = default;
	UI& operator=(UI&&) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() = 0;

	XY offset_{};
};