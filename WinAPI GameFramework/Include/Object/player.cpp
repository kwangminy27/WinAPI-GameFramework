#include "player.h"
#include "../input.h"
#include "../Scene/scene.h"
#include "object_manager.h"

using namespace std;

Player::Player(Player const& other) : Character(other)
{
}

void Player::_Release()
{
}

bool Player::_Initialize()
{
	set_move_speed(300.f);

	return true;
}

void Player::_Input(float time)
{
	auto const& input_manager = Input::instance();

	static auto KeyPush = [&input_manager](string tag) -> bool { return input_manager->KeyPush(tag); };
	static auto KeyPressed = [&input_manager](string tag) -> bool { return input_manager->KeyPressed(tag); };
	static auto KeyUp = [&input_manager](string tag) -> bool { return input_manager->KeyUp(tag); };

	if (KeyPressed("MoveUp"s))
		Move(0.f, -move_speed_ * time);

	if (KeyPressed("MoveDown"s))
		Move(0.f, move_speed_ * time);

	if (KeyPressed("MoveLeft"s))
		Move(-move_speed_ * time, 0.f);

	if (KeyPressed("MoveRight"s))
		Move(move_speed_ * time, 0.f);

	if (KeyPush("Fire"s))
	{
		weak_ptr<Object> bullet = ObjectManager::instance()->CreateCloneObject("Bullet"s, layer());

		bullet.lock()->set_position(position() + XY{ 75.f, 0.f });
	}
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
	float left{ position_.x - size_.x * pivot_.x };
	float top{ position_.y - size_.y * pivot_.y };
	Rectangle(device_context, static_cast<int>(left), static_cast<int>(top), static_cast<int>(left + size_.x), static_cast<int>(top + size_.y));
}

unique_ptr<Object, function<void(Object*)>> Player::_Clone()
{
	return unique_ptr<Object, function<void(Object*)>>(new Player(*this), [](Object* p) {
		dynamic_cast<Player*>(p)->_Release();
		delete dynamic_cast<Player*>(p);
	});
}
