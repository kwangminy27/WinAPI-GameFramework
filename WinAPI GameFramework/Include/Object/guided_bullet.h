#pragma once

#include "bullet.h"

class GuidedBullet final : public Bullet
{
	friend class ObjectManager;
public:
	bool is_guided() const;
	std::shared_ptr<Object> target() const;

	void set_target(std::weak_ptr<Object> const& target);

private:
	GuidedBullet() = default;
	GuidedBullet(GuidedBullet const& other);
	GuidedBullet(GuidedBullet&& other) noexcept;
	GuidedBullet& operator=(GuidedBullet const&) = default;
	GuidedBullet& operator=(GuidedBullet&&) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	bool is_guided_{};
	std::weak_ptr<Object> target_{};
};

