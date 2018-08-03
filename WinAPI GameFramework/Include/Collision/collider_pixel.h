#pragma once

#include "collider.h"

class ColliderPixel final : public Collider
{
	friend class Object;
public:
	XY const& world() const;
	PIXEL24 const& comparision_pixel() const;
	std::shared_ptr<PIXEL24_INFO> pixel_collider() const;

	void set_world(XY const& xy);
	void set_comparision_pixel(PIXEL24 const& pixel);
	void set_pixel_collider(std::string const& tag);

	virtual bool Collision(std::weak_ptr<Collider> const& dest) override;
	virtual void Render(HDC device_context, float time) override;

private:
	ColliderPixel() = default;
	ColliderPixel(ColliderPixel const& other);
	ColliderPixel(ColliderPixel&& other) noexcept;
	ColliderPixel& operator=(ColliderPixel const& other) = default;
	ColliderPixel& operator=(ColliderPixel&& other) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Update(float time) override;

	virtual std::unique_ptr<Collider, std::function<void(Collider*)>> _Clone() override;

	std::weak_ptr<PIXEL24_INFO> pixel_collider_{};
};