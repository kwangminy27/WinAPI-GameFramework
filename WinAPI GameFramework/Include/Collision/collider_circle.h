#pragma once

#include "collider.h"

class ColliderCircle final : public Collider
{
	friend class Object;
public:
	CIRCLE_INFO const& world() const;
	void set_model(CIRCLE_INFO const& model);

	virtual bool Collision(std::weak_ptr<Collider> const& dest) override;
	virtual void Render(HDC device_context, float time) override;

private:
	ColliderCircle() = default;
	ColliderCircle(ColliderCircle const& other);
	ColliderCircle(ColliderCircle&& other) noexcept;
	ColliderCircle& operator=(ColliderCircle const& other) = default;
	ColliderCircle& operator=(ColliderCircle&& other) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Update(float time) override;

	virtual std::unique_ptr<Collider, std::function<void(Collider*)>> _Clone() override;

	CIRCLE_INFO model_{};
	CIRCLE_INFO world_{};
};