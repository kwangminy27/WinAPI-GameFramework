#pragma once

#include "ui.h"

class ButtonUI final : public UI
{
	friend class ObjectManager;
private:
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
};