#pragma once

#include "object.h"

class Stage : public Object
{
	friend class ObjectManager;
public:
	XY const& map_size() const;
	void set_map_size(XY const& size);

	void BeAttached(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);
	void BeDetached(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);

private:
	Stage() = default;
	Stage(Stage const& other);
	Stage(Stage&& other) noexcept;
	Stage& operator=(Stage const&) = default;
	Stage& operator=(Stage&&) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	XY map_size_{};
};