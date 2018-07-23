#pragma once

#include "collider.h"

class ColliderPixel final : public Collider
{
	friend class Object;
public:
	PIXEL_INFO const& world() const;
	void set_model(std::wstring file_name, std::string path_tag);
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

	PIXEL_INFO model_{};
	PIXEL_INFO world_{};
};