#pragma once

#include "collider.h"

class ColliderPixel final : public Collider
{
	friend class Object;
public:
	std::vector<std::vector<PIXEL24>> const& collision_pixel_collection() const;
	PIXEL24 const& comparision_pixel() const;

	void set_collision_pixel_collection(std::wstring const& file_name, std::string const& path_tag);
	void set_comparision_pixel(PIXEL24 const& pixel);

	virtual bool Collision(std::weak_ptr<Collider> const& dest) override;

private:
	ColliderPixel() = default;
	ColliderPixel(ColliderPixel const& other);
	ColliderPixel(ColliderPixel&& other) noexcept;
	ColliderPixel& operator=(ColliderPixel const& other) = default;
	ColliderPixel& operator=(ColliderPixel&& other) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Update(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Collider, std::function<void(Collider*)>> _Clone() override;

	std::vector<std::vector<PIXEL24>> collision_pixel_collection_{};
	PIXEL24 comparision_pixel_{};
};