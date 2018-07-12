#pragma once

#include "character.h"

class Monster final : public Character
{
	friend class ObjectManager;
public:
	float move_dir() const;
	float fire_time() const;

	void set_move_dir(float move_dir);
	void set_fire_time(float fire_time);

private:
	Monster() = default;
	Monster(Monster const& other);

	virtual void _Release() override;

	virtual bool _Initialize() override;
	virtual void _Input(float time) override;
	virtual void _Update(float time) override;
	virtual void _LateUpdate(float time) override;
	virtual void _Collision(float time) override;
	virtual void _Render(HDC device_context, float time) override;

	virtual std::unique_ptr<Object, std::function<void(Object*)>> _Clone() override;

	float move_dir_{};
	float fire_time_{};
};

