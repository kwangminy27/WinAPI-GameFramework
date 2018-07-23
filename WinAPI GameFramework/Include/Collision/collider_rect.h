#pragma once

#include "collider.h"

class ColliderRect final : public Collider
{
	friend class Object;
public:
	RECT_INFO const& world() const;
	void set_model(RECT_INFO const& model);
	virtual bool Collision(std::weak_ptr<Collider> const& dest) override;

private:
	ColliderRect() = default;
	ColliderRect(ColliderRect const& other);
	ColliderRect(ColliderRect&& other) noexcept;
	ColliderRect& operator=(ColliderRect const& other) = default;
	ColliderRect& operator=(ColliderRect&& other) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Update(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Collider, std::function<void(Collider*)>> _Clone() override;

	RECT_INFO model_{};
	RECT_INFO world_{};
};
