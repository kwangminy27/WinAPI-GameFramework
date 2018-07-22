#pragma once

#include "collider.h"

class ColliderPoint final : public Collider
{
	friend class Object;
public:
	XY world() const;
	void set_model(XY const& model);
	virtual bool Collision(std::weak_ptr<Collider> const& dest) override;

private:
	ColliderPoint() = default;
	ColliderPoint(ColliderPoint const& other);
	ColliderPoint(ColliderPoint&& other) noexcept;
	ColliderPoint& operator=(ColliderPoint const& other) = default;
	ColliderPoint& operator=(ColliderPoint&& other) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Update(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Collider, std::function<void(Collider*)>> _Clone() override;

	XY model_{};
	XY world_{};
};