#pragma once

#include "collider.h"

class ColliderRect final : public Collider
{
	friend class Object;
public:
	LTRB world() const;
	void set_model(LTRB const& ltrb);
	virtual bool Collision(std::shared_ptr<Collider> const& dest) override;

private:
	ColliderRect() = default;
	ColliderRect(ColliderRect const& other);
	ColliderRect& operator=(ColliderRect const& other) = default;
	ColliderRect(ColliderRect&& other) noexcept;
	ColliderRect& operator=(ColliderRect&& other) noexcept = default;
	virtual ~ColliderRect() = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Update(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Collider, std::function<void(Collider*)>> _Clone() override;

	LTRB model_{};
	LTRB world_{};
};
