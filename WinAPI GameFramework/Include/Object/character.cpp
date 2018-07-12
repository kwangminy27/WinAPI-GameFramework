#include "character.h"

using namespace std;

float Character::move_speed() const
{
	return move_speed_;
}

void Character::set_move_speed(float move_speed)
{
	move_speed_ = move_speed;
}

Character::Character(Character const& other) : Object(other)
{
	move_speed_ = other.move_speed_;
}

bool Character::_Initialize()
{
	return true;
}

void Character::_Input(float time)
{
}

void Character::_Update(float time)
{
}

void Character::_LateUpdate(float time)
{
}

void Character::_Collision(float time)
{
}

void Character::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}
