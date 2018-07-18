#pragma once

#include "object.h"

class Bullet : public Object
{
	friend class ObjectManager;
public:
	void set_range(float range);
	void stop();
	void start();

protected:
	Bullet() = default;
	Bullet(Bullet const& other);
	Bullet(Bullet&& other) noexcept;
	Bullet& operator=(Bullet const&) = default;
	Bullet& operator=(Bullet&&) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	float range_{};
	bool move_{ true };
};