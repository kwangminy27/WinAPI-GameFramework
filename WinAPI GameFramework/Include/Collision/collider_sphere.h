#pragma once

#include "collider.h"

class ColliderSphere final : public Collider
{
	friend class Object;
public:
	SPHERE world() const;
	void set_model(SPHERE const& model);
	virtual bool Collision(std::shared_ptr<Collider> const& dest) override;

private:
	ColliderSphere() = default;
	ColliderSphere(ColliderSphere const& other);
	ColliderSphere& operator=(ColliderSphere const& other) = default;
	ColliderSphere(ColliderSphere&& other) noexcept;
	ColliderSphere& operator=(ColliderSphere&& other) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Update(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Collider, std::function<void(Collider*)>> _Clone() override;

	SPHERE model_{};
	SPHERE world_{};
};