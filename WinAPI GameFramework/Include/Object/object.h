#pragma once

#include "../tag.h"

class Object : public Tag
{
	friend class Layer;
public:
	Object() = default;
	virtual ~Object() = default;
protected:
	Object(Object const& other);

	virtual void _Release() override = 0;

	virtual bool _Initialize() = 0;
	virtual void _Input(float time) = 0;
	virtual void _Update(float time) = 0;
	virtual void _LateUpdate(float time) = 0;
	virtual void _Collision(float time) = 0;
	virtual void _Render(HDC device_context, float time) = 0;
	virtual std::unique_ptr<Object, std::function<void(void*)>> _Clone() = 0;
};