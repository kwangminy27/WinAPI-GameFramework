#include "player.h"

using namespace std;

Player::Player(Player const& other) : Character(other)
{
}

void Player::_Release()
{
}

bool Player::_Initialize()
{
	return true;
}

void Player::_Input(float time)
{
}

void Player::_Update(float time)
{
}

void Player::_LateUpdate(float time)
{
}

void Player::_Collision(float time)
{
}

void Player::_Render(HDC device_context, float time)
{
}

unique_ptr<Object, function<void(void*)>> Player::_Clone()
{
	return unique_ptr<Object, function<void(void*)>>(new Player(*this), [](void* p) {
		static_cast<Player*>(p)->_Release();
		delete p;
	});
}
