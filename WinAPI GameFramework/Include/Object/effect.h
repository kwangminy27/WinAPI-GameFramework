#pragma once

#include "object.h"

class Effect : public Object
{
	friend class ObjectManager;
public:
	virtual bool Initialize() override;

	float life_time() const;
	float range() const;
	std::shared_ptr<Object> target() const;

	void set_life_time(float time);
	void set_range(float range);
	void set_target(std::weak_ptr<Object> const& target);

private:
	Effect() = default;
	Effect(Effect const& other);
	Effect(Effect&& other) noexcept;
	Effect& operator=(Effect const&) = default;
	Effect& operator=(Effect&&) noexcept = default;

	virtual void _Release() override;

	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	float life_time_{};
	float range_{};
	std::weak_ptr<Object> target_{};
};