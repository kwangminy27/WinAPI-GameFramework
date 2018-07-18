#include "character.h"

using namespace std;

Character::Character(Character const& other) : Object(other)
{
}

Character::Character(Character&& other) noexcept : Object(other)
{
}

bool Character::_Initialize()
{
	return true;
}

void Character::_Input(float time)
{
	Object::_Input(time);
}

void Character::_Update(float time)
{
	Object::_Update(time);
}

void Character::_LateUpdate(float time)
{
	Object::_LateUpdate(time);
}

void Character::_Collision(float time)
{
	Object::_Collision(time);
}

void Character::_Render(HDC device_context, float time)
{
	Object::_Render(device_context, time);
}
