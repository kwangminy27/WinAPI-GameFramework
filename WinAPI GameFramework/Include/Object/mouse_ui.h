#pragma once

#include "ui.h"

class MouseUI : public UI
{
	friend class Input;
	friend class ObjectManager;
public:
	virtual bool Initialize() override;

private:
	MouseUI() = default;
	MouseUI(MouseUI const& other);
	MouseUI(MouseUI&& other) noexcept;
	MouseUI& operator=(MouseUI const&) = default;
	MouseUI& operator=(MouseUI&&) noexcept = default;

	virtual void _Release() override;

	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;
};