#include "character.h"

using namespace std;

Character::Character(Character const& other) : Object(other)
{
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
