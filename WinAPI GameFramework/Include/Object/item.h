#pragma once

#include "object.h"

class Item : public Object
{
	friend class ObjectManager;
public:
	float life_time() const;
	void set_life_time(float time);

protected:
	Item() = default;
	Item(Item const& other);
	Item(Item&& other) noexcept;
	Item& operator=(Item const&) = default;
	Item& operator=(Item&&) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	float life_time_{};
};