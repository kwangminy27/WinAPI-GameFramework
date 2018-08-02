#pragma once

#include "ui.h"

class ButtonUI : public UI
{
	friend class ObjectManager;
public:
	void set_state(BUTTON_STATE state);
	void set_callback(std::function<void(float)> const& callback);

protected:
	ButtonUI() = default;
	ButtonUI(ButtonUI const& other);
	ButtonUI(ButtonUI&& other) noexcept;
	ButtonUI& operator=(ButtonUI const&) = default;
	ButtonUI& operator=(ButtonUI&&) noexcept = default;

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;
	
	void _OnCollisionEnter(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);
	void _OnCollision(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);
	void _OnCollisionLeave(std::weak_ptr<Collider> const& src, std::weak_ptr<Collider> const& dest, float time);

	BUTTON_STATE state_{};
	std::list<std::function<void(float)>> callback_list_{};
};