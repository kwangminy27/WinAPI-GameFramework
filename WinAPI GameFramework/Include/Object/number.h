#pragma once

#include "object.h"

class Number : public Object
{
	friend class ObjectManager;
public:
	virtual bool Initialize() override;

	void set_number(int number);
	void AddNumber(int value);

	void set_offset(XY const& offset);

protected:
	Number() = default;
	Number(Number const& other);
	Number(Number&& other) noexcept;
	Number& operator=(Number const&) = default;
	Number& operator=(Number&&) noexcept = default;

	virtual void _Release() override;

	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;
	
	std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	int number_{};
	std::vector<int> number_slot_{};

	XY offset_{};
};